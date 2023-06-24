#include <string>
#include <openssl/hmac.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

/**
 * Computes HMAC-SHA512 of input data using a secret key.
 * @param key: A secret key used for the HMAC computation. Cannot be empty.
 * @param data: The input data to be authenticated.
 * @returns: A hexadecimal string representation of the HMAC-SHA512 digest.
 * @throws std::invalid_argument: If the key is empty.
 */
std::string hmac_sha512(const std::string& key, const std::string& data) {
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }

    // HMAC function from OpenSSL library computes the HMAC-SHA512 hash.
    /**
     * key.c_str() and key.size() provide the secret key in both pointer and size forms.
    
     * reinterpret_cast<const unsigned char*>(data.c_str()) and data.size() provide the data to be hashed.
     * reinterpret_cast is used to convert the pointer type of the data to an unsigned char*.
     * NULL, NULL arguments are placeholders for an output buffer and its size.
     * When set to NULL, the function allocates and returns a new buffer for the computed HMAC.
    */
    unsigned char* digest = HMAC(EVP_sha512(), key.c_str(), key.size(),
                                 reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), NULL, NULL); 

    // Preparing a character array to hold the hexadecimal HMAC-SHA512 result.
    // Each byte of the result will be represented by two hexadecimal digits,
    // so size of the array is twice the size of the HMAC result (64 bytes for SHA-512) plus one for '\0' character.
    char mdString[129];

    // Converting each byte of the binary HMAC result into two hexadecimal digits.
    for (int i = 0; i < 64; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    return std::string(mdString);
}

/**
 * Pybind11 module definition.
 * The module is named "crypt_message" and exposes the function hmac_sha512 to Python.
 */
PYBIND11_MODULE(crypt_message, m) {
    m.doc() = "Crypto module providing HMAC-SHA512 functionality";
    m.def("hmac_sha512", &hmac_sha512, "A function to compute HMAC-SHA512 of input data using a secret key");
}

