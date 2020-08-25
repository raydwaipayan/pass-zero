#ifndef READER_H
#define READER_H
#include "database.h"

namespace zero {
class Reader {
public:

    /*!
     * \brief Reads and decrypts the database file
     * \param d Database reference to populate
     * \param masterstring The master string for the database
     * \param filename Name of the database file
     */
    static void read(database     & d,
                     const QString& masterstring,
                     const QString& fileame);
};
}
#endif // READER_H
