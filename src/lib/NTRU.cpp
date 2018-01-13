#include "NTRU.h"
namespace NTRU {

key_pair_t generateKeyPair(unsigned int _N, unsigned int _q, unsigned int _p)
{
    bool foundProperPolyF = false;
    key_pair_t kp;
    Polynomial::clsPoly f(_N-1),g(_N-1),f_q,f_p;
    //check the first coef?!
//    g.randInit();//?????
    while (!foundProperPolyF) {
//        f.randInit();
        f_p = Polynomial::inverse(f,_p);
        f_q = Polynomial::inverse(f,_q);
        if (f_p.Degree && f_q.Degree)
            foundProperPolyF = true; //break
    }
    Polynomial::clsPoly tmp = Polynomial::mulPoly_mod(_p,f_q,_q);
    kp.Pk = Polynomial::mulPoly_mod(tmp,g,_q,_N-1);
    kp.Sk.f = f;
    kp.Sk.f_p = f_p;
    return kp;
}

Polynomial::clsPoly encrypt(Polynomial::clsPoly _m, Polynomial::clsPoly _pk)
{
    Polynomial::clsPoly res,r,tmp;
//    r.randInit();/////?????
    unsigned int q,d;///this should be embedded int he public key!
    tmp = Polynomial::mulPoly_mod(_m,r,q,d);
    res = Polynomial::addPoly_mod(_m,tmp,q);
    return res;
}

Polynomial::clsPoly decrypt(Polynomial::clsPoly _c, priv_key_t _Sk)
{
    Polynomial::clsPoly res,a,b;
    unsigned int p,q,d;///this should be embedded int he key!
    a = Polynomial::mulPoly_mod(_c,_Sk.f,q,d);
    b = Polynomial::mulPoly_mod(1,a,p);
    res = Polynomial::mulPoly_mod(_Sk.f_p,b,p,d);
    return res;
}



} // namespace NTRU
