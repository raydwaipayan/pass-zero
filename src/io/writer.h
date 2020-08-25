#ifndef WRITER_H
#define WRITER_H
#include "database.h"

namespace zero {
class Writer {
public:

    /*!
     * \brief Encrypt and write the databse to a file
     * \param d Database to encrypt and write
     * \param filename String containing the name of the file to write to
     * \return boolean to denote success of the operation
     */
    static bool write(database       d,
                      const QString& filename);
};
}
#endif // WRITER_H
