#include <iostream>
#include <string>
using std::string;
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#endif
#include <fstream>
#include <locale>
#include <chrono>
// Cryptopp library
#include <cryptopp/cryptlib.h>
#include "cryptopp/sha3.h"
#include "cryptopp/sha.h"
#include "cryptopp/shake.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"

using CryptoPP::FileSink;
using namespace std;
using namespace CryptoPP;

#ifdef _WIN32
#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT __attribute__((visibility("default")))
#endif

extern "C"
{
    DLL_EXPORT void hashes(const char *algo, const char *input_option, const char *input_data, const char *output_filename, int shakeLength);
}

void parseArguments(int argc, char *argv[], string &hashType, string &inputOption, string &inputData, string &outputFile, int &shakeLength)
{
    hashType = argv[1];
    inputOption = argv[2];
    inputData = argv[3];
    outputFile = argv[4];
    if ((hashType == "SHAKE128" || hashType == "SHAKE256") && argc == 6)
    {
        shakeLength = stoi(argv[5]);
    }
}

unique_ptr<HashTransformation> selectHashFunction(const string &hashType)
{
    if (hashType == "SHA_224")
        return make_unique<SHA224>();
    if (hashType == "SHA_256")
        return make_unique<SHA256>();
    if (hashType == "SHA_384")
        return make_unique<SHA384>();
    if (hashType == "SHA_512")
        return make_unique<SHA512>();
    if (hashType == "SHA3_224")
        return make_unique<SHA3_224>();
    if (hashType == "SHA3_256")
        return make_unique<SHA3_256>();
    if (hashType == "SHA3_384")
        return make_unique<SHA3_384>();
    if (hashType == "SHA3_512")
        return make_unique<SHA3_512>();
    if (hashType == "SHAKE128")
        return make_unique<SHAKE128>();
    if (hashType == "SHAKE256")
        return make_unique<SHAKE256>();
    return nullptr;
}

string getInputMessage(const string &inputOption, const string &inputData)
{
    string message;
    if (inputOption == "screen")
    {
        message = inputData;
    }
    else if (inputOption == "file")
    {
        ifstream file(inputData, ios::binary);
        if (!file)
        {
            cerr << "Error opening file: " << inputData << std::endl;
            exit(1);
        }
        message = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    }
    return message;
}

void hashMessage(unique_ptr<HashTransformation> &hash, const string &message, const string &hashType, const string &outputFile, int shakeLength)
{
    // auto start_time = chrono::high_resolution_clock::now();
    string digest;

    hash->Update((const CryptoPP::byte *)message.data(), message.size());
    if (hashType == "SHAKE128" || hashType == "SHAKE256")
    {
        shakeLength = 128/8;
        digest.resize(shakeLength);
        hash->TruncatedFinal((CryptoPP::byte *)&digest[0], shakeLength);
    }
    else
    {
        digest.resize(hash->DigestSize());
        hash->Final((CryptoPP::byte *)&digest[0]);
    }

    string encoded;
    StringSource(digest, true, new HexEncoder(new StringSink(encoded)));

    ofstream outFile(outputFile);
    if (!outFile)
    {
        cerr << "Error opening output file: " << outputFile << std::endl;
        exit(1);
    }
    outFile << encoded << endl;

    cout << "Digest: " << encoded << endl;

    // auto end_time = chrono::high_resolution_clock::now();
    // auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    // cout << "Timer: " << elapsed_time << " milliseconds" << endl;

    // outFile << "Timer: " << elapsed_time << " milliseconds" << endl;
    outFile.close();
}

void hashes(const char *algo, const char *input_option, const char *input_data, const char *output_filename, int shakeLength)
{
    string hashType(algo);
    string inputOption(input_option);
    string inputData(input_data);
    string outputFile(output_filename);

    auto hash = selectHashFunction(hashType);
    if (!hash)
    {
        cerr << "Invalid hash type: " << hashType << endl;
        return;
    }

    string message = getInputMessage(inputOption, inputData);
    hashMessage(hash, message, hashType, outputFile, shakeLength / 8);
}

int main(int argc, char *argv[])
{
    // support for Vietnamese
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    if (argc != 5 && argc != 6)
    {
        std::cerr << "Usage:\n"
                  << argv[0] << " <hash_type> <option_input> <input_data> <output_file> [<shake_length>]" << std::endl;
        std::cerr << "\tHash type: SHA_224, SHA_256, SHA_384, SHA_512, SHA3_224, SHA3_256, SHA3_384, SHA3_512, SHAKE128, SHAKE256" << std::endl;
        std::cerr << "\tOption input: screen, file" << std::endl;
        std::cerr << "\tInput data: message (if screen), or file name (if file)" << std::endl;
        std::cerr << "\tOutput file: name of the file to save the hash result" << std::endl;
        std::cerr << "\t[<shake_length>]: output length for SHAKE128 or SHAKE256 (optional)" << std::endl;
        return 1;
    }

    const char *algo = argv[1];
    const char *input_option = argv[2];
    const char *input_data = argv[3];
    const char *output_filename = argv[4];
    int shakeLength = (argc == 6) ? std::stoi(argv[5]) : 32;


    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        hashes(algo, input_option, input_data, output_filename, shakeLength);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    
    int totalDuration = duration.count();

    cout << "\n----------------------------------------------------------" << endl;
    cout << "Overview Hashing Test" << endl;
    cout << "algo: " << algo << endl;
    cout << "Hashing time: " << totalDuration << " milliseconds" << endl;
    cout << "----------------------------------------------------------" << endl;
    return 0;
}