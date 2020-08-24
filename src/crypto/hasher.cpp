#include "hasher.h"
#include <cstring>
#include <exception>

template<typename a>
a min(a a1, a a2)

// Finds the minimum of the two data items
{
    if (a1 < a2) return a1;
    else return a2;
}

std::string zero::Hasher::hashutil(uint8_t    *out,
                                   char       *pwd,
                                   uint8_t    *salt,
                                   uint32_t    t_cost,
                                   uint32_t    m_cost,
                                   uint32_t    lanes,
                                   uint32_t    threads,
                                   const char *type)
{
    uint32_t out_length      = ARGON2_OUT_LEN_DEF;
    uint32_t salt_length     = ARGON2_SALT_LEN_DEF;
    uint8_t *secret          = NULL;
    uint32_t secret_length   = 0;
    uint8_t *ad              = NULL;
    uint32_t ad_length       = 0;
    bool     clear_memory    = false;
    bool     clear_secret    = false;
    bool     clear_password  = true;
    bool     print_internals = false;


    if (!pwd) {
        throw("password missing");
    }

    if (!salt) {
        secure_wipe_memory(pwd, strlen(pwd));
        throw("salt missing");
    }

    unsigned pwd_length = strlen(pwd);
    Argon2_Context context(out, out_length, (uint8_t *)pwd, pwd_length, salt,
                           salt_length,
                           secret, secret_length, ad, ad_length, t_cost, m_cost,
                           lanes, threads,
                           NULL, NULL,
                           clear_password, clear_secret, clear_memory,
                           print_internals);

    if (!strcmp(type, "d")) {
        int result = Argon2d(&context);

        if (result != ARGON2_OK) throw(ErrorMessage(result));
    } else if (!strcmp(type, "i")) {
        int result = Argon2i(&context);

        if (result != ARGON2_OK) throw(ErrorMessage(result));
    } else if (!strcmp(type, "id")) {
        int result = Argon2id(&context);

        if (result != ARGON2_OK) throw(ErrorMessage(result));
    } else if (!strcmp(type, "ds")) {
        int result = Argon2ds(&context);

        if (result != ARGON2_OK) throw(ErrorMessage(result));
    } else {
        secure_wipe_memory(pwd, strlen(pwd));
        throw("wrong Argon2 type");
    }

    std::string os = std::string();

    for (uint32_t i = 0; i < context.outlen; ++i) {
        os += std::to_string((char)context.out[i]);
    }
    return os;
}

std::string zero::Hasher::genSalt()
{
    CryptoPP::SecByteBlock b(0x00, ARGON2_SALT_LEN_DEF);
    CryptoPP::AutoSeededRandomPool rng;

    rng.GenerateBlock(b, b.size());

    return std::string((const char *)b.data(), b.size());
}

std::string zero::Hasher::hash(const std::string& spwd,
                               const std::string& ssalt)
{
    uint8_t salt[ARGON2_SALT_LEN_DEF];

    memset(salt, 0x00, ARGON2_SALT_LEN_DEF);
    memcpy(salt, ssalt.data(), ARGON2_SALT_LEN_DEF);

    char pwd[32];

    memset(pwd, 0x00, sizeof(pwd));
    memcpy(pwd, spwd.data(), min(sizeof(pwd), spwd.size()));

    unsigned char out[CryptoPP::AES::MAX_KEYLENGTH];

    memset(out, 0x00, sizeof(out));
    uint32_t m_cost  = 1 << ARGON2_LOG_M_COST_DEF;
    uint32_t t_cost  = ARGON2_T_COST_DEF;
    uint32_t lanes   = ARGON2_LANES_DEF;
    uint32_t threads = ARGON2_THREADS_DEF;
    const char *type = "d";

    std::string op;

    try {
        op = hashutil(out, pwd, salt, t_cost, m_cost, lanes, threads, type);
    }
    catch (std::exception& e)
    {
        throw std::runtime_error{ "Error geerating hash" };
    }
    return std::string(out, out + sizeof(out) / sizeof(out[0]));
}
