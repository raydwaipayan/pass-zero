#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>

#include "database.h"
#include "hasher.h"
#include "crypto.h"
#include <QDebug>

database::database(const std::string& master_string)
{
    // Initialize all required keys, ivs and salt
    salt       = Hasher::genSalt();
    master_key = Crypto::genKey(master_string, salt);
    master_iv  = Crypto::genIv();
    db_key     = Crypto::genKey();
    db_iv      = Crypto::genIv();
}

int database::addItem(const dataitem& d)
{
    data.push_back(d);
    return data.size() - 1;
}

dataitem * database::getItem(const int& idx)
{
    if (idx >= data.size()) return nullptr;

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

bool database::removeItem(const int& idx)
{
    if (idx >= getSize())
    {
        return false;
    }
    data.remove(idx);
    return true;
}

database * database::genEmptyDb()
{
    database *newDb = new database();

    return newDb;
}

database::~database()
{
    // Secure wipe all keys
    fill(salt.begin(),       salt.end(),       0);
    fill(master_key.begin(), master_key.end(), 0);
    fill(master_iv.begin(),  master_iv.end(),  0);
    fill(db_key.begin(),     db_key.end(),     0);
    fill(db_iv.begin(),      db_iv.end(),      0);
}
