#include <string>
#include <iostream>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>
#include "crypto.h"

std::string Crypto::fixKey(const std::string& key)
{
    std::string fkey = key;

    if (CryptoPP::AES::MAX_KEYLENGTH < key.size())
    {
        fkey = key.substr(0, CryptoPP::AES::MAX_KEYLENGTH);
    }
    else if (CryptoPP::AES::MAX_KEYLENGTH > key.size())
    {
        fkey += std::string(CryptoPP::AES::MAX_KEYLENGTH - key.size(), '*');
    }
    return fkey;
}

std::string Crypto::genKey(const std::string& master_string,
                           const std::string& salt)
{
    std::string key = Hasher::hash(master_string, salt);

    key = fixKey(key);

    return key;
}

std::string Crypto::genKey()
{
    CryptoPP::SecByteBlock key(0x00, CryptoPP::AES::MAX_KEYLENGTH);
    CryptoPP::AutoSeededRandomPool rng;

    rng.GenerateBlock(key, key.size());

    return std::string(reinterpret_cast<const char *>(key.data()), key.size());
}

std::string Crypto::genIv()
{
    CryptoPP::SecByteBlock iv(0x00, CryptoPP::AES::BLOCKSIZE);
    CryptoPP::AutoSeededRandomPool rng;

    rng.GenerateBlock(iv, iv.size());

    return std::string(reinterpret_cast<const char *>(iv.data()), iv.size());
}

void Crypto::setEncryptor(const std::string& key, const std::string& iv)
{
    CryptoPP::SecByteBlock bkey(reinterpret_cast<const CryptoPP::byte *>(key.data()),
                                key.size());
    CryptoPP::SecByteBlock biv(reinterpret_cast<const CryptoPP::byte *>(iv.data()),
                               iv.size());

    encryptor.reset(new CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption(bkey,
                                                                      bkey.size(),
                                                                      biv));
}

void Crypto::setDecryptor(const std::string& key, const std::string& iv)
{
    CryptoPP::SecByteBlock bkey(reinterpret_cast<const CryptoPP::byte *>(key.data()),
                                key.size());
    CryptoPP::SecByteBlock biv(reinterpret_cast<const CryptoPP::byte *>(iv.data()),
                               iv.size());

    decryptor.reset(new CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption(bkey,
                                                                      bkey.size(),
                                                                      biv));
}

std::string Crypto::encrypt(const std::string& plaintext)
{
    std::string ciphertext;

    try {
        CryptoPP::StringSource ss(plaintext,
                                  true,
                                  new CryptoPP::StreamTransformationFilter(
                                      *(encryptor.get()),
                                      new
                                      CryptoPP
                                      ::
                                      Base64Encoder(
                                          new
                                          CryptoPP
                                          ::
                                          StringSink(
                                              ciphertext), false)));
    } catch (CryptoPP::Exception& e)
    {
        std::cerr << "Encrypt error: " << e.what();
    }
    return ciphertext;
}

std::string Crypto::decrypt(const std::string& ciphertext)
{
    std::string plaintext;

    try {
        CryptoPP::ArraySource(ciphertext,
                              true,
                              new CryptoPP::Base64Decoder(
                                  new CryptoPP::StreamTransformationFilter(
                                      *(decryptor.get()),
                                      new
                                      CryptoPP
                                      ::
                                      StringSink(
                                          plaintext))));
    }
    catch (CryptoPP::Exception& e)
    {
        std::cerr << "Decrypt error:" << e.what();
        throw std::runtime_error("Invalid password! Decryption failed!");
    }
    return plaintext;
}

std::string Crypto::base64Encrypt(const std::string& plaintext)
{
    std::string ciphertext;

    CryptoPP::ArraySource(plaintext, true,
                          new CryptoPP::Base64Encoder(new CryptoPP::StringSink(
                                                          ciphertext), false));
    return ciphertext;
}

std::string Crypto::base64Decrypt(const std::string& ciphertext)
{
    std::string plaintext;

    CryptoPP::ArraySource(ciphertext, true,
                          new CryptoPP::Base64Decoder(new CryptoPP::StringSink(
                                                          plaintext)));
    return plaintext;
}
