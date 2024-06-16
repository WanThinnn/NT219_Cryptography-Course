// Linux help: http://www.cryptopp.com/wiki/Linux

// Debug:
// g++ -g -ggdb -O0 -Wall -Wextra -Wno-unused -Wno-type-limits -I. -I/usr/include/cryptopp cryptopp-key-gen.cpp -o cryptopp-key-gen.exe -lcryptopp

// Release:
// g++ -O2 -Wall -Wextra -Wno-unused -Wno-type-limits -I. -I/usr/include/cryptopp cryptopp-key-gen.cpp -o cryptopp-key-gen.exe -lcryptopp && strip --strip-all cryptopp-key-gen.exe
#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <stdexcept>
using std::runtime_error;
#include "cryptopp/queue.h"
using CryptoPP::ByteQueue;

#include <cryptopp/files.h>
using CryptoPP::FileSource;
using CryptoPP::FileSink;


#include "cryptopp/rsa.h"
using CryptoPP::RSA;

#include "cryptopp/base64.h"
using CryptoPP::Base64Encoder;
using CryptoPP::Base64Decoder;

#include <cryptopp/cryptlib.h>
using CryptoPP::PrivateKey;
using CryptoPP::PublicKey;
using CryptoPP::BufferedTransformation;

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

void SavePrivateKey(const string& filename, const PrivateKey& key);
void SavePublicKey(const string& filename, const PublicKey& key);

void SaveBase64PrivateKey(const string& filename, const PrivateKey& key);
void SaveBase64PublicKey(const string& filename, const PublicKey& key);

void SaveBase64(const string& filename, const BufferedTransformation& bt);
void Save(const string& filename, const BufferedTransformation& bt);

void LoadPrivateKey(const string& filename, PrivateKey& key);
void LoadPublicKey(const string& filename, PublicKey& key);

void LoadBase64PrivateKey(const string& filename, PrivateKey& key);
void LoadBase64PublicKey(const string& filename, PublicKey& key);

void LoadBase64(const string& filename, BufferedTransformation& bt);
void Load(const string& filename, BufferedTransformation& bt);

int main(int argc, char** argv)
{
	// main part
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

	AutoSeededRandomPool rnd;


	RSA::PrivateKey rsaPrivate;
	rsaPrivate.GenerateRandomWithKeySize(rnd, 3072); // save in der or binary forrmat
		

	RSA::PublicKey rsaPublic(rsaPrivate);

	SavePrivateKey("rsa-private.der", rsaPrivate);
	SavePublicKey("rsa-public.der", rsaPublic);

	RSA::PrivateKey r1, r2;
	r1.GenerateRandomWithKeySize(rnd, 3072);

	SavePrivateKey("rsa-roundtrip.der", r1);
	LoadPrivateKey("rsa-roundtrip.der", r2);

	r1.Validate(rnd, 3);
	r2.Validate(rnd, 3);

	if(r1.GetModulus() != r2.GetModulus() ||
	r1.GetPublicExponent() != r2.GetPublicExponent() ||
	r1.GetPrivateExponent() != r2.GetPrivateExponent())
	{
		throw runtime_error("key data did not round trip");
	}
		
	

	cout << "Successfully generated and saved RSA keys" << endl;

	RSA::PrivateKey rsaPrivate1;
	RSA::PublicKey rsaPublic1;


	LoadPrivateKey("rsa-private.der", rsaPrivate1);
	LoadPublicKey("rsa-public.der", rsaPublic1);


	CryptoPP::Integer modul1 =rsaPrivate1.GetModulus();
	CryptoPP::Integer prime1=rsaPrivate1.GetPrime1();
	CryptoPP::Integer prime2=rsaPrivate1.GetPrime2();
	
	//    secrete exxponent d, public exxponent e
	CryptoPP::Integer SK=rsaPrivate1.GetPrivateExponent(); // secret exponent d; 
	CryptoPP::Integer PK= rsaPublic1.GetPublicExponent(); // public exponent e; 
	CryptoPP::Integer modul2= rsaPublic1.GetModulus(); // public exponent e; 
	cout << "\nModule n from public key n = " <<std::hex << modul2 << endl; 
	cout << "\nModule n from private key n =" << std::hex << modul1 << endl; 
	cout << "\nThe prime number p = " << std::hex << prime1 << endl; 
	cout << "\nThe prime number q = "  << std::hex << prime2 << endl; 
	cout << "\nSecret exponent d = " << std::hex << SK  << endl; 
	cout << "\nPublic exponent e = " << std::hex << PK << endl;
	cout << "\ncheck p.q mod n = " << a_times_b_mod_c(prime1, prime2, modul1) << endl;
	return 0; 
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

void Save(const string& filename, const BufferedTransformation& bt)
{
	// http://www.cryptopp.com/docs/ref/class_file_sink.html
	FileSink file(filename.c_str());

	bt.CopyTo(file);
	file.MessageEnd();
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

void SaveBase64(const string& filename, const BufferedTransformation& bt)
{
	// http://www.cryptopp.com/docs/ref/class_base64_encoder.html
	Base64Encoder encoder;

	bt.CopyTo(encoder);
	encoder.MessageEnd();

	Save(filename, encoder);
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

void Load(const string& filename, BufferedTransformation& bt)
{
	// http://www.cryptopp.com/docs/ref/class_file_source.html
	FileSource file(filename.c_str(), true /*pumpAll*/);

	file.TransferTo(bt);
	bt.MessageEnd();
}

void LoadBase64PrivateKey(const string& filename, PrivateKey& key)
{
	throw runtime_error("Not implemented");
}

void LoadBase64PublicKey(const string& filename, PublicKey& key)
{
	throw runtime_error("Not implemented");
}

void LoadBase64(const string& filename, BufferedTransformation& bt)
{
	throw runtime_error("Not implemented");
}