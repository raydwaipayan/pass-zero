#include "database.h"
#include "hasher.h"
#include "crypto.h"

zero::database::database(const std::string& master_string)
{
    // Initialize all required keys, ivs and salt
    salt       = Hasher::genSalt();
    master_key = Crypto::genKey(master_string, salt);
    master_iv  = Crypto::genIv();
    db_key     = Crypto::genKey();
    db_iv      = Crypto::genIv();
}

void zero::database::setMasterKey(const std::string& master_string)
{
    salt       = Hasher::genSalt();
    master_key = Crypto::genKey(master_string, salt);
    master_iv  = Crypto::genIv();
}

void zero::database::rotateDbKey()
{
    db_key = Crypto::genKey();
    db_iv  = Crypto::genIv();
}

int zero::database::addItem(const dataitem& d)
{
    data.push_back(d);
    return data.size() - 1;
}

zero::dataitem * zero::database::getItem(const int& idx)
{
    if (idx >= data.size()) return nullptr;

    return &data[idx];
}

void zero::database::clear()
{
    data.clear();
}

int zero::database::getSize()
{
    return data.size();
}

bool zero::database::removeItem(const int& idx)
{
    if (idx >= getSize())
    {
        return false;
    }
    data.remove(idx);
    return true;
}

zero::database * zero::database::genEmptyDb()
{
    database *newDb = new database();

    return newDb;
}

zero::database::~database()
{
    // Secure wipe all keys
    fill(salt.begin(),       salt.end(),       0);
    fill(master_key.begin(), master_key.end(), 0);
    fill(master_iv.begin(),  master_iv.end(),  0);
    fill(db_key.begin(),     db_key.end(),     0);
    fill(db_iv.begin(),      db_iv.end(),      0);
}
