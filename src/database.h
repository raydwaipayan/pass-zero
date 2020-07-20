#ifndef DATABASE_H
#define DATABASE_H
#include "dataitem.h"
#include "string.h"
#include <cryptopp/aes.h>

using namespace CryptoPP;
class database{
private:
    SecByteBlock key;
    SecByteBlock iv;
    SecByteBlock masterkey;

    const std::string identifier="passzero8809";
    std::string encidentifier;

    std::string salt;
    std::string masteriv;
    QVector<dataitem> data;
    std::string encryptedkey;
    std::string encryptediv;
    database(){};
public:
    static std::string genKey(const std::string &, const std::string &);
    static database* genEmptyDb();
    static void checkKey(std::string &);
    void clear();
    database(const std::string &);
    int addItem(const dataitem &);
    dataitem* getItem(const int &);
    bool removeItem(const int &);
    int getSize();
    static database* read(const QString &, const QString &);
    bool write(const QString &);
    ~database();
    friend class writer;
    friend class reader;
};

#endif // DATABASE_H
