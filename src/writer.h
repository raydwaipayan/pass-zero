#ifndef WRITER_H
#define WRITER_H
#include "database.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

using namespace CryptoPP;
class writer{
public:
    static void write(database, const QString &);
    static std::string encryptToString(CBC_Mode<AES>::Encryption &, const std::string &);
    static QString encryptToQString(CBC_Mode<AES>::Encryption &, const QString &);

};
#endif // WRITER_H
