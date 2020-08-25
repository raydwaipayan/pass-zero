#ifndef CRYPTO_H
#define CRYPTO_H
#include <cryptopp/osrng.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

#include <string>

#include "hasher.h"

namespace zero {
class Crypto {
private:

    /*!
     * \brief encryptor for aes cbc mode
     */
    std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption>encryptor;

    /*!
     * \brief decryptor for aes cbc mode
     */
    std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption>decryptor;

public:

    /*!
     * \brief Fixes the key by padding with fixed characters
     *          if key length is incorrect
     * \param key Contains the original key
     * \return string containing the fixed key
     */
    static std::string fixKey(const std::string& key);

    /*!
     * \brief Generate the key using the given password string and salt
     * \param master_string Contains the password string
     * \param Contains the salt
     * \return String containing the generated Key.
     */
    static std::string genKey(const std::string& master_string,
                              const std::string& salt);

    /*!
     * \brief Generates a key randomly
     * \return String containing the generated key
     */
    static std::string genKey();

    /*!
     * \brief Generates the iv randomly
     * \return String containing the generated iv
     */
    static std::string genIv();

    /*!
     * \brief Sets the aes encryptor using the supplied key and iv
     * \param key String containing the key
     * \param iv String containing the iv
     */
    void               setEncryptor(const std::string& key,
                                    const std::string& iv);

    /*!
     * \brief Sets the aes decryptor using the supplied key and iv
     * \param key String containing the key
     * \param iv String containing the iv
     */
    void setDecryptor(const std::string& key,
                      const std::string& iv);

    /*!
     * \brief Encrypts the given plaintext usin AES and returns the ciphertext
     * in base64
     * \param plaintext String containing the original text
     * \return String containing the encrypted text
     */
    std::string        encrypt(const std::string& plaintext);

    /*!
     * \brief Decrypts the given base64 ciphertext using AES and returns the
     * plaintext
     * \param ciphertext String containing the encrypted text
     * \return String containing the decrypted text
     */
    std::string        decrypt(const std::string& ciphertext);

    /*!
     * \brief Converts the given text to base64
     * \param plaintext Contains the original text
     * \return Text encoded in base64
     */
    static std::string base64Encrypt(const std::string& plaintext);

    /*!
     * \brief Decrypts the given text from base64
     * \param ciphertext Contains the base64 text
     * \return Decoded base64 text
     */
    static std::string base64Decrypt(const std::string& ciphertext);
};
}
#endif // CRYPTO_H
