#ifndef HASHER_H
#define HASHER_H
#include <string>
#include <cryptopp/osrng.h>

#include "argon2.h"

namespace zero {
class Hasher {
public:

    static std::string hashutil(uint8_t    *out,
                                char       *pwd,
                                uint8_t    *salt,
                                uint32_t    t_cost,
                                uint32_t    m_cost,
                                uint32_t    lanes,
                                uint32_t    threads,
                                const char *type);
    static std::string hash(const std::string&,
                            const std::string&);
    static std::string genSalt();
};
}
#endif // HASHER_H
