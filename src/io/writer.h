#ifndef WRITER_H
#define WRITER_H
#include "database.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

using namespace CryptoPP;
class Writer {
public:

    static bool write(database,
                      const QString&);
};
#endif // WRITER_H
