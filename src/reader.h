#ifndef READER_H
#define READER_H
#include "database.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
using namespace CryptoPP;
class reader{
public:
    static bool read(database &d, const QString &, const QString &fileame);
    static std::string decryptToString(CBC_Mode<AES>::Decryption &decryptor, const QString &);
    static QString decryptToQString(CBC_Mode<AES>::Decryption &decryptor, const QString &);
    static std::string decryptToString(CBC_Mode<AES>::Decryption &decryptor, const std::string &);

};

#endif // READER_H
