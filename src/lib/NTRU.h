#ifndef NTRU_H
#define NTRU_H

#include "MISC.h"
namespace NTRU {

typedef struct
{
    Polynomial::clsPoly f;
    Polynomial::clsPoly f_p;
}priv_key_t;
typedef struct
{
    Polynomial::clsPoly h;
    Config::params_t Param;
}pub_key_t;
typedef struct
{
    priv_key_t Sk;
    pub_key_t Pk;

}key_pair_t;


key_pair_t generateKeyPair(const Config::params_t _param);

Polynomial::clsPoly encrypt(const unsigned char *_m, const size_t _l, const pub_key_t _pk);
std::string decrypt(Polynomial::clsPoly _e, key_pair_t _k);

} // namespace NTRU
#endif // NTRU_H
