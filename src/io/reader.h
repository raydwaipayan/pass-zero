#ifndef READER_H
#define READER_H
#include "database.h"

namespace zero {
class Reader {
public:

    static void read(database     & d,
                     const QString&,
                     const QString& fileame);
};
}
#endif // READER_H
