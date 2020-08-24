#ifndef CRYPTO_H
#define CRYPTO_H
#include <cryptopp/osrng.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

#include <string>

#include "hasher.h"

class Crypto {
private:

    std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption>encryptor;
    std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption>decryptor;

public:

    static std::string fixKey(const std::string&);
    static std::string genKey(const std::string&,
                              const std::string& salt);
    static std::string genKey();
    static std::string genIv();
    void               setEncryptor(const std::string&,
                                    const std::string&);
    void               setDecryptor(const std::string&,
                                    const std::string&);
    std::string        encrypt(const std::string&);
    std::string        decrypt(const std::string&);
    static std::string base64Encrypt(const std::string&);
    static std::string base64Decrypt(const std::string&);
};

#endif // CRYPTO_H
