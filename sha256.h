#ifndef SHA256_H
#define SHA256_H

#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>

std::string sha256(const uint8_t* data, size_t length);
std::string sha256(const std::string& text);

#endif