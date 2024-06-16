/* OpenSSL libraries */
#include <openssl/evp.h>    // common cryptographic algorithms
#include <openssl/evperr.h> // handle errors
#include <openssl/bio.h>    // input, output handle in OpenSSL
/* stand C++ library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DLL_EXPORT
    #ifdef _WIN32
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __atribute__ ((visibility("default")))
    #endif
#endif

extern "C"
{
    void hashes(const char *algo, const char *input_filename, const char *output_filename);
}

void hashes(const char *algo, const char *input_filename, const char *output_filename)
{
    OpenSSL_add_all_digests();

    const EVP_MD *hash_algo = EVP_get_digestbyname(algo); // eg. SHA256, SHA3-256, SHA3-512

    // Open the input file (file input, ouput in C)
    FILE *f_in = NULL;
    errno_t err_in = fopen_s(&f_in, input_filename, "rb"); // read the input file
    if (err_in != 0)
    {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    FILE *f_out = NULL;
    errno_t err_out = fopen_s(&f_out, output_filename, "w"); // Open output file
    if (err_out != 0)
    {
        perror("Failed to open output file");
        fclose(f_in);
        exit(EXIT_FAILURE);
    }

    // Check input arguments algo (from input)
    if (!hash_algo)
    { // SHA2: SHA224, SHA256, SHA384, SHA512,.. SHA3-...
        fprintf(stderr, "Unknown message digest %s\n", algo);
        fclose(f_in);
        fclose(f_out);
        exit(EXIT_FAILURE);
    }

    // Create and initialize the context
    EVP_MD_CTX *mdctx; // context structure for all SHA1, SHA2, SHA3, SHAKE functions

    // Setting hashes funtion (create instances)
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, hash_algo, NULL); // set hash algorithms

    // Read from the file and update the digest
    unsigned char buffer[4096];
    size_t read_bytes;
    while ((read_bytes = fread(buffer, 1, sizeof(buffer), f_in)) != 0)
    {
        if (mdctx && read_bytes > 0)
        {
            EVP_DigestUpdate(mdctx, buffer, read_bytes);
        }
    }

    // Finalize the digest (compute hash output)
    unsigned char md_value[EVP_MAX_MD_SIZE];      // output length (max output 512 bits)
    unsigned int md_len;                          // real ouput size
    EVP_DigestFinal_ex(mdctx, md_value, &md_len); // eg. SHA512-256; set actual output /output length
    EVP_MD_CTX_free(mdctx);                       // closed hashes structure

    // Write each char off the digest to the output file (bio insted ?)
    for (unsigned int i = 0; i < md_len; i++)
    {
        fprintf(f_out, "%02x", md_value[i]);
    }
    fprintf(f_out, "\n"); // write ouput md_value to file
    // Close files
    fclose(f_in);
    fclose(f_out);
}

int main(int argc, char **argv)
{
    if (argc != 4)
    { // C# should be 3
        fprintf(stderr, "Usage: %s <hash-algorithm> <input-file> <output-file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *algo = argv[1];
    const char *input_filename = argv[2];
    const char *output_filename = argv[3];
    hashes(algo, input_filename, output_filename);
    printf("Hashed saved to %s", output_filename);
    return 0;
}