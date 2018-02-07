#ifndef NTRU_H
#define NTRU_H

#include "MISC.h"
namespace NTRU {

typedef struct
{
    Polynomial::clsPoly F;
    Polynomial::clsPoly f_q;
}poly_F_t;
typedef struct
{
    Polynomial::clsPoly h;
    Config::params_t Param;
}pub_key_t;
typedef struct
{
    Polynomial::clsPoly Sk;
    pub_key_t Pk;

}key_pair_t;

typedef struct
{
    poly_F_t Sk;
    pub_key_t Pk;

}key_pair_t2;


key_pair_t generateKeyPair(const Config::params_t _param);
key_pair_t generateKeyPair2(const Config::params_t _param);
poly_F_t generateF(const Config::params_t _param);
Polynomial::clsPoly encrypt(const unsigned char *_m, const size_t _l, const pub_key_t _pk);
std::string decrypt(Polynomial::clsPoly _e, key_pair_t _k);
Polynomial::clsPoly inv(const Polynomial::clsPoly _a,const Config::params_t _param);
Polynomial::clsPoly generateG(const Config::params_t _param);

} // namespace NTRU
#endif // NTRU_H
