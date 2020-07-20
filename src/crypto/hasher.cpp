#include "hasher.h"
#include <cstring>
#include <cryptopp/osrng.h>
#include <QCryptographicHash>
#include <QString>
#include <exception>
#include <QDebug>
std::string hasher::hashutil(uint8_t *out, char *pwd, uint8_t *salt, uint32_t t_cost,
                         uint32_t m_cost, uint32_t lanes, uint32_t threads,
                         const char *type)
{
    uint32_t out_length=ARGON2_OUT_LEN_DEF;
       uint32_t salt_length=ARGON2_SALT_LEN_DEF;
       uint8_t* secret=NULL;
       uint32_t secret_length=0;
       uint8_t* ad=NULL;
       uint32_t ad_length=0;
       bool clear_memory = false;
       bool clear_secret = false;
       bool clear_password = true;
       bool print_internals = false;


       if (!pwd) {
           throw("password missing");
       }

       if (!salt) {
           secure_wipe_memory(pwd, strlen(pwd));
           throw("salt missing");
       }

       unsigned pwd_length = strlen(pwd);
       Argon2_Context context(out, out_length, (uint8_t*)pwd, pwd_length, salt, salt_length,
               secret, secret_length, ad, ad_length, t_cost, m_cost, lanes, threads,
               NULL, NULL,
               clear_password, clear_secret, clear_memory, print_internals);
       if (!strcmp(type, "d")) {
           int result = Argon2d(&context);
           if (result != ARGON2_OK)
               throw(ErrorMessage(result));
       } else if (!strcmp(type, "i")) {
           int result = Argon2i(&context);
           if (result != ARGON2_OK)
               throw(ErrorMessage(result));
       } else if (!strcmp(type, "id")) {
           int result = Argon2id(&context);
           if (result != ARGON2_OK)
               throw(ErrorMessage(result));
       } else if (!strcmp(type, "ds")) {
           int result = Argon2ds(&context);
           if (result != ARGON2_OK)
               throw(ErrorMessage(result));
       } else {
           secure_wipe_memory(pwd, strlen(pwd));
           throw("wrong Argon2 type");
       }

       std::string os("");
       for (uint32_t i = 0; i < context.outlen; ++i) {
               os+=std::to_string((char)context.out[i]);
       }
       return os;
}
std::string hasher::genSalt()
{
    CryptoPP::SecByteBlock b(0x00,ARGON2_SALT_LEN_DEF);
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock(b,b.size());

    return std::string((const char*)b.data(), b.size());
}
std::string hasher::hash(const std::string &spwd, const std::string &ssalt)
{
    uint8_t salt[ARGON2_SALT_LEN_DEF];
    memset(salt, 0x00, ARGON2_SALT_LEN_DEF);
    memcpy(salt, ssalt.data(),ARGON2_SALT_LEN_DEF);

    char pwd[32];
    memcpy(pwd,spwd.data(),sizeof(pwd));

    unsigned char out[CryptoPP::AES::MAX_KEYLENGTH];
    memset(out,0x00,sizeof(out));
    uint32_t m_cost = 1 << ARGON2_LOG_M_COST_DEF;
    uint32_t t_cost = ARGON2_T_COST_DEF;
    uint32_t lanes = ARGON2_LANES_DEF;
    uint32_t threads = ARGON2_THREADS_DEF;
    const char* type="d";

    std::string op;
    try{
     op=hashutil(out, pwd, salt, t_cost, m_cost, lanes, threads, type);
    }
    catch(std::exception &e)
    {
        op = QString(QCryptographicHash::hash(QByteArray(spwd.data()), QCryptographicHash::Sha512)).toStdString();
    }

    return op;
}
