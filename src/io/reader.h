#ifndef READER_H
#define READER_H
#include "database.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
using namespace CryptoPP;
class Reader {
public:

    static void read(database     & d,
                     const QString&,
                     const QString& fileame);
};

#endif // READER_H
