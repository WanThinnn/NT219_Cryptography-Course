// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
// Declare functions with extern "C" to prevent name mangling in C++
#ifndef DLL_EXPORT
#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport) //define class specifier
#else
#define DLL_EXPORT
#endif
#endif
extern "C"
{
    DLL_EXPORT void GenerateAndSaveIV_Keys(int KeySize, const char* KeyFormat, const char* KeyFileName);
    DLL_EXPORT void Encryption(const char* mode, const char* KeyFile, const char* KeyFormat, const char* PlaintextFile, const char* PlaintextFormat, const char* CipherFile, const char* CipherFormat);
    DLL_EXPORT void Decryption(const char* mode, const char* KeyFile, const char* KeyFormat, const char* RecoveredFile, const char* RecoveredFormat, const char* CipherFile, const char* CipherFormat);
}
// C/C++ Standard Libraries
// C/C++ Standard Libraries

#include <assert.h>

#include <iostream>
using std::string;

#include <stdio.h>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#include <stdexcept>
using std::runtime_error;

#include <chrono>

#include <string>
using std::string;

#include <exception>
using std::exception;

#include <sstream>

// Crypto++ Libraries
#include "cryptopp/base64.h"
using CryptoPP::Base64Decoder;
using CryptoPP::Base64Encoder;

#include "cryptopp/hex.h"
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

#include "cryptopp/cryptlib.h"
using CryptoPP::AuthenticatedSymmetricCipher;
using CryptoPP::BufferedTransformation;
using CryptoPP::DecodingResult;
using CryptoPP::Exception;
using CryptoPP::PrivateKey;
using CryptoPP::PublicKey;

#include "cryptopp/files.h"
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include "cryptopp/filters.h"
using CryptoPP::ArraySink;
using CryptoPP::AuthenticatedDecryptionFilter;
using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::HashVerificationFilter;
using CryptoPP::PK_DecryptorFilter;
using CryptoPP::PK_EncryptorFilter;
using CryptoPP::Redirector;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "cryptopp/queue.h"
using CryptoPP::ByteQueue;

#include "cryptopp/secblock.h"
using CryptoPP::SecByteBlock;

// DES Libary
#include "cryptopp/aes.h"
using CryptoPP::AES;

// Confidentiality only modes
#include "cryptopp/modes.h"
using CryptoPP::CBC_Mode;
using CryptoPP::CFB_Mode;
using CryptoPP::CTR_Mode;
using CryptoPP::ECB_Mode;
using CryptoPP::OFB_Mode;

// Confidentiality and Authentication modes
#include "cryptopp/ccm.h"
using CryptoPP::CCM;

#include "cryptopp/eax.h"
using CryptoPP::EAX;

#include "cryptopp/gcm.h"
using CryptoPP::GCM;

#include "cryptopp/xts.h"
using CryptoPP::XTS;
#include "cryptopp/ccm.h"
using CryptoPP::CCM;
#include "cryptopp/gcm.h"
using CryptoPP::GCM;

// Define platform-specific features
#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef _WIN32
#include <direct.h>  // For Windows
#define mkdir _mkdir // For Windows
#else
#include <sys/stat.h> // For Linux
#endif
void SaveKey(const string& filename, const CryptoPP::SecByteBlock& bt)
{
    StringSource ss(bt, bt.size(), true,
        new FileSink(filename.c_str(), true)); // StringSource
}

void SaveIV(const string& filename, const CryptoPP::SecByteBlock& bt)
{
    StringSource ss(bt, bt.size(), true,
        new FileSink(filename.c_str(), true)); // StringSource
}

void SaveKeyBase64(const string& filename, const CryptoPP::SecByteBlock& bt)
{
    StringSource ss(bt, bt.size(), true,
        new Base64Encoder(
            new FileSink(filename.c_str(), false)) // Base64Encoder
    );                                                         // StringSource
}

void SaveIVBase64(const string& filename, const CryptoPP::SecByteBlock& bt)
{
    StringSource ss(bt, bt.size(), true,
        new Base64Encoder(
            new FileSink(filename.c_str(), false)) // Base64Encoder
    );                                                         // StringSource
}

void SaveKeyHex(const string& filename, const CryptoPP::SecByteBlock& bt)
{
    StringSource ss(bt, bt.size(), true,
        new HexEncoder(
            new FileSink(filename.c_str(), false)) // HexEncoder
    );                                                         // StringSource
    // HexEncoder encoder(new FileSink(filename.c_str(), false)); // HexEncoder
    // encoder.Put(bt, bt.size());
    // encoder.MessageEnd();
}

void SaveIVHex(const string& filename, const CryptoPP::SecByteBlock& bt)
{
    StringSource ss(bt, bt.size(), true,
        new HexEncoder(
            new FileSink(filename.c_str(), false)) // HexEncoder
    );
    // HexEncoder encoder(new FileSink(filename.c_str(), false)); // HexEncoder
    // encoder.Put(bt, bt.size());
    // encoder.MessageEnd();
}

// Load key & iv
void LoadKey(const string& filename, CryptoPP::SecByteBlock& bt)
{
    FileSource fs(filename.c_str(), true,
        new ArraySink(bt, bt.size()), true); // FileSource
}

void LoadIV(const string& filename, CryptoPP::SecByteBlock& bt)
{
    FileSource fs(filename.c_str(), true,
        new ArraySink(bt, bt.size()), true); // FileSource
}

void LoadKeyBase64(const string& filename, CryptoPP::SecByteBlock& bt)
{
    FileSource fs(filename.c_str(), true,
        new Base64Decoder(
            new ArraySink(bt, bt.size())) /*Base64Decoder*/,
        false); // FileSource
}

void LoadIVBase64(const string& filename, CryptoPP::SecByteBlock& bt)
{
    FileSource fs(filename.c_str(), true,
        new Base64Decoder(
            new ArraySink(bt, bt.size())) /*Base64Decoder*/,
        false);
}
void LoadKeyHex(const string& filename, CryptoPP::SecByteBlock& bt)
{
    FileSource fs(filename.c_str(), true,
        new HexDecoder(
            new ArraySink(bt, bt.size())) /*Base64Decoder*/,
        false); // FileSource
}

void LoadIVHex(const string& filename, CryptoPP::SecByteBlock& bt)
{
    FileSource fs(filename.c_str(), true,
        new HexDecoder(
            new ArraySink(bt, bt.size())) /*Base64Decoder*/,
        false);
}

string standardizeString(const char* mode)
{
    string result = mode;
    bool isLowerCase = true;

    // Kiểm tra xem tất cả các ký tự có phải là chữ cái viết thường không
    for (char c : result)
    {
        if (isalpha(c) && isupper(c))
        {
            isLowerCase = false;
            break;
        }
    }

    // Nếu tất cả các ký tự đều viết thường, chuyển đổi thành chữ in hoa
    if (isLowerCase)
    {
        transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
            { return std::toupper(c); });
    }

    return result;
}

size_t GetKeySizeFromFile(const std::string& filename, const std::string& format)
{
    size_t keySize = 0;

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    // Xác định độ dài của key dựa trên định dạng
    if (format == "Base64")
    {
        std::string key;
        StringSource(buffer.str(), true, new Base64Decoder(new StringSink(key)));
        keySize = key.size() * 8; // Đổi từ byte sang bit
    }
    else if (format == "HEX")
    {
        keySize = buffer.str().size() * 4; // Mỗi ký tự HEX biểu diễn 4 bit
    }
    else if (format == "DER")
    {
        keySize = buffer.str().size() * 8; // Đổi từ byte sang bit
    }
    else
    {
        cerr << "Unsupported format: " << format << std::endl;
        exit(1);
    }

    return keySize;
}

bool createDirectory(const std::string& directory)
{
#ifdef _WIN32
    int result = _mkdir(directory.c_str()); // Sử dụng _mkdir cho Windows
#else
    int result = mkdir(directory.c_str(), 0777); // Sử dụng mkdir cho Linux
#endif

    if (result == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Generate and save keys
void GenerateAndSaveIV_Keys(const int KeySize, const char* KeyFormat, const char* KeyFileName)
{
    AutoSeededRandomPool prng;
    string strKeyFormat(KeyFormat);
    string strKeyFileName(KeyFileName);

    // Generate key & iv
    CryptoPP::SecByteBlock key(KeySize);
    prng.GenerateBlock(key, key.size());

    CryptoPP::SecByteBlock iv(AES::BLOCKSIZE);
    prng.GenerateBlock(iv, iv.size());

    // Save key & iv
    if (strKeyFormat == "DER")
    {
        SaveKey( strKeyFileName, key);
        SaveIV("iv.bin", iv);
    }
    else if (strKeyFormat == "Base64")
    {
        SaveKeyBase64( strKeyFileName, key);
        SaveIVBase64("iv.pem", iv);
    }
    else if (strKeyFormat == "HEX")
    {
        SaveKeyHex( strKeyFileName, key);
        SaveIVHex("iv.hex", iv);
    }
    else
    {
        cerr << "Unsupported key format. Please choose 'DER', 'Base64', or 'HEX'\n";
        exit(1);
    }
    cout << "----------------------------------------------------------" << endl;
    cout << "Successfully generate Key and IV! Key and IV saved to: " << strKeyFileName << " and iv.{format}!" << endl;
    cout << "----------------------------------------------------------" << endl;
}
// Encryption
void Encryption(const char* mode, const char* KeyFile, const char* KeyFormat, const char* PlaintextFile, const char* PlaintextFormat, const char* CipherFile, const char* CipherFormat)
{
    string strMode = standardizeString(mode);
    string strKeyFormat(KeyFormat);
    string strKeyFile(KeyFile);
    string strPlaintextFormat(PlaintextFormat);
    string strCipherFormat(CipherFormat);

    size_t KeySize = GetKeySizeFromFile( strKeyFile, strKeyFormat);
    KeySize /= 8;

    // Load key & iv
    CryptoPP::SecByteBlock key(KeySize);

    CryptoPP::SecByteBlock iv(AES::BLOCKSIZE);
    if (strMode == "CBC" || strMode == "CFB" || strMode == "OFB" || strMode == "CTR" || strMode == "GCM" || strMode == "CCM" || strMode == "XTS")
    {
        if (strKeyFormat == "DER")
        {
            LoadKey( strKeyFile, key);
            LoadIV("iv.bin", iv);
        }
        else if (strKeyFormat == "Base64")
        {
            LoadKeyBase64( strKeyFile, key);
            LoadIVBase64("iv.pem", iv);
        }
        else if (strKeyFormat == "HEX")
        {
            LoadKeyHex( strKeyFile, key);
            LoadIVHex("iv.hex", iv);
        }

        else
        {
            cerr << "Unsupported key format. Please choose 'DER', 'Base64' or 'HEX'!\n";
            exit(1);
        }
    }
    else if (strMode == "ECB")
    {
        if (strKeyFormat == "DER")
        {
            LoadKey( strKeyFile, key);
        }
        else if (strKeyFormat == "Base64")
        {
            LoadKeyBase64( strKeyFile, key);
        }
        else if (strKeyFormat == "HEX")
        {
            LoadKeyHex( strKeyFile, key);
        }
        else
        {
            cerr << "Unsupported key format. Please choose 'DER', 'Base64' or 'HEX'!\n";
            exit(1);
        }
    }

    else if (strMode == "XTS")
    {
        if (KeySize < 32)
        {
            cerr << "Độ dài của key không đủ để encrypt XTS\n";
        }
        else
        {
            if (strKeyFormat == "DER")
            {
                LoadKey( strKeyFile, key);
                LoadIV("iv.bin", iv);
            }
            else if (strKeyFormat == "Base64")
            {
                LoadKeyBase64( strKeyFile, key);
                LoadIVBase64("iv.pem", iv);
            }
            else if (strKeyFormat == "HEX")
            {
                LoadKeyHex( strKeyFile, key);
                LoadIVHex("iv.hex", iv);
            }

            else
            {
                cerr << "Unsupported key format. Please choose 'DER', 'Base64' or 'HEX'!\n";
                exit(1);
            }
        }
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

    // Encryption
    string cipher;
    if (strMode == "ECB")
    {
        ECB_Mode<AES>::Encryption e;
        e.SetKey(key, key.size());

        StringSource ss(plain, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher)));
    }
    else if (strMode == "CBC")
    {
        CBC_Mode<AES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(plain, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher)));
    }
    else if (strMode == "CFB")
    {
        CFB_Mode<AES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(plain, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher)));
    }
    else if (strMode == "OFB")
    {
        OFB_Mode<AES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(plain, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher)));
    }
    else if (strMode == "CTR")
    {
        CTR_Mode<AES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(plain, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher)));
    }
    else if (strMode == "GCM")
    {
        const int TAG_SIZE = 12;
        GCM<AES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource ss1(plain, true,
            new AuthenticatedEncryptionFilter(e,
                new StringSink(cipher), false, TAG_SIZE) // AuthenticatedEncryptionFilter
        );                                                                                          // StringSource
    }
    else if (strMode == "CCM")
    {
        const int TAG_SIZE = 8;
        CCM<AES, TAG_SIZE>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);
        e.SpecifyDataLengths(0, plain.size(), 0);

        StringSource ss(plain, true,
            new AuthenticatedEncryptionFilter(e,
                new StringSink(cipher)));
    }
    else if (strMode == "XTS")
    {
        XTS<AES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(plain, true,
            new StreamTransformationFilter(e,
                new StringSink(cipher)));
    }
    else
    {
        cerr << "Unsupported mode. Please choose: 'ECB', 'CBC', 'CFB', 'OFB', 'CTR', 'GCM', 'CCM', 'XTS'!\n";
        exit(1);
    }

    // Save cipher
    if (strCipherFormat == "DER")
    {
        StringSource(cipher, true,
            new FileSink(CipherFile, true));
    }
    else if (strCipherFormat == "Base64")
    {
        StringSource(cipher, true,
            new Base64Encoder(
                new FileSink(CipherFile, false)));
    }
    else if (strCipherFormat == "HEX")
    {
        StringSource(cipher, true,
            new HexEncoder(
                new FileSink(CipherFile, false)));
    }
    else
    {
        cerr << "Unsupported cipher format. Please choose 'DER', 'Base64' or 'HEX'\n";
        exit(1);
    }

    // cout << "----------------------------------------------------------" << endl;
    // cout << "Encryption successful. Cipher text saved to: " << CipherFile << endl;
    // cout << "----------------------------------------------------------" << endl;
}

// Decryption
void Decryption(const char* mode, const char* KeyFile, const char* KeyFormat, const char* RecoveredFile, const char* RecoveredFormat, const char* CipherFile, const char* CipherFormat)
{
    string strMode = standardizeString(mode);
    string strKeyFile(KeyFile);

    string strKeyFormat = standardizeString(KeyFormat);
    string strPlaintextFormat(RecoveredFormat);
    string strCipherFormat(CipherFormat);

    size_t KeySize = GetKeySizeFromFile( strKeyFile, strKeyFormat);

    // Load key & iv
    CryptoPP::SecByteBlock key(KeySize / 8);
    CryptoPP::SecByteBlock iv(AES::BLOCKSIZE);

    if (strMode == "CBC" || strMode == "CFB" || strMode == "OFB" || strMode == "CTR" || strMode == "GCM" || strMode == "CCM" || strMode == "XTS")
    {
        if (strKeyFormat == "DER")
        {
            LoadKey( strKeyFile, key);
            LoadIV("iv.bin", iv);
        }
        else if (strKeyFormat == "Base64")
        {
            LoadKeyBase64( strKeyFile, key);
            LoadIVBase64("iv.pem", iv);
        }
        else if (strKeyFormat == "HEX")
        {
            LoadKeyHex( strKeyFile, key);
            LoadIVHex("iv.hex", iv);
        }
        else
        {
            cerr << "Unsupported key format. Please choose 'DER', 'Base64' or 'HEX'!\n";
            exit(1);
        }
    }
    else if (strMode == "ECB")
    {
        if (strKeyFormat == "DER")
        {
            LoadKey( strKeyFile, key);
        }
        else if (strKeyFormat == "Base64")
        {
            LoadKeyBase64( strKeyFile, key);
        }
        else if (strKeyFormat == "HEX")
        {
            LoadKeyHex( strKeyFile, key);
        }
        else
        {
            cerr << "Unsupported key format. Please choose 'DER', 'Base64' or 'HEX'!\n";
            exit(1);
        }
    }
    // Load cipher
    string cipher;
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

    // Decryption
    string recovered;
    if (strMode == "ECB")
    {
        ECB_Mode<AES>::Decryption d;
        d.SetKey(key, key.size());

        StringSource ss(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)));
    }
    else if (strMode == "CBC")
    {
        CBC_Mode<AES>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)));
    }
    else if (strMode == "CFB")
    {
        CFB_Mode<AES>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)));
    }
    else if (strMode == "OFB")
    {
        OFB_Mode<AES>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)));
    }
    else if (strMode == "CTR")
    {
        CTR_Mode<AES>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)));
    }
    else if (strMode == "GCM")
    {
        GCM<AES>::Decryption d;
        const int TAG_SIZE = 12;
        d.SetKeyWithIV(key, key.size(), iv);

        AuthenticatedDecryptionFilter df(d,
            new StringSink(recovered),
            AuthenticatedDecryptionFilter::DEFAULT_FLAGS, TAG_SIZE); // AuthenticatedDecryptionFilter

        StringSource ss2(cipher, true,
            new Redirector(df)); // StringSource

        if (true == df.GetLastResult())
        {
            // cout << "Verified data." << endl
            //      << endl;
        }
        else
        {
            cout << "Failed to verify data." << endl
                << endl;
        }
    }
    else if (strMode == "CCM")
    {
        const int TAG_SIZE = 8;
        CCM<AES, TAG_SIZE>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);
        d.SpecifyDataLengths(0, cipher.size() - TAG_SIZE, 0);

        AuthenticatedDecryptionFilter df(d,
            new StringSink(recovered));
        StringSource ss(cipher, true,
            new Redirector(df));

        if (true == df.GetLastResult())
        {
            // cout << "Verified data." << endl
            //      << endl;
        }
        else
        {
            cout << "Failed to verify data." << endl
                << endl;
        }
    }
    else if (strMode == "XTS")
    {
        XTS<AES>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(cipher, true,
            new StreamTransformationFilter(d,
                new StringSink(recovered)));
    }

    else
    {
        cerr << "Unsupported mode. Please choose: 'ECB', 'CBC', 'CFB', 'OFB', 'CTR', 'GCM', 'CCM', 'XTS'!\n";
        exit(1);
    }

    // Save recovered
    if (strPlaintextFormat == "Text")
    {
        StringSource(recovered, true,
            new FileSink(RecoveredFile, false));
    }
    else if (strPlaintextFormat == "DER")
    {
        StringSource(recovered, true,
            new FileSink(RecoveredFile, true));
    }
    else if (strPlaintextFormat == "Base64")
    {
        StringSource(recovered, true,
            new Base64Encoder(
                new FileSink(RecoveredFile, false)));
    }
    else if (strPlaintextFormat == "HEX")
    {
        StringSource(recovered, true,
            new HexEncoder(
                new FileSink(RecoveredFile, false)));
    }
    else
    {
        cerr << "Unsupported recovery text format. Please choose 'text', 'DER', 'Base64' or 'HEX'!\n";
        exit(1);
    }

    // cout << "----------------------------------------------------------" << endl;
    // cout << "Decryption successful! Plaintext saved to: " << RecoveredFile << endl;
    // cout << "----------------------------------------------------------" << endl;
}

// Hàm để lấy kích thước của một tệp
std::streamsize getFileSize(const std::string& filename)
{
    // Mở tệp
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1; // Trả về -1 nếu có lỗi
    }

    // Lấy kích thước tệp
    std::streamsize size = file.tellg();
    file.close();

    return size;
}
void ProcessInput(const string& action, int argc, char* argv[])
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
        GenerateAndSaveIV_Keys(KeySize / 8, argv[3], argv[4]);
    }
    else if (action == "encrypt")
    {
        if (argc != 9)
        {
            cerr << "Usage: " << argv[0] << " encrypt <Mode> <KeyFile> <KeyFileFormat> <PlaintextFile> <PlaintextFormat> <CipherFile> <CipherFormat>" << endl;
            return;
        }

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++)
        {
            Encryption(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        string plaintextFile = argv[5];
        string ciphertextFile = argv[7];
        std::streamsize plain = getFileSize(plaintextFile);
        std::streamsize cipher = getFileSize(ciphertextFile);

        // cout << "\n----------------------------------------------------------" << endl;
        cout << "Overview AES Encryption Test" << endl;
        cout << "Mode: " << argv[2] << endl;
        cout << "Plaintext file: " << plaintextFile << endl;
        cout << "Size of plaintext file: " << plain << " bytes" << endl;
        cout << "Ciphertext file: " << ciphertextFile << endl;
        cout << "Size of ciphertext file: " << cipher << " bytes" << endl;
        cout << "Encryption time: " << duration.count() << " milliseconds" << endl;
        cout << "----------------------------------------------------------" << endl;

        cout.flush(); // Đảm bảo dữ liệu được ghi vào cout sẽ được xuất ra màn hình ngay lập tức
    }
    else if (action == "decrypt")
    {
        if (argc != 9)
        {
            cerr << "Usage: " << argv[0] << " decrypt <Mode> <KeyFile> <KeyFileFormat> <RecoveredFile> <RecoveredFileFormat> <CipherFile> <CipherFormat>" << endl;
            return;
        }

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++) {
            Decryption(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        string rcvTextFile = argv[5];
        std::streamsize rcv = getFileSize(rcvTextFile);

        string ciphertextFile = argv[7];
        std::streamsize cipher = getFileSize(ciphertextFile);
        // cout << "----------------------------------------------------------" << endl;
        cout << "Overview AES Decryption Test" << endl;
        cout << "Mode: " << argv[2] << endl;
        cout << "Ciphertext file: " << ciphertextFile << endl;
        cout << "Size of cipher text file: " << cipher << " bytes" << endl;
        cout << "Recovered text file: " << rcvTextFile << endl;
        cout << "Size of recovered text file: " << rcv << " bytes" << endl;
        cout << "Decryption time: " << duration.count() << " milliseconds" << endl;
        cout << "----------------------------------------------------------" << endl;

        cout.flush(); // Đảm bảo dữ liệu được ghi vào cout sẽ được xuất ra màn hình ngay lập tức
    }
    else
    {
        cerr << "Invalid action. Please choose 'genkey', 'encrypt', or 'decrypt'." << endl;
    }
}

int main(int argc, char* argv[])
{
    // Set UTF-8 Encoding
    // Set locale to support UTF-8
#ifdef _linux_
    std::locale::global(std::locale("C.utf8"));
#endif
#ifdef _WIN32
    // Set console code page to UTF-8 on Windows C.utf8, CP_UTF8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::ios_base::sync_with_stdio(false);

    if (argc < 2)
    {
        cerr << "Invalid arguments. Please follow the instructions:\n";

        cerr << "Usage:\n"
            << "\t" << argv[0] << " genkey <KeySize> <KeyFileFormat> <KeyFile>\n"
            << "\t" << argv[0] << " encrypt <Mode> <KeyFile> <KeyFileFormat> <PlaintextFile> <PlaintextFormat> <CipherFile> <CipherFormat>\n"
            << "\t" << argv[0] << " decrypt <Mode> <KeyFile> <KeyFileFormat> <RecoveredFile> <RecoveredFileFormat> <CipherFile> <CipherFormat>\n"
            << "Note:\n"
            << "\tKeySize represents the size of the key in bits (128, 192, 256, 512(only XTS))\n"
            << "\tMode options: 'ECB', 'CBC', 'CFB', 'OFB', 'CTR', 'GCM', 'CCM', 'XTS' (>=256)\n"
            << "\tOutputFormat options: 'DER', 'Base64', 'HEX'\n"
            << "\tKeyFormat & CiphertextFormat options: 'DER', 'Base64', 'HEX'\n"
            << "\tPlaintextFormat & RecoveredFormat options: 'Text', 'DER', 'Base64', 'HEX'\n\n"
            << "Example:\n"
            << "\t" << argv[0] << " genkey 256 Base64 key.pem\n"
            << "\t" << argv[0] << " encrypt CBC key.pem Base64 plain.txt Text cipher.pem Base64\n"
            << "\t" << argv[0] << " decrypt CBC key.pem Base64 recovered.txt Text cipher.pem Base64\n";

        return -1;
    }

    string action = argv[1];

    ProcessInput(action, argc, argv);

    return 0;
}