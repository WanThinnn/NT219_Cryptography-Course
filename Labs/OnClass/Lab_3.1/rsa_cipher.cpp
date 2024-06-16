#include <bits/stdc++.h>

using namespace std;

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif



#include "cryptopp/rsa.h"
using CryptoPP::InvertibleRSAFunction;
using CryptoPP::RSA;
using CryptoPP::RSAES_OAEP_SHA_Decryptor;
using CryptoPP::RSAES_OAEP_SHA_Encryptor;

#include "cryptopp/filters.h"
using CryptoPP::PK_DecryptorFilter;
using CryptoPP::PK_EncryptorFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include "cryptopp/files.h"
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "cryptopp/queue.h"
using CryptoPP::ByteQueue;

#include "cryptopp/cryptlib.h"
using CryptoPP::BufferedTransformation;
using CryptoPP::Exception;
using CryptoPP::PrivateKey;
using CryptoPP::PublicKey;

#include "cryptopp/hex.h"
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

#include "cryptopp/nbtheory.h"
#include "cryptopp/modarith.h"
#include "cryptopp/integer.h"
using CryptoPP::Integer;


// Conver integer to wstring;
wstring integer_to_wstring (const CryptoPP::Integer& t)
{
    std::ostringstream oss;
    oss.str("");
    oss.clear();
    oss << t;
    std::string encoded(oss.str());
    std::wstring_convert<codecvt_utf8<wchar_t>> towstring;
    return towstring.from_bytes(encoded);
}

// Conver integer to string;
string integer_to_string (const CryptoPP::Integer& t)
{
    std::ostringstream oss;
    oss.str("");
    oss.clear();
    oss << t;
    std::string encoded(oss.str());
    return encoded;
}

// Convert string to wstring
wstring s2ws(const std::string &str)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.from_bytes(str);
}

// Convert wstring to string
string ws2s(const std::wstring &wstr)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.to_bytes(wstr);
}

// convert byte string to hex wstring cryptopp::byte
void BeautifulPrinter(string byteString)
{
	string encodedCode = "";
	StringSource(byteString, true,
				 new HexEncoder(
					 new StringSink(encodedCode)));
	wstring wstr = s2ws(encodedCode);
	wcout << wstr << endl;
}

// convert byte string to hex wstring cryptopp::byte
wstring BeautifulPrinterForFile(string byteString)
{
	string encodedCode = "";
	StringSource(byteString, true,
				 new HexEncoder(
					 new StringSink(encodedCode)));
	wstring wstr = s2ws(encodedCode);
	return wstr;
}

// convert byte string to hex wstring cryptopp::byte
string BeautifulPrinterForFileString(string str)
{
	string encodedCode = "";
	StringSource(str, true,
				 new HexEncoder(
					 new StringSink(encodedCode)));
	return encodedCode;
}

// get the key from file
void getKeyFromFile(const string &filename, BufferedTransformation &bufferedTransformation)
{
	FileSource file(filename.c_str(), true);
	file.TransferTo(bufferedTransformation);
	bufferedTransformation.MessageEnd();
}

// get private key from file
void getPrivateKeyFromFile(const string &filename, PrivateKey &key)
{
	ByteQueue queueOfByte;
	getKeyFromFile(filename, queueOfByte);
	key.Load(queueOfByte);
}

// get public key from file
void getPublicKeyFromFile(const string &filename, PublicKey &key)
{
	ByteQueue queueOfByte;
	getKeyFromFile(filename, queueOfByte);
	key.Load(queueOfByte);
}

// decode the hex string from the input file
string decodeCiphertext(const wstring &wciphertext)
{
	string ciphertext;
	StringSource(ws2s(wciphertext), true,
				 new HexDecoder(new StringSink(ciphertext)));
	return ciphertext;
}

// select encrypt or decrypt
int selectEncDec()
{
	int choice;
	wcout << L"Menu" << endl;
	wcout << L"1. Key gen" << endl;
	wcout << L"2. Encrypt" << endl;
	wcout << L"3. Decrypt" << endl;
	wcout << L"Enter your choice: ";

		wcin >> choice;
		if (choice < 1 || choice > 3)
		{
			wcout << L"Invalid choice!" << endl;
			exit(1);
		}


	return choice;
}

// get the type of input
int selectTypeOfInput()
{
	int choose;
	wcout << L"Input from file or keyboard?" << endl;
	wcout << L"1. File" << endl;
	wcout << L"2. Keyboard" << endl;
	wcout << "Choose: ";
	wcin >> choose;
	if (choose < 1 || choose > 2)
	{
		wcout << L"Invalid choice!" << endl;
		exit(1);
	}

	return choose;
}

// this is the rsa encryption function
string rsaEncrypt(AutoSeededRandomPool &prng, const RSA::PublicKey &rsaPublicKey, const string &plaintext)
{
	string ciphertext;
	RSAES_OAEP_SHA_Encryptor encryptor(rsaPublicKey);
	StringSource(plaintext, true,
				 new PK_EncryptorFilter(prng, encryptor,
										new StringSink(ciphertext)));
	return ciphertext;
}

// this is the rsa decryption function
string rsaDecrypt(AutoSeededRandomPool &prng, const RSA::PrivateKey &rsaPrivateKey, const string &ciphertext)
{
	string recovertext;
	RSAES_OAEP_SHA_Decryptor decryptor(rsaPrivateKey);
	StringSource(ciphertext, true,
				 new PK_DecryptorFilter(prng, decryptor,
										new StringSink(recovertext)));
	return recovertext;
}

// this is the rsa function to get the key and validate the key
void getKeyFromFileAndValidate(RSA::PrivateKey &rsaPrivateKey, RSA::PublicKey &rsaPublicKey)
{
	AutoSeededRandomPool prng;

	#ifdef _WIN32
			getPrivateKeyFromFile(".\\rsaPrivate.key", rsaPrivateKey);
			getPublicKeyFromFile(".\\rsaPublic.key", rsaPublicKey);

	#elif __linux__
			getPrivateKeyFromFile("./rsaPrivate.key", rsaPrivateKey);
			getPublicKeyFromFile("./rsaPublic.key", rsaPublicKey);

	#endif

	if (rsaPrivateKey.Validate(prng, 3) == false)
	{
		wcout << L"Invalid private key!" << endl;
		exit(1);
	}
	if (rsaPublicKey.Validate(prng, 3) == false)
	{
		wcout << L"Invalid public key!" << endl;
		exit(1);
	}

}

// this function to get the text from the file
string getPlaintextFromFile(string filename)
{
	string plaintext;
	ifstream file(filename);
	if (file.is_open())
	{
		getline(file, plaintext);
		file.close();
	}
	else
	{
		wcout << L"Unable to open file!" << endl;
		exit(1);
	}
	return plaintext;
}

// save the ciphertext to file
void saveCiphertextToFile(const string &filename, const string &ciphertext)
{
	ofstream file(filename);
	if (file.is_open())
	{
		file << ciphertext;
		file.close();
	}
	else
	{
		wcout << L"Unable to open file!" << endl;
		exit(1);
	}
}

// this function to get the data from the file
string getCiphertextFromFile(string filename)
{
	std::ifstream in_file;
	in_file.open(filename);
	if (!in_file.is_open())
	{
		wcout << L"Can not open file!" << endl;
		exit(1);
	}

	string data;
	string line;
	while (in_file.good())
	{
		getline(in_file, line);
		data += line;
	}
	in_file.close();
	return data;
}

// this function to transform the integer to wstring
wstring in2ws(const CryptoPP::Integer &t)
{
	std::ostringstream oss;
	oss.str("");
	oss.clear();
	oss << t;
	std::string encoded(oss.str());
	std::wstring_convert<codecvt_utf8<wchar_t>> towstring;
	return towstring.from_bytes(encoded);
}

void Save(const string& filename, const BufferedTransformation& bt)
{
	// http://www.cryptopp.com/docs/ref/class_file_sink.html
	FileSink file(filename.c_str());

	bt.CopyTo(file);
	file.MessageEnd();
}
void SavePrivateKey(const string& filename, const PrivateKey& key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;
	key.Save(queue);

	Save(filename, queue);
}


void SavePublicKey(const string& filename, const PublicKey& key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;
	key.Save(queue);

	Save(filename, queue);
}


void Load(const string& filename, BufferedTransformation& bt)
{
	// http://www.cryptopp.com/docs/ref/class_file_source.html
	FileSource file(filename.c_str(), true /*pumpAll*/);

	file.TransferTo(bt);
	bt.MessageEnd();
}

void LoadPrivateKey(const string& filename, PrivateKey& key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;

	Load(filename, queue);
	key.Load(queue);	
}
void LoadPublicKey(const string& filename, PublicKey& key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;

	Load(filename, queue);
	key.Load(queue);	
}
// this function use to encrypt the plaintext
void encrypt(int choiceTypeOfInput)
{
	AutoSeededRandomPool prng;
	RSA::PrivateKey privateKey;
	RSA::PublicKey publicKey;
	string plaintext;
	wstring wplaintext;

	wcout << L"----------------------------------------------------------------" << endl;

	// get the key from file and validate the key
	getKeyFromFileAndValidate(privateKey, publicKey);

	// get input from file or keyboard

	if (choiceTypeOfInput == 1)
	{

	#ifdef _WIN32
			plaintext = getPlaintextFromFile(".\\plaintext.txt");
	#elif __linux__
			plaintext = getPlaintextFromFile("./plaintext.txt");
	#endif
			wplaintext = s2ws(plaintext);
	}

	else if (choiceTypeOfInput == 2)
	{
		wcout << L"Input Plaintext: ";
		fflush(stdin);
		getline(wcin, wplaintext);
		plaintext = ws2s(wplaintext);
	}
	else
	{
		wcout << L"Invalid choice!" << endl;
		exit(1);
	}

	// encrypt the plaintext

	string ciphertext;

	ciphertext = rsaEncrypt(prng, publicKey, plaintext);
	saveCiphertextToFile(".\\ciphertext.txt", BeautifulPrinterForFileString(ciphertext));

	wcout << L"----------------------------------------------------------------" << endl;
	wcout << L"RSA Encryption: " << endl;
	wcout << L"Plaintext: " << wplaintext << endl;
	wcout << L"Ciphertext: ";
	BeautifulPrinter(ciphertext);
	wcout << L"----------------------------------------------------------------" << endl;
}

// this function use to decrypt the ciphertext
void decrypt(int choiceTypeOfInput)
{
	// declare variables
	AutoSeededRandomPool prng;
	RSA::PrivateKey privateKey;
	RSA::PublicKey publicKey;
	string ciphertext;
	wstring wciphertext;

	wcout << L"----------------------------------------------------------------" << endl;
	getKeyFromFileAndValidate(privateKey, publicKey);

	// get input from file or keyboard

	if (choiceTypeOfInput == 1)
	{

	#ifdef _WIN32
			ciphertext = getCiphertextFromFile(".\\ciphertext.txt");
	#elif __linux__
			ciphertext = getCiphertextFromFile("./ciphertext.txt");
	#endif
			wciphertext = s2ws(ciphertext);
			ciphertext = decodeCiphertext(wciphertext);
	}
	else if (choiceTypeOfInput == 2)
	{
		wcout << L"Input Cipher text: ";
		fflush(stdin);
		getline(wcin, wciphertext);
		if (wciphertext[wciphertext.size() - 1] != L'H')
		{
			wciphertext += L'H';
		}
		ciphertext = decodeCiphertext(wciphertext);
	}
	else
	{
		wcout << L"Invalid choice!" << endl;
		exit(1);
	}

	// decrypt the ciphertext

	string recovertext;

	recovertext = rsaDecrypt(prng, privateKey, ciphertext);

	wcout << L"----------------------------------------------------------------" << endl;
	wcout << L"RSA Decryption " << endl;
	wcout << L"Ciphertext: ";
	BeautifulPrinter(ciphertext);
	wcout << L"Recovertext: " << s2ws(recovertext) << endl;
	wcout << L"----------------------------------------------------------------" << endl;
}


void keygen()
{
	AutoSeededRandomPool rnd;
	RSA::PrivateKey rsaPrivate;
	
	rsaPrivate.GenerateRandomWithKeySize(rnd, 3072); // save in der or binary forrmat
	RSA::PublicKey rsaPublic(rsaPrivate);

	SavePrivateKey("rsaPrivate.key", rsaPrivate);
	SavePublicKey("rsaPublic.key", rsaPublic);
		
	RSA::PrivateKey r1, r2;
	r1.GenerateRandomWithKeySize(rnd, 3072);

	SavePrivateKey("rsaRoundtrip.key", r1);
	LoadPrivateKey("rsaRoundtrip.key", r2);

	r1.Validate(rnd, 3);
	r2.Validate(rnd, 3);

	if(r1.GetModulus() != r2.GetModulus() ||
	r1.GetPublicExponent() != r2.GetPublicExponent() ||
	r1.GetPrivateExponent() != r2.GetPrivateExponent())
	{
		throw runtime_error("key data did not round trip");
	}


	wcout << L"Successfully generated and saved RSA keys" << endl;
	RSA::PrivateKey rsaPrivate1;
	RSA::PublicKey rsaPublic1;


	LoadPrivateKey("rsaPrivate.key", rsaPrivate1);
	LoadPublicKey("rsaPublic.key", rsaPublic1);


	CryptoPP::Integer modul1 =rsaPrivate1.GetModulus();
	CryptoPP::Integer prime1=rsaPrivate1.GetPrime1();
	CryptoPP::Integer prime2=rsaPrivate1.GetPrime2();
	
	//    secrete exxponent d, public exxponent e
	CryptoPP::Integer SK=rsaPrivate1.GetPrivateExponent(); // secret exponent d; 
	CryptoPP::Integer PK= rsaPublic1.GetPublicExponent(); // public exponent e; 
	CryptoPP::Integer modul2= rsaPublic1.GetModulus(); // public exponent e; 
	wcout << L"\nModule n from public key n = " <<std::hex << integer_to_wstring(modul2) << endl; 
	wcout << L"\nModule n from private key n =" << std::hex << integer_to_wstring(modul1) << endl; 
	wcout << L"\nThe prime number p = " << std::hex << integer_to_wstring(prime1) << endl; 
	wcout << L"\nThe prime number q = "  << std::hex << integer_to_wstring(prime2) << endl; 
	wcout << L"\nSecret exponent d = " << std::hex << integer_to_wstring(SK)  << endl; 
	wcout << L"\nPublic exponent e = " << std::hex << integer_to_wstring(PK) << endl;
	wcout << L"\ncheck p.q mod n = " << integer_to_wstring(a_times_b_mod_c(prime1, prime2, modul1)) << endl;
}


void setUpVietnamese()
{
#ifdef _WIN32
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
#endif
}

int main()
{
	setUpVietnamese();
	int choiceEncDec = selectEncDec();
	

	if (choiceEncDec == 1)
	{
		keygen();

	}
	else if (choiceEncDec == 2)
	{	
		
		int choose = selectTypeOfInput();
		encrypt(choose);
	}
	else if (choiceEncDec == 3 )
	{
		int choose = selectTypeOfInput();
		decrypt(choose);
	}
	else wcout << L"Invalid choice!" << endl;

	return 0;
}