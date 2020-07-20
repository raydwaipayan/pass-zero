#include "database.h"
#include "reader.h"
#include "writer.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>
#include <QDebug>
#include "crypto/hasher.h"
using namespace CryptoPP;
void database::checkKey(std::string &masterkey)
{
    if(AES::MAX_KEYLENGTH<masterkey.size())
    {
        masterkey=masterkey.substr(0,AES::MAX_KEYLENGTH);
    }
    else if(AES::MAX_KEYLENGTH>masterkey.size())
    {
        masterkey+=std::string(AES::MAX_KEYLENGTH - masterkey.size(), '*');
    }
}

std::string database::genKey(const std::string &masterstring, const std::string &salt)
{
    std::string mkstring;
    mkstring=hasher::hash(masterstring, salt);
    checkKey(mkstring);
    return mkstring;
}

database::database(const std::string& masterstring)
{
    std::string masterkeyString, salt;
    salt=hasher::genSalt();
    masterkeyString=genKey(masterstring, salt);

    masterkey=SecByteBlock((const byte*)(masterkeyString.data()),masterkeyString.size());
    SecByteBlock msiv(0x00, AES::BLOCKSIZE);

    AutoSeededRandomPool rng;
    rng.GenerateBlock(msiv, msiv.size());
    key=SecByteBlock(0x00, AES::MAX_KEYLENGTH);
    rng.GenerateBlock(key, key.size());

    iv=SecByteBlock(0x00, AES::BLOCKSIZE);
    rng.GenerateBlock(iv,iv.size());


    CBC_Mode<AES>::Encryption encryptor(masterkey, masterkey.size(),msiv);
    encidentifier=writer::encryptToString(encryptor, identifier);

    ArraySource as(key,key.size(), true,
                       new StreamTransformationFilter(
                           encryptor, new Base64Encoder(new StringSink(encryptedkey))
                       ));
    ArraySource as2(iv, iv.size(), true,
                        new StreamTransformationFilter(
                              encryptor, new Base64Encoder(new StringSink(encryptediv))));

    ArraySource as3(salt, true,
                      new Base64Encoder(new StringSink(this->salt)));

    ArraySource as4(msiv, msiv.size(), true,
             new Base64Encoder(new StringSink(masteriv)));
}

int database::addItem(const dataitem &d)
{
    data.push_back(d);
    return data.size()-1;
}
dataitem* database::getItem(const int &idx)
{
    if(idx>=data.size())
        return nullptr;
    return &data[idx];
}
void database::clear()
{
    data.clear();
}
int database::getSize()
{
    return data.size();
}
bool database::removeItem(const int &idx)
{
    if(idx>=getSize())
    {
        return false;
    }
    data.remove(idx);
    return true;
}
database* database::genEmptyDb()
{
    database *newDb=new database();
    return newDb;
}
database* database::read(const QString &filename, const QString &masterstring)
{
    database *temp=database::genEmptyDb();
    if(reader::read((*temp), masterstring, filename))
        return temp;
    return nullptr;
}
bool database::write(const QString &filename)
{
    writer::write((*this),filename);
    return true;
}
database::~database()
{
}
