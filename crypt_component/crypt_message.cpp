#include <string>
#include <openssl/hmac.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

// HMAC-SHA512 function
std::string hmac_sha512(const std::string& key, const std::string& data) {
    // create a buffer to hold the result
    unsigned char* digest = HMAC(EVP_sha512(), key.c_str(), key.size(),
                                 reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), NULL, NULL); 

    // convert the result to hexadecimal
    char mdString[129]; // SHA-512 produces a 512-bit digest, which is 128 hex characters + 1 for '\0'
    for (int i = 0; i < 64; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    return std::string(mdString);
}

PYBIND11_MODULE(crypt_message, m) {
    m.doc() = "Crypto module providing HMAC-SHA512 functionality";
    m.def("hmac_sha512", &hmac_sha512, "Compute HMAC-SHA512");
}

