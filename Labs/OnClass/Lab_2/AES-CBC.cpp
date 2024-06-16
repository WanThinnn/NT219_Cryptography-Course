// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
using namespace std;
// Cryptopp lib

#include "include/cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "include/cryptopp/cryptlib.h"
using CryptoPP::Exception;

#include "include/cryptopp/hex.h"
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

#include "include/cryptopp/filters.h"
using CryptoPP::ArraySink;
using CryptoPP::ArraySource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include "include/cryptopp/aes.h"
using CryptoPP::AES;

#include "include/cryptopp/modes.h"
using CryptoPP::CBC_Mode;
using CryptoPP::CFB_Mode;

#include "include/cryptopp/files.h"
using CryptoPP::FileSink;
using CryptoPP::FileSource;

// #include "include/cryptopp/assert.h"

// Cpp library

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

// header part
#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdlib>
#include <locale>
#include <cctype>

int main(int argc, char *argv[])
{
// main part
// Set locale to support UTF-8
#ifdef _linux_
	std::locale::global(std::locale("C.utf8"));
#endif

#ifdef _WIN32
	// Set console code page to UTF-8 on Windows C.utf8, CP_UTF8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif

	cout << "Would you like to do?" << endl;
	cout << "1. Key generation" << endl;
	cout << "2. Encryption data" << endl;
	cout << "3. Decryption data" << endl;
	int actions;
	cin >> actions;
	string encoded;
	AutoSeededRandomPool prng;

	switch (actions)
	{
	case 1:
	{
		CryptoPP::byte key[AES::DEFAULT_KEYLENGTH]; // Key=128
		prng.GenerateBlock(key, sizeof(key));

		CryptoPP::byte iv[AES::BLOCKSIZE];
		prng.GenerateBlock(iv, sizeof(iv));

		// /*********************************
		// \*********************************/

		// Pretty print key
		encoded.clear();

		// save key
		encoded.clear();

		StringSource(key, sizeof(key), true,
					 //  new HexEncoder(
					 new FileSink("key.bin") // HexEncoder
		);									 // StringSource
		cout << "key: " << encoded << endl;

		// Pretty print iv
		encoded.clear();
		StringSource(iv, sizeof(iv), true,
					 //  new HexEncoder(
					 new FileSink("iv.bin") // HexEncoder
		);									// StringSource
		cout << "iv: " << encoded << endl;
		break;
	}
	case 2:
	{
		string plain = "Thuc hanh 2";
		string cipher;
		cout << "plain text: " << plain << endl;
		// load key
		encoded.clear();
		CryptoPP::byte key[AES::DEFAULT_KEYLENGTH]; // Key=128

		FileSource("key.bin", true,
				   //  new HexEncoder(
				   new ArraySink(key, sizeof(key)), true // HexEncoder
		);												 // StringSource
		cout << "key: " << encoded << endl;
		// prng.GenerateBlock(key, sizeof(key));

		// prng.GenerateBlock(iv, sizeof(iv));
		// load iv
		encoded.clear();
		CryptoPP::byte iv[AES::BLOCKSIZE];

		FileSource("iv.bin", true,
				   //  new HexEncoder(
				   new ArraySink(iv, sizeof(iv)), true // HexEncoder
		);											   // StringSource
		cout << "iv: " << encoded << endl;

		CBC_Mode<AES>::Encryption e;
		e.SetKeyWithIV(key, sizeof(key), iv);

		StringSource(plain, true,
					 new StreamTransformationFilter(e,
													new StringSink(cipher)) // StreamTransformationFilter
		);																	// StringSource

		encoded.clear();
		StringSource(cipher, true,
					 new HexEncoder(
						 new StringSink(encoded)) // HexEncoder
		);										  // StringSource
		cout << "cipher text (hex): " << encoded << endl;
		break;

		// ,
	}
	case 3:
	{
		string cipher, recovered;
		CryptoPP::byte key[AES::DEFAULT_KEYLENGTH]; // Key=128
		prng.GenerateBlock(key, sizeof(key));

		CryptoPP::byte iv[AES::BLOCKSIZE];
		prng.GenerateBlock(iv, sizeof(iv));
		CBC_Mode<AES>::Decryption d;
		d.SetKeyWithIV(key, sizeof(key), iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource(cipher, true,
					 new StreamTransformationFilter(d,
													new StringSink(recovered)) // StreamTransformationFilter
		);																	   // StringSource

		cout << "recovered text: " << recovered << endl;
	}
	}

	/*********************************\
	\*********************************/

	// try
	// {

	// The StreamTransformationFilter removes
	//  padding as required.

	// #if 0
	// 		StreamTransformationFilter filter(e);
	// 		filter.Put((const byte*)plain.data(), plain.size());
	// 		filter.MessageEnd();

	// 		const size_t ret = filter.MaxRetrievable();
	// 		cipher.resize(ret);
	// 		filter.Get((byte*)cipher.data(), cipher.size());
	// #endif
	// 	}
	// 	catch (const CryptoPP::Exception &e)
	// 	{
	// 		cerr << e.what() << endl;
	// 		exit(1);
	// 	}

	/*********************************\
	\*********************************/

	// Pretty print

	/*********************************\
	\*********************************/

	/*********************************\
	\*********************************/

	return 0;
}