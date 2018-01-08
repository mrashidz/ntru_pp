#ifndef NTRU_H
#define NTRU_H
#include "clsPoly.h"
namespace NTRU {

typedef struct
{
    Polynomial::clsPoly f;
    Polynomial::clsPoly f_p;
}priv_key_t;
typedef struct
{
    priv_key_t Sk;
    Polynomial::clsPoly Pk;

}key_pair_t;

key_pair_t generateKeyPair(unsigned int _N, unsigned int _q, unsigned int _p);
Polynomial::clsPoly encrypt(Polynomial::clsPoly _m, Polynomial::clsPoly _pk);
Polynomial::clsPoly decrypt(Polynomial::clsPoly _c, priv_key_t _Sk);

} // namespace NTRU
#endif // NTRU_H
