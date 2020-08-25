#ifndef HASHER_H
#define HASHER_H
#include <string>
#include <cryptopp/osrng.h>

#include "argon2.h"

namespace zero {
class Hasher {
private:

    /*!
     * \brief Utility for hashing using Argon2
     * \param out
     * \param pwd
     * \param salt
     * \param t_cost
     * \param m_cost
     * \param lanes
     * \param threads
     * \param type
     * \return String containing the hashed password
     */
    static std::string hashutil(uint8_t    *out,
                                char       *pwd,
                                uint8_t    *salt,
                                uint32_t    t_cost,
                                uint32_t    m_cost,
                                uint32_t    lanes,
                                uint32_t    threads,
                                const char *type);

public:

    /*!
     * \brief Hashes the given password using the given salt string
     * \param spwd String containing the password string
     * \param ssalt String containing the salt
     * \return String containing the Hashed password, which acts as the Key for
     *          AES.
     */
    static std::string hash(const std::string& spwd,
                            const std::string& ssalt);

    /*!
     * \brief Generates a salt string randomly
     * \return String containing the generated salt
     */
    static std::string genSalt();
};
}
#endif // HASHER_H
