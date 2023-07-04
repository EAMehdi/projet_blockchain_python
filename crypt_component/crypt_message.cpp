#include <string>
#include <openssl/hmac.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

/**
 * Checks if a given string is a valid hexadecimal string.
 * @param str: The string to check.
 * @returns: True if the string is a valid hexadecimal string, false otherwise.
 */
bool is_hex(const std::string& str) {
    const std::string hex_chars = "0123456789abcdefABCDEF";

    for (char c : str) {
        if (hex_chars.find(c) == std::string::npos) {
            return false;
        }
    }

    return true;
}

/**
 * Computes HMAC-SHA512 of input data using a secret key.
 * @param key: A secret key used for the HMAC computation. Must be a 66-character string starting with "0x" followed by a 64-character hexadecimal string (256 bits).
 * @param data: The input data to be authenticated.
 * @returns: A hexadecimal string representation of the HMAC-SHA512 digest.
 * @throws std::invalid_argument: If the key is not a 66-character string starting with "0x" followed by a 64-character hexadecimal string.
 */
std::string hmac_sha512(const std::string& key, const std::string& data) {
    if (key.length() != 66 || !is_hex(key.substr(2)) || key.substr(0, 2) != "0x") {
        throw std::invalid_argument("Key must be a 66-character string starting with '0x' followed by a 64-character hexadecimal string");
    }

    std::string key_bin;
    key_bin.reserve(32);
    for (int i = 2; i < 66; i += 2) {
        key_bin.push_back(static_cast<char>(std::stoi(key.substr(i, 2), nullptr, 16)));
    }

    unsigned char* digest = HMAC(EVP_sha512(), key_bin.c_str(), key_bin.size(),
                                 reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), NULL, NULL); 

    char mdString[129];

    for (int i = 0; i < 64; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    return std::string(mdString);
}

PYBIND11_MODULE(crypt_message, m) {
    m.doc() = "Crypto module providing HMAC-SHA512 functionality";
    m.def("hmac_sha512", &hmac_sha512, "A function to compute HMAC-SHA512 of input data using a secret key");
}

