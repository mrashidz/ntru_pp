#ifndef NTRU_H
#define NTRU_H
#include <string>
#include "MISC.h"
namespace NTRU {
typedef struct params
{
    char Name[11];
    u_int16_t N;
    u_int16_t q;
//    u_int8_t prod_flag; //1 for product-form private keys, 0 for ternary
    u_int16_t df; //number of ones in the private polynomial f1 (if prod=1) or f (if prod=0)
//    u_int16_t df2; //number of ones in the private polynomial f2; ignored if prod=0
//    u_int16_t df3; //number of ones in the private polynomial f3; ignored if prod=0
    u_int16_t dg; //number of ones in the polynomial g (used during key generation)
    u_int16_t dm0; //min number of -1's, 0's, and 1's in the polynomial m' -- the last encryption step
    u_int16_t db; //number of random bits to prepend to the message
     u_int16_t dr; //number of random bits to add to r in encryption
    u_int16_t c; //a parameter for the Index Generation Function
    u_int16_t min_calls_r; //min number of hash calls for the IGF to make
    u_int16_t min_calls_mask; //min number of calls to generate the masking polynomial
    u_int8_t hash_seed; //whether to hash the seed in the MGF first (1) or use the seed directly (0)
    u_int8_t oid[3]; //three bytes that uniquely identify the parameter set
    void (*hash)(u_int8_t[], u_int16_t, u_int8_t[]); // hash function, e.g. ntru_sha256
    void (*hash_4way)(u_int8_t *[4], u_int16_t, u_int8_t *[4]); //hash function for 4 inputs, e.g. ntru_sha256_4way
    void (*hash_8way)(u_int8_t *[8], u_int16_t, u_int8_t *[8]); //hash function for 8 inputs, e.g. ntru_sha256_8way
    u_int16_t hlen; //output length of the hash function
    u_int16_t pklen; //number of bits of the public key to hash
    params() {}
}params_t;

typedef struct
{
    Polynomial::clsPoly f;
    Polynomial::clsPoly f_p;
}priv_key_t;
typedef struct
{
    Polynomial::clsPoly h;
    params_t Param;
}pub_key_t;
typedef struct
{
    priv_key_t Sk;
    pub_key_t Pk;

}key_pair_t;


key_pair_t generateKeyPair(const params_t _param);
Polynomial::clsPoly MbinToMtrin(const unsigned char *_m, size_t _l, params_t _param, u_int16_t _max_len);
std::string MtrinToMbin(const Polynomial::clsPoly *_mtrin);
Polynomial::clsPoly encrypt(const unsigned char *_m, const size_t _l, const pub_key_t _pk);
Polynomial::clsPoly decrypt(Polynomial::clsPoly _e, key_pair_t _k);

} // namespace NTRU
#endif // NTRU_H
