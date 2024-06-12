#include "sha256.h"

std::string sha256(const uint8_t* data, size_t length) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, length);
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

std::string sha256(const std::string& text) {
    return sha256(reinterpret_cast<const uint8_t*>(text.c_str()), text.length());
}