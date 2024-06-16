// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread



#include <locale>
#include <cctype>
#include "cryptopp/integer.h"
using CryptoPP::Integer;

#include <sstream>
using std::ostringstream;

#include "cryptopp/nbtheory.h"
using CryptoPP::ModularSquareRoot;

#include "cryptopp/modarith.h"
using CryptoPP::ModularArithmetic;;
// cryptopp
#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "cryptopp/cryptlib.h"
using CryptoPP::Exception;

#include "cryptopp/hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "cryptopp/base64.h"
using CryptoPP::Base64Encoder;
using CryptoPP::Base64Decoder;

#include "cryptopp/filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "cryptopp/des.h"
using CryptoPP::DES;

#include "cryptopp/modes.h"
using CryptoPP::CBC_Mode;

#include "cryptopp/secblock.h"
using CryptoPP::SecByteBlock;

// Standar C, cpp
#include <iomanip>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include <random>


// UTF-8
#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdlib>
#include <locale>
#include <cctype>

using namespace std;


string integer_to_string (const CryptoPP::Integer& t)
{
    std::ostringstream oss;
    oss.str("");
    oss.clear();
    oss << t;
    std::string encoded(oss.str());
    return encoded;
}

int main(int argc, char* argv[])
{
    // main part
	// Set locale to support UTF-8
	#ifdef __linux__
	std::locale::global(std::locale("C.utf8"));
	#endif
	#ifdef _WIN32
	// Set console code page to UTF-8 on Windows C.utf8, CP_UTF8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	#endif
    AutoSeededRandomPool prng;
    Integer x("988988984848448373736373748959483827372327327283832732723784438437427");

    Integer p("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2FH");

    Integer y(prng, 1, p);

    cout << "x = " << integer_to_string(x) << endl;
    cout << "y = " << integer_to_string(y) << endl;
    cout << "p = " <<integer_to_string(p) << endl;

    // compute mod p in Z_p
    ModularArithmetic ma(p); // mod p
    cout << "x+y mod p: " << ma.Add(x, y) << endl;
    cout << "x-y mod p: " << ma.Subtract(x, y) << endl;
    cout << "x*y mod p: " << ma.Multiply(x, y) << endl;
    cout << "x/y mod p: " << ma.Divide(x, y) << endl;
    cout << "x%y mod p: " << ma.Reduce(x, y) << endl;
    cout << "x^y mod p: " << ma.Exponentiate(x, y) << endl;
    
    Integer x1("19585692114440311621042896604212625392821833723283292396128832735.");
    cout << "x1=x^-1 mod p: " <<ma.Divide(1, x) << endl;
    cout << "x*x1 mod p: " << ma.Multiply(x, x1) << endl;

    //text to int
    cout << "Input your text: ";
    string text;

    getline(cin, text);
    string text_hex;
    StringSource (text, true, new HexEncoder(new StringSink(text_hex)));
    text_hex=text_hex+"H";


    Integer u(text_hex.data());


    cout << text_hex.data() << endl;

    cout << text << endl;
    cout << "Text to integer: " << u << endl;
    cout << "u mod p = " << u%p << endl;


	return 0;
}

