// C/C++ Standard Libraries

#include <assert.h>

#include <iostream>

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

// Crypto++ Libraries
#include "cryptopp/base64.h"
using CryptoPP::Base64Decoder;
using CryptoPP::Base64Encoder;

#include "cryptopp/hex.h"
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

#include "cryptopp/cryptlib.h"
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
#include "cryptopp/des.h"
using CryptoPP::DES;

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

// Save key & iv

void SaveKey(const string &filename, const CryptoPP::SecByteBlock &bt)
{
    StringSource ss(bt, bt.size(), true,
                    new FileSink(filename.c_str(), true)); // StringSource
}

void SaveIV(const string &filename, const CryptoPP::SecByteBlock &bt)
{
    StringSource ss(bt, bt.size(), true,
                    new FileSink(filename.c_str(), true)); // StringSource
}

void SaveKeyBase64(const string &filename, const CryptoPP::SecByteBlock &bt)
{
    StringSource ss(bt, bt.size(), true,
                    new Base64Encoder(
                        new FileSink(filename.c_str(), false)) // Base64Encoder
    );                                                         // StringSource
}

void SaveIVBase64(const string &filename, const CryptoPP::SecByteBlock &bt)
{
    StringSource ss(bt, bt.size(), true,
                    new Base64Encoder(
                        new FileSink(filename.c_str(), false)) // Base64Encoder
    );                                                         // StringSource
}

void SaveKeyHex(const string &filename, const CryptoPP::SecByteBlock &bt)
{
    StringSource ss(bt, bt.size(), true,
                    new HexEncoder(
                        new FileSink(filename.c_str(), false)) // HexEncoder
    );                                                         // StringSource
    // HexEncoder encoder(new FileSink(filename.c_str(), false)); // HexEncoder
    // encoder.Put(bt, bt.size());
    // encoder.MessageEnd();
}

void SaveIVHex(const string &filename, const CryptoPP::SecByteBlock &bt)
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
void LoadKey(const string &filename, CryptoPP::SecByteBlock &bt)
{
    FileSource fs(filename.c_str(), true,
                  new ArraySink(bt, bt.size()), true); // FileSource
}

void LoadIV(const string &filename, CryptoPP::SecByteBlock &bt)
{
    FileSource fs(filename.c_str(), true,
                  new ArraySink(bt, bt.size()), true); // FileSource
}

void LoadKeyBase64(const string &filename, CryptoPP::SecByteBlock &bt)
{
    FileSource fs(filename.c_str(), true,
                  new Base64Decoder(
                      new ArraySink(bt, bt.size())) /*Base64Decoder*/,
                  false); // FileSource
}

void LoadIVBase64(const string &filename, CryptoPP::SecByteBlock &bt)
{
    FileSource fs(filename.c_str(), true,
                  new Base64Decoder(
                      new ArraySink(bt, bt.size())) /*Base64Decoder*/,
                  false);
}
void LoadKeyHex(const string &filename, CryptoPP::SecByteBlock &bt)
{
    FileSource fs(filename.c_str(), true,
                  new HexDecoder(
                      new ArraySink(bt, bt.size())) /*Base64Decoder*/,
                  false); // FileSource
}

void LoadIVHex(const string &filename, CryptoPP::SecByteBlock &bt)
{
    FileSource fs(filename.c_str(), true,
                  new HexDecoder(
                      new ArraySink(bt, bt.size())) /*Base64Decoder*/,
                  false);
}

string standardizeString(const char *mode)
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

bool createDirectory(const std::string &directory)
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
void GenerateAndSaveIV_Keys(const char *KeyFormat, const char *KeyFileName)
{

    AutoSeededRandomPool prng;
    string strKeyFormat = standardizeString(KeyFormat);
    string strKeyFileName(KeyFileName);

    // Generate key & iv
    CryptoPP::SecByteBlock key(DES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());

    CryptoPP::SecByteBlock iv(DES::BLOCKSIZE);
    prng.GenerateBlock(iv, iv.size());
    createDirectory("keys");
    // Save key & iv
    if (strKeyFormat == "DER")
    {
        SaveKey("./keys/" + strKeyFileName, key);
        SaveIV("./keys/iv.bin", iv);
    }
    else if (strKeyFormat == "Base64")
    {
        SaveKeyBase64("./keys/" + strKeyFileName, key);
        SaveIVBase64("./keys/iv.txt", iv);
    }
    else if (strKeyFormat == "HEX")
    {
        SaveKeyHex("./keys/" + strKeyFileName, key);
        SaveIVHex("./keys/iv.hex", iv);
    }
    else
    {
        cerr << "Unsupported key format. Please choose 'DER', 'Base64', or 'HEX'\n";
        exit(1);
    }
    cout << "----------------------------------------------------------" << endl;
    cout << "Successfully generate Key and IV! Key and IV saved to: " << strKeyFileName << " and iv.{your_choose_format}!" << endl;
    cout << "----------------------------------------------------------" << endl;
}

// Encryption
void Encryption(const char *mode, const char *KeyFile, const char *KeyFormat, const char *PlaintextFile, const char *PlaintextFormat, const char *CipherFile, const char *CipherFormat)
{
    string strMode = standardizeString(mode);
    string strKeyFormat = standardizeString(KeyFormat);
    string strKeyFile(KeyFile);
    string strPlaintextFormat(PlaintextFormat);
    string strCipherFormat(CipherFormat);

    // Load key & iv
    CryptoPP::SecByteBlock key(DES::DEFAULT_KEYLENGTH);
    CryptoPP::SecByteBlock iv(DES::BLOCKSIZE);
    if (strMode == "CBC" || strMode == "CFB" || strMode == "OFB" || strMode == "CTR")
    {
        if (strKeyFormat == "DER")
        {
            LoadKey("./keys/" + strKeyFile, key);
            LoadIV("./keys/iv.bin", iv);
        }
        else if (strKeyFormat == "Base64")
        {
            LoadKeyBase64("./keys/" + strKeyFile, key);
            LoadIVBase64("./keys/iv.txt", iv);
        }
        else if (strKeyFormat == "HEX")
        {
            LoadKeyHex("./keys/" + strKeyFile, key);
            LoadIVHex("./keys/iv.hex", iv);
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
            LoadKey("./keys/" + strKeyFile, key);
        }
        else if (strKeyFormat == "Base64")
        {
            LoadKeyBase64("./keys/" + strKeyFile, key);
        }
        else if (strKeyFormat == "HEX")
        {
            LoadKeyHex("./keys/" + strKeyFile, key);
        }
        else
        {
            cerr << "Unsupported key format. Please choose 'DER', 'Base64' or 'HEX'!\n";
            exit(1);
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
        ECB_Mode<DES>::Encryption e;
        e.SetKey(key, key.size());

        StringSource ss(plain, true,
                        new StreamTransformationFilter(e,
                                                       new StringSink(cipher)));
    }
    else if (strMode == "CBC")
    {
        CBC_Mode<DES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(plain, true,
                        new StreamTransformationFilter(e,
                                                       new StringSink(cipher)));
    }
    else if (strMode == "CFB")
    {
        CFB_Mode<DES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(plain, true,
                        new StreamTransformationFilter(e,
                                                       new StringSink(cipher)));
    }
    else if (strMode == "OFB")
    {
        OFB_Mode<DES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(plain, true,
                        new StreamTransformationFilter(e,
                                                       new StringSink(cipher)));
    }
    else if (strMode == "CTR")
    {
        CTR_Mode<DES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(plain, true,
                        new StreamTransformationFilter(e,
                                                       new StringSink(cipher)));
    }
    else
    {
        cerr << "Unsupported mode. Please choose: 'ECB', 'CBC', 'CFB', 'OFB', 'CTR'!\n";
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
void Decryption(const char *mode, const char *KeyFile, const char *KeyFormat, const char *RecoveredFile, const char *RecoveredFormat, const char *CipherFile, const char *CipherFormat)
{
    string strMode = standardizeString(mode);
    string strKeyFile(KeyFile);
    string strKeyFormat = standardizeString(KeyFormat);
    string strPlaintextFormat(RecoveredFormat);
    string strCipherFormat(CipherFormat);

    // Load key & iv
    CryptoPP::SecByteBlock key(DES::DEFAULT_KEYLENGTH);
    CryptoPP::SecByteBlock iv(DES::BLOCKSIZE);

    if (strMode == "CBC" || strMode == "CFB" || strMode == "OFB" || strMode == "CTR")
    {
        if (strKeyFormat == "DER")
        {
            LoadKey("./keys/" + strKeyFile, key);
            LoadIV("./keys/iv.bin", iv);
        }
        else if (strKeyFormat == "Base64")
        {
            LoadKeyBase64("./keys/" + strKeyFile, key);
            LoadIVBase64("./keys/iv.txt", iv);
        }
        else if (strKeyFormat == "HEX")
        {
            LoadKeyHex("./keys/" + strKeyFile, key);
            LoadIVHex("./keys/iv.hex", iv);
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
            LoadKey("./keys/" + strKeyFile, key);
        }
        else if (strKeyFormat == "Base64")
        {
            LoadKeyBase64("./keys/" + strKeyFile, key);
        }
        else if (strKeyFormat == "HEX")
        {
            LoadKeyHex("./keys/" + strKeyFile, key);
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
        ECB_Mode<DES>::Decryption d;
        d.SetKey(key, key.size());

        StringSource ss(cipher, true,
                        new StreamTransformationFilter(d,
                                                       new StringSink(recovered)));
    }
    else if (strMode == "CBC")
    {
        CBC_Mode<DES>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(cipher, true,
                        new StreamTransformationFilter(d,
                                                       new StringSink(recovered)));
    }
    else if (strMode == "CFB")
    {
        CFB_Mode<DES>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(cipher, true,
                        new StreamTransformationFilter(d,
                                                       new StringSink(recovered)));
    }
    else if (strMode == "OFB")
    {
        OFB_Mode<DES>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(cipher, true,
                        new StreamTransformationFilter(d,
                                                       new StringSink(recovered)));
    }
    else if (strMode == "CTR")
    {
        CTR_Mode<DES>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource ss(cipher, true,
                        new StreamTransformationFilter(d,
                                                       new StringSink(recovered)));
    }
    else
    {
        cerr << "Unsupported mode. Please choose: 'ECB', 'CBC', 'CFB', 'OFB', 'CTR'!\n";
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
std::streamsize getFileSize(const std::string &filename)
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
void ProcessInput(const string &action, int argc, char *argv[])
{
    string mode = argv[2];
    if (action == "genkey")
    {
        if (argc != 4)
        {
            cerr << "Usage: " << argv[0] << " genkey <KeyFileFormat> <KeyFile>" << endl;
            return;
        }
        GenerateAndSaveIV_Keys(argv[2], argv[3]);
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
        cout << "Overview DES Encryption Test" << endl;
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
        for (int i = 0; i < 10000; i++)
        {
            Decryption(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        string rcvTextFile = argv[5];
        std::streamsize rcv = getFileSize(rcvTextFile);

        string ciphertextFile = argv[7];
        std::streamsize cipher = getFileSize(ciphertextFile);
        // cout << "----------------------------------------------------------" << endl;
        cout << "Overview DES Decryption Test" << endl;
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

int main(int argc, char *argv[])
{
    // Set UTF-8 Encoding
#ifdef __APPLE__
    std::locale::global(std::locale("en_US.UTF-8"));
#elif __macosx__
    std::locale::global(std::locale("en_US.UTF-8"));
#elif __linux__
    std::locale::global(std::locale("C.utf8"));
#elif __unix__
    std::locale::global(std::locale("C.UTF8"));
#elif _WIN32
    // Set console code page to UTF-8 on Windows C.utf8, CP_UTF8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::ios_base::sync_with_stdio(false);

    if (argc < 2)
    {
        cerr << "Invalid arguments. Please follow the instructions:\n";

        cerr << "Usage: \n"
             << "\t" << argv[0] << " genkey <KeyFileFormat> <KeyFile>\n"
             << "\t" << argv[0] << " encrypt <Mode> <KeyFile> <KeyFileFormat> <PlaintextFile> <PlaintextFormat> <CipherFile> <CipherFormat>\n"
             << "\t" << argv[0] << " decrypt <Mode> <KeyFile> <KeyFileFormat> <RecoveredFile> <RecoveredFileFormat> <CipherFile> <CipherFormat>\n"
             << "Note:\n"
             << "\tKeySize represents the size of the key in bits, support only 64 bits in DES\n"
             << "\tMode options: 'ECB', 'CBC', 'CFB', 'OFB', 'CTR'\n"
             << "\tOutputFormat options: 'DER', 'Base64', 'HEX'\n"
             << "\tKeyFormat & CiphertextFormat options: 'DER', 'Base64', 'HEX'\n"
             << "\tPlaintextFormat & RecoveredFormat options: 'Text', 'DER', 'Base64', 'HEX'\n\n"
             << "Example:\n"
             << "\t" << argv[0] << " genkey Base64 key.txt\n"
             << "\t" << argv[0] << " encrypt CBC key.txt Base64 plain.txt Text cipher.txt Base64\n"
             << "\t" << argv[0] << " decrypt CBC key.txt Base64 recovered.txt Text cipher.txt Base64\n";
        return -1;
    }

    string action = argv[1];

    ProcessInput(action, argc, argv);

    return 0;
}