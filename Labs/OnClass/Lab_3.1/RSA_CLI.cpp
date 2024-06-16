// C/C++ libraries
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <string>
using std::exit;
#include <cstdlib>
using std::string;

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

// Save (BER-BIN) key to file
void Save(const string &filename, const BufferedTransformation &bt);
void SavePrivateKey(const string &filename, const PrivateKey &key);
void SavePublicKey(const string &filename, const PublicKey &key);

// Save (BER)
void SaveBase64(const string &filename, const BufferedTransformation &bt);
void SaveBase64PrivateKey(const string &filename, const PrivateKey &key);
void SaveBase64PublicKey(const string &filename, const PublicKey &key);

void Load(const string &filename, BufferedTransformation &bt);
void LoadPrivateKey(const string &filename, PrivateKey &key);
void LoadPublicKey(const string &filename, PublicKey &key);

// Load BER_BASE64
void LoadBase64(const string &filename, BufferedTransformation &bt);
void LoadBase64PrivateKey(const string &filename, PrivateKey &key);
void LoadBase64PublicKey(const string &filename, PublicKey &key);

// RSA keys generation
void GenerationAndSaveRSAKeys(int keySize, const char *format, const char *privateKeyFile, const char *publicKeyFile)
{

	string strFormat(format);
	string strPrivateKeyFile(privateKeyFile);
	string strPublicKeyFile(publicKeyFile);
	AutoSeededRandomPool rnd;

	// General private key
	RSA::PrivateKey rsaPrivate;
	rsaPrivate.GenerateRandomWithKeySize(rnd, keySize); // tao RSA

	// General public key
	RSA::PublicKey rsaPublic(rsaPrivate);

	if (strFormat == "DER")
	{

		// Save keys to file (BIN)
		SavePrivateKey(strPrivateKeyFile, rsaPrivate);
		SavePublicKey(strPublicKeyFile, rsaPublic);
	}
	else if (strFormat == "Base64")
	{
		// Save keys to file (BASE64)
		SaveBase64PrivateKey(strPrivateKeyFile, rsaPrivate);
		SaveBase64PublicKey(strPublicKeyFile, rsaPublic);
	}
	else
	{
		cerr << "Unsupported format. Please choose 'DER, 'Base64'." << endl;
		exit(1);
	}

	// Integer modul1 = rsaPrivate.GetModulus();
	// Integer prime1 = rsaPrivate.GetPrime1();
	// Integer prime2 = rsaPrivate.GetPrime2();
	// Integer SK = rsaPrivate.GetPrivateExponent();

	// Integer PK = rsaPublic.GetPublicExponent();
	// Integer modul2 = rsaPublic.GetModulus();
	// cout<<"Modulo (private) n= "<<modul1<<endl;
	// cout<<"Modulo (public) n= "<<modul2<<endl;
	// cout<<"Prime number 1 (private) p= "<<std::hex<<prime1<<std::dec<<endl;
	// cout<<"Prime number 2 (private) q= "<<std::hex<<prime2<<std::dec<<endl;
	// cout<<"Secret exponent d= "<<SK<<endl;
	// cout<<"Public exponent e= "<<PK<<endl;

	// //Checking the key generator function
	// RSA::PrivateKey r1, r2;
	// r1.GenerateRandomWithKeySize(rnd, 3072);

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

	cout << "Successfully generated and saved RSA keys" << endl;
}

// encrypt
void RSAencrypt(const char *format, const char *publicKeyFile, const char *PlaintextFile, const char *CipherFile)
{
	RSA::PrivateKey privateKey;
	RSA::PublicKey publicKey;
	AutoSeededRandomPool rnd;
	string strFormatt(format);
	string strpublicKeyFile(publicKeyFile);
	// load key from files
	if (strFormatt == "DER")
	{
		LoadPublicKey(strpublicKeyFile, publicKey);
	}
	else if (strFormatt == "Base64")
	{
		LoadBase64PublicKey(strpublicKeyFile, publicKey);
	}
	else
	{
		cout << "Key format unsupported!" << endl;
	}

	string plain, cipher;

	FileSource(PlaintextFile, true, new StringSink(plain), false);
	// khai bao ham encryption
	// Encryption
	RSAES_OAEP_SHA_Encryptor e(publicKey);

	StringSource(plain, true,
				 new PK_EncryptorFilter(rnd, e,
										new FileSink(CipherFile, true)) // PK_EncryptorFilter
	);

	cout << "Successfully encrypt in CipherFile: " << CipherFile << endl;
}

// decrypt
void RSAdecrypt(const char *format, const char *privateKeyFile, const char *CipherFile, const char *PlaintextFile)
{
	RSA::PrivateKey privateKey;
	RSA::PublicKey publicKey;
	AutoSeededRandomPool rnd;
	string strFormatt(format);
	string strprivateKeyFile(privateKeyFile);
	if (strFormatt == "DER")
	{
		LoadPrivateKey(strprivateKeyFile, privateKey);
	}
	else if (strFormatt == "Base64")
	{
		LoadBase64PrivateKey(strprivateKeyFile, privateKey);
	}
	else
	{
		cout << "Key format unsupported!" << endl;
	}
	// Khởi tạo đối tượng để giải mã RSA
	RSAES_OAEP_SHA_Decryptor d(privateKey);

	string recover, cipher;

	// Đọc dữ liệu đã mã hóa từ tệp CipherFile
	FileSource(CipherFile, true, new StringSink(cipher));

	// Giải mã dữ liệu
	StringSource(cipher, true,
				 new PK_DecryptorFilter(rnd, d,
										new FileSink(PlaintextFile, true)) // PK_DecryptorFilter
	);

	cout << "Successfully decrypt in RecoveredFile: " << PlaintextFile << endl;
}

int main(int argc, char **argv)
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
			 << argv[0] << " genkey <keysize> <format> <privateKeyFile> <publicKeyFile>\n"
			 << argv[0] << " encrypt <format> <publicKeyFile> <plaintextFile> <cipherFile>\n"
			 << argv[0] << " decrypt <format> <privateKeyFile> <cipherFile> <plaintextFile>\n";
		return -1;
	}

	string mode = argv[1];

	if (mode == "genkey" && argc == 6)
	{
		int keySize = std::stoi(argv[2]);
		GenerationAndSaveRSAKeys(keySize, argv[3], argv[4], argv[5]);
	}
	else if (mode == "encrypt" && argc == 6)
	{
		RSAencrypt(argv[2], argv[3], argv[4], argv[5]);
	}
	else if (mode == "decrypt" && argc == 6)
	{
		RSAdecrypt(argv[2], argv[3], argv[4], argv[5]);
	}
	else
	{
		cerr << "Invalid arguments. Please check the usage instructions.\n";
		return -1;
	}

	return 0;
}

// encryption

// Def functions
/* ################################################################ */

void SavePrivateKey(const string &filename, const PrivateKey &key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;
	key.Save(queue);

	Save(filename, queue);
}

void SavePublicKey(const string &filename, const PublicKey &key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;
	key.Save(queue);

	Save(filename, queue);
}

void Save(const string &filename, const BufferedTransformation &bt)
{
	// http://www.cryptopp.com/docs/ref/class_file_sink.html
	FileSink file(filename.c_str());

	bt.CopyTo(file);
	file.MessageEnd();
}

void SaveBase64PrivateKey(const string &filename, const PrivateKey &key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;
	key.Save(queue);

	SaveBase64(filename, queue);
}

void SaveBase64PublicKey(const string &filename, const PublicKey &key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;
	key.Save(queue);

	SaveBase64(filename, queue);
}

void SaveBase64(const string &filename, const BufferedTransformation &bt)
{
	// http://www.cryptopp.com/docs/ref/class_base64_encoder.html
	Base64Encoder encoder;

	bt.CopyTo(encoder);
	encoder.MessageEnd();

	Save(filename, encoder);
}

void LoadPrivateKey(const string &filename, PrivateKey &key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;

	Load(filename, queue);
	key.Load(queue);
}

void LoadPublicKey(const string &filename, PublicKey &key)
{
	// http://www.cryptopp.com/docs/ref/class_byte_queue.html
	ByteQueue queue;

	Load(filename, queue);
	key.Load(queue);
}

void Load(const string &filename, BufferedTransformation &bt)
{
	// http://www.cryptopp.com/docs/ref/class_file_source.html
	FileSource file(filename.c_str(), true /*pumpAll*/);

	file.TransferTo(bt);
	bt.MessageEnd();
}

void LoadBase64PrivateKey(const string &filename, PrivateKey &key)
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

void LoadBase64PublicKey(const string &filename, PublicKey &key)
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
void LoadBase64(const string &filename, BufferedTransformation &bt)
{
	throw runtime_error("Not implemented");
}