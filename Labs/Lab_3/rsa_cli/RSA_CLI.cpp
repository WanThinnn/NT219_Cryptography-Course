// #include "pch.h"

// #ifndef DLL_EXPORT
// #ifdef _WIN32
//     #define DLL_EXPORT __declspec(dllexport)
// #else
//     #define DLL_EXPORT
// #endif
// #endif

// extern "C"
// {
//     DLL_EXPORT void GenerationAndSaveRSAKeys(int keySize, const char* format, const char* privateKeyFile, const char* publicKeyFile);
//     DLL_EXPORT void RSAencrypt(const char* keyformat, const char* publicKeyFile, const char* PlaintextFormat, const char* PlaintextFile, const char* CipherFormat, const char* CipherFile);
//     DLL_EXPORT void RSAdecrypt(const char* keyformat, const char* privateKeyFile, const char* CipherFormat, const char* CipherFile, const char* RecoveredFormat, const char* RecoverFile);
// }


// C/C++ libraries
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <string>
using std::exit;
#include <cstdlib>
using std::string;

using namespace std;
// header part
#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdlib>
#include <locale>
#include <cctype>

// Cryptopp libraries

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "cryptopp/cryptlib.h"
using CryptoPP::Exception;

#include "cryptopp/hex.h"
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;
// base64
#include "cryptopp/base64.h"
using CryptoPP::Base64Decoder;
using CryptoPP::Base64Encoder;

#include "cryptopp/filters.h"
using CryptoPP::PK_DecryptorFilter;
using CryptoPP::PK_EncryptorFilter;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

/* Integer arithmatics*/
#include <cryptopp/integer.h>
using CryptoPP::Integer;

#include <cryptopp/nbtheory.h>
using CryptoPP::ModularSquareRoot;

#include <cryptopp/modarith.h>
using CryptoPP::ModularArithmetic;
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <stdexcept>
using std::runtime_error;

#include <cryptopp/queue.h>
using CryptoPP::ByteQueue;

#include <cryptopp/files.h>
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include "cryptopp/rsa.h"
using CryptoPP::RSA;

#include "cryptopp/base64.h"
using CryptoPP::Base64Decoder;
using CryptoPP::Base64Encoder;

#include "cryptopp/hex.h"
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

#include <cryptopp/cryptlib.h>
using CryptoPP::BufferedTransformation;
using CryptoPP::PrivateKey;
using CryptoPP::PublicKey;

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

// them vo ba cai nay de lam encode decode
#include "cryptopp/filters.h"
using CryptoPP::StreamTransformationFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include "cryptopp/rsa.h"
using CryptoPP::InvertibleRSAFunction;
using CryptoPP::RSA;
using CryptoPP::RSAES_OAEP_SHA_Decryptor;
using CryptoPP::RSAES_OAEP_SHA_Encryptor;

#include "cryptopp/sha.h"
using CryptoPP::SHA1; // for padding OAEP




// Def functions
/* ################################################################ */
// Function to save a PrivateKey key in DER format
void SavePriKeyDER(const std::string& filename, const RSA::PrivateKey& key) {
	ByteQueue queue;
	key.DEREncodePrivateKey(queue);
	FileSink file(filename.c_str());
	queue.CopyTo(file);
	file.MessageEnd();
}


// Functions to save a PublicKey key in DER format (Distinguished Encoding Rules)
void SavePubKeyDER(const std::string& filename, const RSA::PublicKey& key) {
	ByteQueue queue;
	key.DEREncodePublicKey(queue);
	FileSink file(filename.c_str());
	queue.CopyTo(file);
	file.MessageEnd();
}


void Save(const string& filename, const BufferedTransformation& bt)
{
	// http://www.cryptopp.com/docs/ref/class_file_sink.html
	FileSink file(filename.c_str());

	bt.CopyTo(file);
	file.MessageEnd();
}

void SaveBase64(const string& filename, const BufferedTransformation& bt)
{
	// http://www.cryptopp.com/docs/ref/class_base64_encoder.html
	Base64Encoder encoder;

	bt.CopyTo(encoder);
	encoder.MessageEnd();

	Save(filename, encoder);
}




void SaveBase64PrivateKey(const string& filename, const PrivateKey& key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;
	key.Save(queue);

	SaveBase64(filename, queue);
}




void SaveBase64PublicKey(const string& filename, const PublicKey& key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;
	key.Save(queue);

	SaveBase64(filename, queue);
}



// Helper function to encode and write in proper PEM format
void WritePEM(const ByteQueue& queue, std::ofstream& file, const std::string& begin, const std::string& end)
{
	file << begin << "\n";

	// Create a Base64Encoder that writes to a std::string
	std::string encoded;
	Base64Encoder encoder(new StringSink(encoded), true, 64 /* insert line breaks */);

	// Copy queue contents to encoder
	queue.CopyTo(encoder);
	encoder.MessageEnd();

	// Write encoded content to file with proper line breaks
	file << encoded;
	file << end; // Ensure there's a newline before and after the footer
}

// Function to save a public key in PEM format
void SavePubKeyPEM(const std::string& filename, const RSA::PublicKey& key)
{
	std::ofstream file(filename);
	ByteQueue queue;
	key.DEREncodePublicKey(queue);
	WritePEM(queue, file, "-----BEGIN PUBLIC KEY-----", "-----END PUBLIC KEY-----");
	file.close();
}

// Function to save a private key in PEM format
void SavePriKeyPEM(const std::string& filename, const RSA::PrivateKey& key)
{
	std::ofstream file(filename);
	ByteQueue queue;
	key.DEREncodePrivateKey(queue);
	WritePEM(queue, file, "-----BEGIN RSA PRIVATE KEY-----", "-----END RSA PRIVATE KEY-----");
	file.close();
}







// Function to load a PublicKey key from a DER format
void LoadPubKeyDER(const std::string& filename, RSA::PublicKey& key) {
	FileSource file(filename.c_str(), true);
	ByteQueue queue;
	file.TransferTo(queue);
	queue.MessageEnd();
	key.BERDecodePublicKey(queue, false /*optParams*/, queue.MaxRetrievable());
}

// Function to load a PrivateKey key from a DER format
void LoadPriKeyDER(const std::string& filename, RSA::PrivateKey& key) {
	FileSource file(filename.c_str(), true);
	ByteQueue queue;
	file.TransferTo(queue);
	queue.MessageEnd();
	key.BERDecodePrivateKey(queue, false /*optParams*/, queue.MaxRetrievable());
}


void LoadBase64PrivateKey(const string& filename, PrivateKey& key)
{
	// Create a FileSource that automatically decodes Base64 data from the file
	CryptoPP::FileSource file(filename.c_str(), true, new CryptoPP::Base64Decoder);

	// Load the decoded data into a ByteQueue
	CryptoPP::ByteQueue queue;
	file.TransferTo(queue);
	queue.MessageEnd();

	// Load the private key from the ByteQueue
	key.Load(queue);

	// Optionally, check the validity of the loaded key
	CryptoPP::AutoSeededRandomPool prng;
	if (!key.Validate(prng, 3))
	{
		throw std::runtime_error("Loaded private key is invalid.");
	}
}

void LoadBase64PublicKey(const string& filename, PublicKey& key)
{
	// Create a FileSource that automatically decodes Base64 data from the file
	CryptoPP::FileSource file(filename.c_str(), true, new CryptoPP::Base64Decoder);

	// Load the decoded data into a ByteQueue
	CryptoPP::ByteQueue queue;
	file.TransferTo(queue);
	queue.MessageEnd();

	// Load the public key from the ByteQueue
	key.Load(queue);
	// Optionally, check the validity of the loaded key
	AutoSeededRandomPool prng;
	if (!key.Validate(prng, 3))
	{
		throw std::runtime_error("Loaded public key is invalid.");
	}
}




// Helper function to read and decode from PEM format
void ReadPEM(ByteQueue& queue, const string& filename, const string& begin, const string& end)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw runtime_error("Failed to open file: " + filename);
	}

	string line, encoded;
	bool capture = false;
	while (getline(file, line))
	{
		// Check for the begin marker to start capturing
		if (line.find(begin) != string::npos)
		{
			capture = true;
			continue; // Skip the line with the begin marker
		}
		// Stop capturing after finding the end marker and skip it
		if (line.find(end) != string::npos)
		{
			break;
		}
		// Append the line to the encoded string if capturing is active
		if (capture)
		{
			encoded += line;
		}
	}
	// cout << "Successfully read the key: " << filename << endl;
	// Decode the captured Base64 content into the ByteQueue
	StringSource(encoded, true, new Base64Decoder(new CryptoPP::Redirector(queue)));
}

// Function to load a public key from PEM format
void LoadPubKeyPEM(const std::string& filename, RSA::PublicKey& key)
{
	ByteQueue queue;
	ReadPEM(queue, filename, "-----BEGIN PUBLIC KEY-----", "-----END PUBLIC KEY-----");
	key.BERDecodePublicKey(queue, false /*optParams*/, queue.MaxRetrievable());
	// key.Load(queue);
}

// Function to load a private key from PEM format
void LoadPriKeyPEM(const std::string& filename, RSA::PrivateKey& key)
{
	ByteQueue queue;
	ReadPEM(queue, filename, "-----BEGIN RSA PRIVATE KEY-----", "-----END RSA PRIVATE KEY-----");
	key.BERDecodePrivateKey(queue, false /*optParams*/, queue.MaxRetrievable());
	// key.Load(queue);
}

// RSA keys generation
void GenerationAndSaveRSAKeys(int keySize, const char* format, const char* privateKeyFile, const char* publicKeyFile)
{

	string strFormat(format);
	string strPrivateKeyFile(privateKeyFile);
	string strPublicKeyFile(publicKeyFile);
	AutoSeededRandomPool rnd;

	// General private key
	RSA::PrivateKey rsaPrivate;
	rsaPrivate.GenerateRandomWithKeySize(rnd, keySize); // tao RSA


	// General public key
    RSA::PublicKey rsaPublic;
    rsaPublic.AssignFrom(rsaPrivate); // Tạo khóa công khai từ khóa riêng

	if (strFormat == "DER")
	{

		// Save keys to file (BIN)
		SavePriKeyDER(strPrivateKeyFile, rsaPrivate);
		SavePubKeyDER(strPublicKeyFile, rsaPublic);
	}
	else if (strFormat == "Base64")
	{
		// Save keys to file (BASE64)
		SaveBase64PrivateKey(strPrivateKeyFile, rsaPrivate);
		SaveBase64PublicKey(strPublicKeyFile, rsaPublic);
	}
	else if (strFormat == "PEM")
	{
		// Save keys to file (BASE64)
		SavePriKeyPEM(strPrivateKeyFile, rsaPrivate);
		SavePubKeyPEM(strPublicKeyFile, rsaPublic);
	}
	else
	{
		cerr << "Unsupported format. Please choose 'DER, 'Base64'." << endl;
		exit(1);
	}

	Integer modul1 = rsaPrivate.GetModulus();
	Integer prime1 = rsaPrivate.GetPrime1();
	Integer prime2 = rsaPrivate.GetPrime2();
	Integer SK = rsaPrivate.GetPrivateExponent();

	Integer PK = rsaPublic.GetPublicExponent();
	Integer modul2 = rsaPublic.GetModulus();

	// cout<<"Modulo (private) n = "<<modul1<<endl;
	// cout << endl;
	// cout<<"Modulo (public) n = "<<modul2<<endl;
	// cout << endl;
	// cout<<"Prime number 1 (private) p = "<<std::hex<<prime1<<std::dec<<endl;
	// cout << endl;
	// cout<<"Prime number 2 (private) q = "<<std::hex<<prime2<<std::dec<<endl;
	// cout << endl;
	// cout<<"Secret exponent d = "<<SK<<endl;
	// cout << endl;
	// cout<<"Public exponent e = "<<PK<<endl;
	// cout << endl;

	//Checking the key generator function
	// RSA::PrivateKey r1, r2;
	// r1.GenerateRandomWithKeySize(rnd, keySize);

	// SavePrivateKey("rsa-roundtrip.key", r1);
	// LoadPrivateKey("rsa-roundtrip.key", r2);

	// r1.Validate(rnd, 3);
	// r2.Validate(rnd, 3);

	// if(r1.GetModulus() != r2.GetModulus() ||
	//    r1.GetPublicExponent() != r2.GetPublicExponent() ||
	//    r1.GetPrivateExponent() != r2.GetPrivateExponent())
	// {
	// 	throw runtime_error("key data did not round trip");
	// }

	////////////////////////////////////////////////////////////////////////////////////

	// cout << "Successfully generated and saved RSA keys" << endl;
}

// encrypt
void RSAencrypt(const char* keyformat, const char* publicKeyFile, const char* PlaintextFormat, const char* PlaintextFile, const char* CipherFormat, const char* CipherFile)
{
	RSA::PrivateKey privateKey;
	RSA::PublicKey publicKey;
	string strKeyFormat(keyformat);
	string strpublicKeyFile(publicKeyFile);
	string strPlaintextFormat(PlaintextFormat);
	string strCipherFormat(CipherFormat);



	AutoSeededRandomPool rnd;
	// load key from files
	if (strKeyFormat == "DER")
	{
		LoadPubKeyDER(strpublicKeyFile, publicKey);
	}
	else if (strKeyFormat == "Base64")
	{
		LoadBase64PublicKey(strpublicKeyFile, publicKey);
	}
	else if (strKeyFormat == "PEM")
	{
		LoadPubKeyPEM(strpublicKeyFile, publicKey);
	}
	else
	{
		cout << "Key format unsupported!" << endl;
	}

	// Load plaintext
	string plain;
	if (strPlaintextFormat == "Text")
	{
		FileSource fs(PlaintextFile, true, new StringSink(plain), false);
	}
	else if (strPlaintextFormat == "DER")
	{
		FileSource fs(PlaintextFile, true, new StringSink(plain), true);
	}
	else if (strPlaintextFormat == "Base64")
	{
		FileSource fs(PlaintextFile, true, new Base64Decoder(new StringSink(plain)), false);
	}
	else if (strPlaintextFormat == "HEX")
	{
		FileSource fs(PlaintextFile, true, new HexDecoder(new StringSink(plain)), false);
	}
	else
	{
		cerr << "Unsupported plain text format. Please choose 'Text', 'DER', 'Base64' or 'HEX'!\n";
		exit(1);
	}



	RSAES_OAEP_SHA_Encryptor ecryptor(publicKey);


	// Save cipher
	if (strCipherFormat == "DER")
	{
		StringSource(plain, true,
			new PK_EncryptorFilter(rnd, ecryptor,
				new FileSink(CipherFile, true)) // PK_EncryptorFilter
		);
	}
	else if (strCipherFormat == "Base64")
	{
		StringSource(plain, true,
			new PK_EncryptorFilter(rnd, ecryptor,
				new Base64Encoder(new FileSink(CipherFile, true)))); // PK_EncryptorFilter
	}
	else if (strCipherFormat == "HEX")
	{
		StringSource(plain, true,
			new PK_EncryptorFilter(rnd, ecryptor,
				new HexEncoder(new FileSink(CipherFile, true)))); // PK_EncryptorFilter
	}
	else
	{
		cerr << "Unsupported cipher format. Please choose 'DER', 'Base64' or 'HEX'\n";
		exit(1);
	}
	// cout << "Successfully encrypt in CipherFile: " << CipherFile << endl;
}

// decrypt
void RSAdecrypt(const char* keyformat, const char* privateKeyFile, const char* CipherFormat, const char* CipherFile, const char* RecoveredFormat, const char* RecoverFile)
{
	RSA::PrivateKey privateKey;
	RSA::PublicKey publicKey;
	AutoSeededRandomPool rnd;
	string strPubKeyFormat(keyformat);
	string strprivateKeyFile(privateKeyFile);
	string strRcvFormat(RecoveredFormat);
	string strCipherFormat(CipherFormat);

	//Load Key
	if (strPubKeyFormat == "DER")
	{
		LoadPriKeyDER(strprivateKeyFile, privateKey);
	}
	else if (strPubKeyFormat == "Base64")
	{
		LoadBase64PrivateKey(strprivateKeyFile, privateKey);
	}
	else if (strPubKeyFormat == "PEM")
	{
		LoadPriKeyPEM(strprivateKeyFile, privateKey);
	}

	else
	{
		cout << "Key format unsupported!" << endl;
	}
	// Khởi tạo đối tượng để giải mã RSA
	RSAES_OAEP_SHA_Decryptor decryptor(privateKey);

	string  cipher;

	if (strCipherFormat == "DER" || strCipherFormat == "Base64" || strCipherFormat == "HEX")
	{
		// Load ciphertext from file with the specified format
		string encodedCipher;
		FileSource fs(CipherFile, true, new StringSink(encodedCipher));

		if (strCipherFormat == "Base64")
		{
			// Decode Base64 ciphertext
			StringSource(encodedCipher, true,
				new Base64Decoder(new StringSink(cipher)));
		}
		else if (strCipherFormat == "HEX")
		{
			// Decode HEX ciphertext
			StringSource(encodedCipher, true,
				new HexDecoder(new StringSink(cipher)));
		}
		else
		{
			// Use ciphertext as is (DER format)
			cipher = encodedCipher;
		}
	}
	else
	{
		cerr << "Unsupported cipher format. Please choose 'DER', 'Base64' or 'HEX'\n";
		exit(1);
	}

	string rcv;
	// Giải mã dữ liệu
	StringSource(cipher, true,
		new PK_DecryptorFilter(rnd, decryptor,
			new StringSink(rcv))); // PK_DecryptorFilter


	// Save recovered
	if (strRcvFormat == "Text")
	{
		StringSource(rcv, true,
			new FileSink(RecoverFile, false));
	}
	else if (strRcvFormat == "DER")
	{
		StringSource(rcv, true,
			new FileSink(RecoverFile, true));
	}
	else if (strRcvFormat == "Base64")
	{
		StringSource(rcv, true,
			new Base64Encoder(
				new FileSink(RecoverFile, false)));
	}
	else if (strRcvFormat == "HEX")
	{
		StringSource(rcv, true,
			new HexEncoder(
				new FileSink(RecoverFile, false)));
	}
	else
	{
		cerr << "Unsupported recovery text format. Please choose 'Text', 'DER', 'Base64' or 'HEX'!\n";
		exit(1);
	}




	// cout << "Successfully decrypt in RecoveredFile: " << RecoverFile << endl;
}

int main(int argc, char** argv)
{
	// Set locale to support UTF-8
#ifdef linux
	std::locale::global(std::locale("C.utf8"));
#endif
#ifdef _WIN32
	// Set console code page to UTF-8 on Windows C.utf8, CP_UTF8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif

	std::ios_base::sync_with_stdio(false);

	// GenerationAndSaveRSAKeys(keySize, format, privateKeyFile, PublicKeyFile );
	if (argc < 2)
	{
		cerr << "Usage: \n"
			<< argv[0] << " genkey <KeySize> <KeyFormat> <PrivateKeyFile> <PublicKeyFile>\n"
			<< argv[0] << " encrypt <KeyFormat> <PublicKeyFile> <PlainTextFormat> <PlainTextFile> <CipherTextFormat> <CipherFile>\n"
			<< argv[0] << " decrypt <KeyFormat> <PrivateKeyFile> <CiphertextFormat> <CipherFile> <rcvTextFormat> <rcvTextFile>\n";
		return -1;
	}

	string mode = argv[1];

	if (mode == "genkey" && argc == 6)
	{
		int keySize = std::stoi(argv[2]);
		GenerationAndSaveRSAKeys(keySize, argv[3], argv[4], argv[5]);
	}
	else if (mode == "encrypt" && argc == 8)
	{
		auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++){
			RSAencrypt(argv[2], argv[3], argv[4], argv[5],argv[6], argv[7]);

        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        cout << "Overview RSA Encryption Test" << endl;
        cout << "Encryption time: " << duration.count() << " milliseconds" << endl;
        cout << "----------------------------------------------------------" << endl;

        cout.flush(); // Đảm bảo dữ liệu được ghi vào cout sẽ được xuất ra màn hình ngay lập tức

	}
	else if (mode == "decrypt" && argc == 8)
	{
		

		auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++){
			RSAdecrypt(argv[2], argv[3], argv[4], argv[5],argv[6], argv[7]);

        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        cout << "Overview RSA Decryption Test" << endl;
        cout << "Decryption time: " << duration.count() << " milliseconds" << endl;
        cout << "----------------------------------------------------------" << endl;

        cout.flush(); // Đảm bảo dữ liệu được ghi vào cout sẽ được xuất ra màn hình ngay lập tức
	}
	else
	{
		cerr << "Invalid arguments. Please check the usage instructions.\n";
		return -1;
	}

	return 0;
}
