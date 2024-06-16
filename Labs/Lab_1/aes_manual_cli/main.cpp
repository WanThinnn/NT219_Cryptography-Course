// CPP lib
// #include "pch.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <sstream>
#include <bitset>
using std::endl;
#include <string>
using std::string;
#include <cstdlib>
#include <cstdint>
using std::exit;
#include "assert.h"
#include <locale>
/**/
/* Set utf8 support for windows*/
#ifdef _WIN32
#include <windows.h>
#endif
/* Convert string <--> utf8*/
#include <locale>
#include <codecvt>
#include "CBC.h"
#include "AES.h"
#ifndef DLL_EXPORT
#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport) // define class specifier
#else
#define DLL_EXPORT
#endif
#endif
extern "C"
{
	DLL_EXPORT void GenerateKeyandIV(int keysize, const char *keyformat, const char *keyfile);
	DLL_EXPORT void Encryption(const char *keyformat, const char *keyfile, const char *plaintextformat, const char *plaintextfile, const char *ciphertextformat, const char *ciphertextfile);
	DLL_EXPORT void Decryption(const char *keyformat, const char *keyfile, const char *ciphertextformat, const char *ciphertextfile, const char *rcvtextformat, const char *rcvtextfile);
}
using namespace std;

vector<uint8_t> str2vector(string str);
string vector2str(vector<uint8_t> byteVector);
std::vector<uint8_t> hex2byte(std::string hexStr);
string byte2hex(vector<uint8_t> byteVector);

vector<uint8_t> str2vector(string str)
{
	// Chuyển đổi string UTF-8 thành vector<uint8_t>
	std::vector<uint8_t> byteVector(str.begin(), str.end());
	return byteVector;
}

/*từ vector byte chuyển sang wstring*/
string vector2str(vector<uint8_t> byteVector)
{
	// Khởi tạo locale với codecvt
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);

	// Chuyển đổi vector<uint8_t> thành chuỗi UTF-8
	std::string utf8Str(byteVector.begin(), byteVector.end());
	// Chuyển đổi chuỗi UTF-8 thành wstring
	return utf8Str;
}
/*từ hex chuyển sang vector byte*/
std::vector<uint8_t> hex2byte(std::string hexStr)
{
	std::vector<uint8_t> byteVector;
	for (size_t i = 0; i < hexStr.size(); i += 2)
	{
		// Lấy cặp ký tự hex từ chuỗi UTF-8 và chuyển đổi thành giá trị uint8_t
		std::string byteStr = hexStr.substr(i, 2);
		uint8_t byte = static_cast<uint8_t>(std::stoul(byteStr, nullptr, 16));
		byteVector.push_back(byte);
	}
	return byteVector;
}

std::vector<uint8_t> stringToByte(const std::string &str)
{
	std::vector<uint8_t> byteVector;
	for (char ch : str)
	{
		byteVector.push_back(static_cast<uint8_t>(ch));
	}
	return byteVector;
}

string byte2hex(vector<uint8_t> byteVector)
{
	stringstream ss;
	string result;
	for (int i = 0; i < byteVector.size(); i++)
	{
		ss << hex << setw(2) << setfill('0') << (unsigned int)(byteVector[i] & 0xff);
	}
	result = ss.str();
	return result;
}

std::string byteToBase64(const std::vector<uint8_t> &bytes)
{
	static const std::string base64Chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	std::string base64;
	base64.reserve((bytes.size() + 2) / 3 * 4);

	int val = 0;
	int bits = -8;
	for (uint8_t byte : bytes)
	{
		val = (val << 8) + byte;
		bits += 8;
		while (bits >= 0 || (bits == -8 && base64.size() % 4 != 0))
		{
			base64.push_back(base64Chars[(val >> bits) & 0x3F]);
			bits -= 6;
		}
	}

	while (base64.size() % 4 != 0)
	{
		base64.push_back('=');
	}

	return base64;
}

std::vector<uint8_t> base64ToByte(const std::string &base64)
{
	static const std::string base64Chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	std::vector<uint8_t> bytes;
	bytes.reserve(base64.size() * 3 / 4);

	int val = 0;
	int bits = -8;
	for (char c : base64)
	{
		if (std::isspace(c))
		{
			continue;
		}
		else if (c == '=')
		{
			break;
		}
		else
		{
			size_t index = base64Chars.find(c);
			if (index == std::string::npos)
			{
				throw std::invalid_argument("Invalid Base64 character");
			}
			val = (val << 6) + index;
			bits += 6;
			if (bits >= 0)
			{
				bytes.push_back((val >> bits) & 0xFF);
				bits -= 8;
			}
		}
	}

	return bytes;
}

std::string HexToString(const std::string &hexInput)
{
	std::stringstream resultStream;
	for (size_t i = 0; i < hexInput.length(); i += 2)
	{
		std::string byteString = hexInput.substr(i, 2);
		int byteValue;
		std::stringstream ss;
		ss << std::hex << byteString;
		ss >> byteValue;
		resultStream << static_cast<char>(byteValue);
	}
	return resultStream.str();
}

std::string stringToHex(const std::string &input)
{
	std::stringstream hexStream;
	hexStream << std::hex << std::uppercase << std::setfill('0');
	for (char ch : input)
	{
		hexStream << std::setw(2) << static_cast<int>(static_cast<unsigned char>(ch));
	}
	return hexStream.str();
}

std::vector<uint8_t> binaryToByte(const std::string &binary)
{
	if (binary.size() % 8 != 0)
	{
		throw std::invalid_argument("Invalid binary string length");
	}

	std::vector<uint8_t> bytes;
	bytes.reserve(binary.size() / 8);

	for (size_t i = 0; i < binary.size(); i += 8)
	{
		std::bitset<8> bits(binary.substr(i, 8));
		bytes.push_back(static_cast<uint8_t>(bits.to_ulong()));
	}

	return bytes;
}

std::string byteToBinary(const std::vector<uint8_t> &bytes)
{
	std::string binary;
	for (uint8_t byte : bytes)
	{
		binary += std::bitset<8>(byte).to_string();
	}
	return binary;
}

// std::string HexToString(const std::string& hexInput) {
//	std::stringstream resultStream;
//	for (size_t i = 0; i < hexInput.length(); i += 2) {
//		// Lấy một cặp ký tự hex từ chuỗi
//		std::string byteString = hexInput.substr(i, 2);
//		// Chuyển đổi ký tự hex thành giá trị số nguyên
//		int byteValue;
//		std::stringstream(byteString) >> std::hex >> byteValue;
//		// Chuyển đổi giá trị số nguyên thành ký tự và thêm vào chuỗi kết quả
//		resultStream << static_cast<char>(byteValue);
//	}
//	return resultStream.str();
// }
//

// Hàm chuyển đổi chuỗi thành chuỗi Base64
std::string StringToBase64(const std::string &input)
{
	// Bảng mã Base64
	const std::string base64Chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	std::stringstream base64Stream;
	int i = 0;
	int j = 0;
	uint32_t bytes3;
	for (char ch : input)
	{
		bytes3 |= ch << (16 - i % 3 * 8);
		i++;
		if (i % 3 == 0)
		{
			base64Stream << base64Chars[(bytes3 >> 18) & 63]
						 << base64Chars[(bytes3 >> 12) & 63]
						 << base64Chars[(bytes3 >> 6) & 63]
						 << base64Chars[bytes3 & 63];
			bytes3 = 0;
		}
	}

	if (i % 3 != 0)
	{
		base64Stream << base64Chars[(bytes3 >> 18) & 63]
					 << base64Chars[(bytes3 >> 12) & 63];
		if (i % 3 == 1)
		{
			base64Stream << "==";
		}
		else
		{
			base64Stream << base64Chars[(bytes3 >> 6) & 63] << "=";
		}
	}

	return base64Stream.str();
}

// Hàm chuyển đổi chuỗi Base64 thành chuỗi
std::string Base64ToString(const std::string &base64Input)
{
	// Bảng mã Base64
	const std::string base64Chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	std::stringstream resultStream;
	uint32_t bytes3 = 0;
	int i = 0;
	for (char ch : base64Input)
	{
		if (ch == '=')
		{
			break;
		}
		bytes3 |= base64Chars.find(ch) << (18 - i % 4 * 6);
		i++;
		if (i % 4 == 0)
		{
			resultStream << static_cast<char>((bytes3 >> 16) & 0xFF)
						 << static_cast<char>((bytes3 >> 8) & 0xFF)
						 << static_cast<char>(bytes3 & 0xFF);
			bytes3 = 0;
		}
	}

	return resultStream.str();
}

std::string StringToBinary(const std::string &input)
{
	std::string binaryString;
	for (char c : input)
	{
		binaryString += std::bitset<8>(c).to_string();
	}
	return binaryString;
}

std::string BinaryToString(const std::string &binaryString)
{
	std::string result;
	for (size_t i = 0; i < binaryString.length(); i += 8)
	{
		std::bitset<8> bits(binaryString.substr(i, 8));
		result += char(bits.to_ulong());
	}
	return result;
}

// Hàm để tạo ngẫu nhiên khóa AES và trả về dưới dạng chuỗi string
std::string generateRandomKeyAsString(int keySize)
{
	std::random_device rd;							// Thiết bị sinh số ngẫu nhiên
	std::mt19937 gen(rd());							// Máy sinh số ngẫu nhiên với seed từ rd
	std::uniform_int_distribution<int> dis(0, 255); // Phân phối đồng nhất từ 0 đến 255

	std::string result;
	for (int i = 0; i < keySize; ++i)
	{
		result += static_cast<char>(dis(gen)); // Chuyển đổi byte ngẫu nhiên thành ký tự ASCII và thêm vào chuỗi kết quả
	}
	return result; // Trả về chuỗi string
}

// Hàm để tạo ngẫu nhiên IV và trả về dưới dạng chuỗi string
std::string generateRandomIVAsString()
{
	std::random_device rd;							 // Thiết bị sinh số ngẫu nhiên
	std::mt19937 gen(rd());							 // Máy sinh số ngẫu nhiên với seed từ rd
	std::uniform_int_distribution<int> dis(97, 122); // Phân phối đồng nhất từ 'a' đến 'z'

	std::string result;
	for (int i = 0; i < 16; ++i)
	{												   // Tạo IV có kích thước 16 byte (128 bit)
		char randomChar = static_cast<char>(dis(gen)); // Tạo một ký tự ngẫu nhiên
		result += randomChar;						   // Thêm ký tự vào chuỗi kết quả
	}
	return result; // Trả về chuỗi string
}

std::string readTextFromFile(const std::string &filename)
{
	std::ifstream file(filename); // Mở tập tin để đọc
	std::string content;		  // Chuỗi để lưu nội dung của tập tin
	std::string line;			  // Chuỗi để lưu từng dòng trong tập tin

	if (file.is_open())
	{
		// Đọc từng dòng trong tập tin và thêm vào chuỗi content
		while (std::getline(file, line))
		{
			content += line;
			// Không thêm dấu xuống dòng sau mỗi dòng
		}
		file.close(); // Đóng tập tin
	}
	else
	{
		std::cerr << "Unable to open file: " << filename << std::endl;
	}

	return content;
}

void saveTextToFile(const std::string &filename, const std::string &content)
{
	std::ofstream file(filename); // Mở tập tin để ghi
	if (file.is_open())
	{
		file << content; // Ghi nội dung vào tập tin
		file.close();	 // Đóng tập tin
	}
	else
	{
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
}

void GenerateKeyandIV(int keysize, const char *keyformat, const char *keyfile)
{
	string Key = generateRandomKeyAsString(keysize / 8);
	string IV = generateRandomIVAsString();
	string keyFormatStr(keyformat); // Chuyển đổi const char* thành std::string
	string keyFileStr(keyfile);

	if (keyFormatStr == "HEX")
	{
		saveTextToFile(keyFileStr, stringToHex(Key));
		saveTextToFile("aes_iv.key", stringToHex(IV));
	}
	else if (keyFormatStr == "Binary")
	{
		saveTextToFile(keyFileStr, StringToBinary(Key));
		saveTextToFile("aes_iv.key", StringToBinary(IV));
	}

	cout << "Successfully generated key and IV!" << endl;
	cout << "Key saved to: " << keyfile << endl;
	cout << "IV saved to: aes_iv.key" << endl;
}

void Encryption(const char *keyformat, const char *keyfile, const char *plaintextformat, const char *plaintextfile, const char *ciphertextformat, const char *ciphertextfile)
{
	string plaintext = readTextFromFile(plaintextfile);
	string Key = readTextFromFile(keyfile);
	string IV = readTextFromFile("aes_iv.key");
	string keyFormatStr(keyformat);
	string plaintextFormatStr(plaintextformat);
	string ciphertextFormatStr(ciphertextformat);
	string ciphertextFileStr(ciphertextfile);

	if (keyFormatStr == "HEX")
	{
		Key = HexToString(Key);
		IV = HexToString(IV);
	}
	else if (keyFormatStr == "Binary")
	{
		Key = BinaryToString(Key);
		IV = BinaryToString(IV);
	}
	else
	{
		cout << "Unsupported key format!" << endl;
	}

	if (plaintextFormatStr == "HEX")
	{
		plaintext = HexToString(plaintext);
	}
	else if (plaintextFormatStr == "Binary")
	{
		plaintext = BinaryToString(plaintext);
	}
	else if (plaintextFormatStr == "Text")
	{
		plaintext = plaintext;
	}
	else
	{
		cout << "Unsupported plaintext format!" << endl;
	}

	vector<uint8_t> byte_pl = str2vector(plaintext);
	vector<uint8_t> byte_key = str2vector(Key);
	vector<uint8_t> byte_iv = str2vector(IV);

	CBC_mode mode = CBC_mode(byte_key, byte_iv);
	vector<uint8_t> enc_data = mode.cbc_encrypt(byte_pl);

	string cipher;
	if (ciphertextFormatStr == "HEX")
	{
		cipher = byte2hex(enc_data);
	}
	else if (ciphertextFormatStr == "Binary")
	{
		cipher = byteToBinary(enc_data);
	}
	else
	{
		cout << "Unsupported ciphertext format!" << endl;
	}

	saveTextToFile(ciphertextFileStr, cipher);

	// cout << "Successfully encrypted!" << endl;
	// cout << "Ciphertext saved to: " << ciphertextfile << endl;
}

void Decryption(const char *keyformat, const char *keyfile, const char *ciphertextformat, const char *ciphertextfile, const char *rcvtextformat, const char *rcvtextfile)
{
	string cipher = readTextFromFile(ciphertextfile);
	string Key = readTextFromFile(keyfile);
	string IV = readTextFromFile("aes_iv.key");
	string keyFormatStr(keyformat);
	string ciphertextFormatStr(ciphertextformat);
	string rcvtextFormatStr(rcvtextformat);
	string rcvtextFileStr(rcvtextfile);

	if (keyFormatStr == "HEX")
	{
		Key = HexToString(Key);
		IV = HexToString(IV);
	}
	else if (keyFormatStr == "Binary")
	{
		Key = BinaryToString(Key);
		IV = BinaryToString(IV);
	}
	else
	{
		cout << "Unsupported key format!" << endl;
	}

	if (ciphertextFormatStr == "HEX")
	{
		cipher = HexToString(cipher);
	}
	else if (ciphertextFormatStr == "Binary")
	{
		cipher = BinaryToString(cipher);
	}
	else
	{
		cout << "Unsupported ciphertext format!" << endl;
	}

	vector<uint8_t> byte_cipher = str2vector(cipher);
	vector<uint8_t> byte_key = str2vector(Key);
	vector<uint8_t> byte_iv = str2vector(IV);

	CBC_mode mode = CBC_mode(byte_key, byte_iv);
	vector<uint8_t> dec_data = mode.cbc_decrypt(byte_cipher);

	string recovered;
	if (rcvtextFormatStr == "HEX")
	{
		recovered = stringToHex(vector2str(dec_data));
	}
	else if (rcvtextFormatStr == "Binary")
	{
		recovered = StringToBinary(vector2str(dec_data));
	}
	else if (rcvtextFormatStr == "Text")
	{
		recovered = vector2str(dec_data);
	}
	else
	{
		cout << "Unsupported recovered text format!" << endl;
	}

	saveTextToFile(rcvtextFileStr, recovered);

	// cout << "Successfully decrypted!" << endl;
	// cout << "Recovered text saved to: " << rcvtextfile << endl;
}

void ProcessInput(const string &action, int argc, char *argv[])
{
	string mode = argv[2];
	if (action == "genkey")
	{
		if (argc != 5)
		{
			cerr << "Usage: " << argv[0] << " genkey <KeySize> <KeyFileFormat> <KeyFile>" << endl;
			return;
		}
		int KeySize = std::stoi(argv[2]);
		GenerateKeyandIV(KeySize, argv[3], argv[4]);
	}
	else if (action == "encrypt")
	{
		if (argc != 8)
		{
			cerr << "Usage: " << argv[0] << " encrypt <KeyFileFormat> <KeyFile> <PlaintextFormat> <PlaintextFile> <CipherFormat> <CipherFile>" << endl;
			return;
		}
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; i++)
		{
			Encryption(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
		}
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		cout << "----------------------------------------------------------" << endl;
		cout << "Overview AES CBC Manual Encryption Test" << endl;
		cout << "Encryption time: " << duration.count() << " milliseconds" << endl;
		cout << "----------------------------------------------------------" << endl;
	}
	else if (action == "decrypt")
	{
		if (argc != 8)
		{
			cerr << "Usage: " << argv[0] << " decrypt <KeyFileFormat> <KeyFile> <CipherFormat> <CipherFile> <RecoveredFileFormat> <RecoveredFile> " << endl;
			return;
		}

		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; i++)
		{
		Decryption(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
		}
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		cout << "----------------------------------------------------------" << endl;
		cout << "Overview AES CBC Manual Decryption Test" << endl;
		cout << "Decryption time: " << duration.count() << " milliseconds" << endl;
		cout << "----------------------------------------------------------" << endl;
	}
	else
	{
		cerr << "Invalid action. Please choose 'genkey', 'encrypt', or 'decrypt'." << endl;
	}
}

int main(int argc, char *argv[])
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif
	std::ios_base::sync_with_stdio(false);

	if (argc < 2)
	{
		cerr << "Invalid arguments. Please follow the instructions:\n";

		cerr << "Usage:\n"
			 << "\t" << argv[0] << " genkey <KeySize> <KeyFileFormat> <KeyFile>\n"
			 << "\t" << argv[0] << " encrypt <KeyFileFormat> <KeyFile> <PlaintextFormat> <PlaintextFile> <CipherFormat> <CipherFile>\n"
			 << "\t" << argv[0] << " decrypt <KeyFileFormat> <KeyFile> <CipherFormat> <CipherFile> <RecoveredFileFormat> <RecoveredFile> \n";

		return -1;
	}

	string action = argv[1];

	ProcessInput(action, argc, argv);

	return 0;
}
