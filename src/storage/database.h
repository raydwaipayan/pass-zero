#ifndef DATABASE_H
#define DATABASE_H

#include "dataitem.h"
#include "string.h"


namespace zero {
class database  {
private:

    const std::string identifier = "passzero8809";
    std::string master_key, master_iv, salt, db_key, db_iv;
    QVector<dataitem>data;
    database() {}

public:

    static database* genEmptyDb();
    void             clear();
    void             setMasterKey(const std::string&);
    void             rotateDbKey();
    database(const std::string&);
    int              addItem(const dataitem&);
    dataitem       * getItem(const int&);
    bool             removeItem(const int&);
    int              getSize();
    ~database();
    friend class Writer;
    friend class Reader;
};
}
#endif // DATABASE_H
