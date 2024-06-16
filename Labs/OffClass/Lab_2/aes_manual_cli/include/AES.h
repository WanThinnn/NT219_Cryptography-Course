#ifndef AES_H
#define AES_H

#include <vector>
#include <cstdlib>
#include <cstdint>
class AES
{
private:
    std::vector<std::vector<uint8_t>> round_keys;
    std::vector<uint8_t> key;
    size_t key_length;

    // AES constants
    std::vector<uint8_t> S_BOX;
    std::vector<uint8_t> INV_S_BOX;
    std::vector<std::vector<uint8_t>> RCON;

    std::vector<uint8_t> sub_word(std::vector<uint8_t> word);
    std::vector<uint8_t> rot_word(std::vector<uint8_t> word);
    std::vector<std::vector<uint8_t>> key_expansion_128();
    std::vector<std::vector<uint8_t>> key_expansion_192();
    std::vector<std::vector<uint8_t>> key_expansion_256();
    std::vector<std::vector<uint8_t>> key_expansion();
    void sub_bytes(std::vector<std::vector<uint8_t>> &state);
    void shift_rows(std::vector<std::vector<uint8_t>> &state);
    void mix_columns(std::vector<std::vector<uint8_t>> &state);
    void add_round_key(std::vector<std::vector<uint8_t>> &state, int round_number);
    void inv_sub_bytes(std::vector<std::vector<uint8_t>> &state);
    void inv_shift_rows(std::vector<std::vector<uint8_t>> &state);
    void inv_mix_columns(std::vector<std::vector<uint8_t>> &state);

public:
    AES(const std::vector<uint8_t> &key, size_t key_length);

    std::vector<uint8_t> encrypt(const std::vector<uint8_t> &data);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t> &ciphertext);
};

#endif // AES_H
