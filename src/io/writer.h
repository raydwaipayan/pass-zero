#ifndef WRITER_H
#define WRITER_H
#include "database.h"

namespace zero {
class Writer {
public:

    static bool write(database,
                      const QString&);
};
}
#endif // WRITER_H
