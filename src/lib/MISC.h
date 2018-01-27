#ifndef MISC_H
#define MISC_H
#include "clsPoly.h"
#include <string>
/*
Parameter set       N       q       df      Known strength      Recommended security level
ees401ep1           401     2048    113         154.88                  112
ees541ep1           541     2048    49          141.766                 112
ees659ep1           659     2048    38          137.861                 112
ees449ep1           449     2048    134         179.899                 128
ees613ep1           613     2048    55          162.385                 128
ees761ep1           761     2048    42          157.191                 128
ees653ep1           653     2048    194         276.736                 192
ees887ep1           887     2048    81          245.126                 192
ees1087ep1          1087    2048    63          236.586                 192
ees853ep1           853     2048    268         376.32                  256
ees1171ep1          1171    2048    106         327.881                 256
ees1499ep1          1499    2048    79          312.949                 256
*/
#define EES401EP1 401
#define EES449EP1 449
#define EES653EP1 653
#define EES853EP1 853
#define EES541EP1 541
#define EES613EP1 613
#define EES887EP1 887
#define EES659EP1 659
#define EES761EP1 761
#define EES1171EP1 1171
#define EES1087EP1 1087
#define EES1499EP1 1499

const int8_t BIN_TO_TRIN_POLY_1[8] = {0, 0, 0, 1, 1, 1,-1,-1};
const int8_t BIN_TO_TRIN_POLY_2[8] = {0, 1,-1, 0, 1,-1, 0, 1};

namespace MISC {
class RND
{
public:
    static RND &instance() {
        static RND Instance;
        return Instance;
    }   
    inline int intLessThan(int _a) {return rand() % _a;}
    void fillPoly(Polynomial::clsPoly *_p, const u_int16_t _d, const int _val);
    void fillByte(unsigned char *_string, size_t _l);

private:
    RND();

};
} // namespace MISC
namespace Inverese {
Polynomial::clsPoly NewtonIteration_for2(Polynomial::clsPoly _p, Polynomial::clsPoly _p_1, int _m, int _N);
Polynomial::clsPoly forQ(Polynomial::clsPoly _p, unsigned int _N, unsigned int _Q);
Polynomial::clsPoly AI_forP(Polynomial::clsPoly _p, unsigned int _N, unsigned int _m); //Allmost Inverse
Polynomial::clsPoly AI_for3(Polynomial::clsPoly _p, unsigned int _N);
Polynomial::clsPoly AI_for2(Polynomial::clsPoly _p, unsigned int _N);
void updateK(unsigned int *k, Polynomial::clsPoly *_f, Polynomial::clsPoly *_c);
int ExtendedEuclidian(unsigned int _a, unsigned int _b);
} // namespace Inverese



namespace Config {
typedef struct params
{
    u_int16_t N;
    u_int16_t q;
//    u_int8_t prod_flag; //1 for product-form private keys, 0 for ternary
    u_int16_t df; //number of ones in the private polynomial f1 (if prod=1) or f (if prod=0)
//    u_int16_t df2; //number of ones in the private polynomial f2; ignored if prod=0
//    u_int16_t df3; //number of ones in the private polynomial f3; ignored if prod=0
    u_int16_t dg; //number of ones in the polynomial g (used during key generation)
//    u_int16_t dm0; //min number of -1's, 0's, and 1's in the polynomial m' -- the last encryption step
    u_int16_t db; //number of random bits to prepend to the message
    u_int16_t dr; //number of random bits to add to r in encryption
    u_int16_t c; //a parameter for the Index Generation Function
    u_int16_t maxMsgLen; // in bytes
//    u_int16_t min_calls_r; //min number of hash calls for the IGF to make
//    u_int16_t min_calls_mask; //min number of calls to generate the masking polynomial
//    u_int8_t hash_seed; //whether to hash the seed in the MGF first (1) or use the seed directly (0)
//    u_int8_t oid[3]; //three bytes that uniquely identify the parameter set
//    void (*hash)(u_int8_t[], u_int16_t, u_int8_t[]); // hash function, e.g. ntru_sha256
//    void (*hash_4way)(u_int8_t *[4], u_int16_t, u_int8_t *[4]); //hash function for 4 inputs, e.g. ntru_sha256_4way
//    void (*hash_8way)(u_int8_t *[8], u_int16_t, u_int8_t *[8]); //hash function for 8 inputs, e.g. ntru_sha256_8way
//    u_int16_t hlen; //output length of the hash function
//    u_int16_t pklen; //number of bits of the public key to hash
//    params();
}params_t;
params_t __EES401EP1__();
params_t __EES449EP1__();
params_t __EES653EP1__();
params_t __EES853EP1__();
params_t __EES541EP1__();
params_t __EES613EP1__();
params_t __EES887EP1__();
params_t __EES659EP1__();
params_t __EES761EP1__();
params_t __EES1171EP1__();
params_t __EES1087EP1__();
params_t __EES1499EP1__();
} //namespace Config
namespace  Converse {
Polynomial::clsPoly convert_BS2ROSP(unsigned char *_m, size_t _l, unsigned int _N);
Polynomial::clsPoly MbinToMtrin(const unsigned char *_m, size_t _l,const Config::params_t _param,const u_int16_t _max_len);
std::string MtrinToMbin(const Polynomial::clsPoly *_mtrin);
} // namespace  Conversion
#endif // MISC_H
