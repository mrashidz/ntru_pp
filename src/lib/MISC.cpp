#include "MISC.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include <cstring>

namespace Inverese {

Polynomial::clsPoly
AI_for3(Polynomial::clsPoly _p, unsigned int _N) {
    unsigned int k = 0;
    Polynomial::clsPoly b(0),c(0),f=_p,g(_N),tmp;
    g.Coef[_N] = b.Coef[0] = 1;
    g.Coef[0] = -1;    
    Polynomial::clsPoly x(1);
    x.Coef[1] = 1;
    do {
        while (f.Coef[0]==0) {
            k++;
            f.decreaseDeg();
            f.refine();
            c = Polynomial::mulPoly(&c,&x);
            c.refine();
        }
        if (f.Degree == 0) {
            if (f.Coef[0]) {
                b.refine();
                k %=_N;
                x = Polynomial::clsPoly(_N-k);
                x.Coef[_N-k] = f.Coef[0];
                tmp = Polynomial::mulPoly_mod(b,x,3,_N-1);
                tmp.refine();
            } else
                tmp.zero();
            break;
        }
        if (f.Degree < g.Degree) {
            tmp = f;
            f = g;
            g = tmp;
            tmp = c;
            c = b;
            b = tmp;
        }
        if (f.Coef[0] == g.Coef[0]) {        
            f = Polynomial::subPoly_mod(f,g,3);
            b = Polynomial::subPoly_mod(b,c,3);

        } else {            
            f = Polynomial::addPoly_mod(f,g,3);
            b = Polynomial::addPoly_mod(b,c,3);
        }
        b.refine();
        f.refine();
    } while (true);
    return tmp;
}

Polynomial::clsPoly AI_for2(Polynomial::clsPoly _p, unsigned int _N)
{
    unsigned int k = 0;
    Polynomial::clsPoly b(0),c(0),f=_p,g(_N),tmp;
    g.Coef[_N] = b.Coef[0] = 1;
    g.Coef[0] = -1;
    Polynomial::clsPoly x(1);
    x.Coef[1] = 1;
    do {
        while (f.Coef[0]==0) {
            k++;
            f.decreaseDeg();
            f.refine();
            c = Polynomial::mulPoly(&c,&x);
            c.refine();
        }
        if (f.Degree == 0) {
            if (f.Coef[0]==1) {
                k %=_N;
                x = Polynomial::clsPoly(_N-k);
                x.Coef[_N-k] = f.Coef[0];
                tmp = Polynomial::mulPoly_mod(b,x,2,_N-1);
                tmp.refine();
            } else
                tmp.zero();
            break;
        }
        if (f.Degree < g.Degree) {
            tmp = f;
            f = g;
            g = tmp;
            tmp = c;
            c = b;
            b = tmp;
        }
        f = Polynomial::addPoly_mod(f,g,2);
        b = Polynomial::addPoly_mod(b,c,2);
        b.refine();
        f.refine();
    } while (true);
    return tmp;
}

Polynomial::clsPoly
NewtonIteration_for2(Polynomial::clsPoly _p,
                              Polynomial::clsPoly _p_1,
                              int _m,
                              int _N)
{
    Polynomial::clsPoly res = _p_1,two(0),tmp;
    two.Coef[0]=2;
    int q = 2;
    while (_m > q) {
//        q = std::pow(q,2);
        q *=2;
        std::cout << q << " < " << _m<< std::endl;
        if (q > 32) {
            std::cout << q << " > " << _m<< std::endl;
            break;
        }
        tmp = Polynomial::mulPoly_mod(_p,res,q,_N-1);
        tmp = Polynomial::subPoly_mod(two,tmp,q);
        res = Polynomial::mulPoly_mod(tmp,res,q,_N-1);

    }
    res.refine();
    res = Polynomial::addPoly_mod(0,res,_m);
    return res;
}

Polynomial::clsPoly forQ(Polynomial::clsPoly _p, unsigned int _N, unsigned int _Q)
{
    Polynomial::clsPoly p_2 = AI_for2(_p,_N);
    return NewtonIteration_for2(_p,p_2,_Q,_N);
}

Polynomial::clsPoly AI_forP(Polynomial::clsPoly _p, unsigned int _N, unsigned int _m)
{
    unsigned int k = 0;
    Polynomial::clsPoly b(0),c(0),f=_p,g(_N),tmp;
    g.Coef[_N] = b.Coef[0] = 1;
    g.Coef[0] = -1;
    Polynomial::clsPoly x(1);
    x.Coef[1] = 1;
    do {
        while (f.Coef[0]==0) {
            k++;
            f.decreaseDeg();
            f.refine();
            c = Polynomial::mulPoly(&c,&x);
            c.refine();
        }
        if (f.Degree == 0) {
            int u = ExtendedEuclidian(f.Coef[0],_m);
            b = Polynomial::mulPoly_mod(u,b,_m);
//            b.refine();
            k %=_N;
            x = Polynomial::clsPoly(_N-k);
            x.Coef[_N-k] = f.Coef[0];
            tmp = Polynomial::mulPoly_mod(b,x,_m,_N-1);
            tmp.refine();

            break;
        }
        if (f.Degree < g.Degree) {
            tmp = f;
            f = g;
            g = tmp;
            tmp = c;
            c = b;
            b = tmp;
        }
        int u = (ExtendedEuclidian(g.Coef[0],_m)*f.Coef[0])%_m;
        tmp = Polynomial::mulPoly_mod(u,g,_m);
        f = Polynomial::subPoly_mod(f,tmp,_m);
        tmp = Polynomial::mulPoly_mod(u,c,_m);
        b = Polynomial::subPoly_mod(b,tmp,_m);
        b.refine();
        f.refine();
    } while (true);
    return tmp;
}

int ExtendedEuclidian(unsigned int _a, unsigned int _b) {
    unsigned int /*gcd = 0,*/r =0,r_prime=0, x = 1, x_prime = 0,y=0,y_prime=1,dev=0,tmp = 0;
    int reverse = -1;
    r = _b;
    r_prime = _a%_b;
//    unsigned char i = 1;
    while (r_prime != 0) {
        dev = r/r_prime;
        tmp = r;
        r = r_prime;
        r_prime = tmp - (dev*r_prime);
        tmp = x;
        x = x_prime;
        x_prime = tmp - (dev*x_prime);
        tmp = y;
        y = y_prime;
        y_prime = tmp - (dev*y_prime);
    }
    //since we are not using these variable anymore, using them as temp to print nice formula
    r = _b*x;
    r_prime=(_a%_b)*y;
    if (r+r_prime == 1) {
//        while (reverse < 0)
            reverse = y;//(y+=_b)%_b; //get rid of the minus
    }
    return reverse;
}

} // namespace Inverese

namespace MISC {
void RND::fillPoly(Polynomial::clsPoly *_p,const u_int16_t _d, const int _val)
{
    u_int16_t i,t = 0;
    while (t < _d) {
        i = this->intLessThan(_p->Degree+1);
        if (!_p->Coef[i]) {
            _p->Coef[i] = _val;
            t++;
        }
    }
}

void RND::fillByte(unsigned char *_string, size_t _l)
{
    unsigned char tmp;
    for (int i = 0; i < _l; i++) {
        tmp = (unsigned char)rand();
        memcpy(_string+i,&tmp,sizeof(unsigned char));
    }
}

RND::RND()
{
    srand (time(NULL));

}

} // namespace MISC

namespace Converse {
Polynomial::clsPoly MbinToMtrin(const unsigned char *_m, size_t _l,const Config::params_t _param,const u_int16_t _max_len){

    Polynomial::clsPoly Mtrin(_param.N-1);
    u_int16_t db_byte = _param.db/8;
    u_int16_t Mbin_len = db_byte + 1 + _max_len + 1;
    // creat M and b
    u_int8_t b[db_byte],Mbin[Mbin_len];
    MISC::RND::instance().fillByte(b,db_byte);
    memcpy(&Mbin,&b,db_byte);
    u_int8_t *M_head = (u_int8_t*)&Mbin + db_byte;
    *M_head = _l;
    M_head++;
    memcpy(M_head, _m, _l);
    M_head += _l;
    memset(M_head, 0, _max_len+1-_l);
    //convert Mbin to Mtrin
    u_int16_t Mtrin_idx = 0;
    //32 > 3*8=24
    int32_t tmp;
    uint16_t i = 0;
    while (i<(Mbin_len+2)/3*3 && Mtrin_idx<_param.N-1) { //wtf
        tmp = (unsigned char)Mbin[i+2];
        tmp <<= 8;
        tmp += (unsigned char)Mbin[i+1];
        tmp <<= 8;
        tmp += (unsigned char)Mbin[i];
        i += 3;
        uint8_t j;
        for (j=0; j<8 && Mtrin_idx<_param.N-1; j++) {
            unsigned char k = tmp & 7;
            Mtrin.Coef[Mtrin_idx++] = BIN_TO_TRIN_POLY_1[k];
            Mtrin.Coef[Mtrin_idx++] = BIN_TO_TRIN_POLY_2[k];
            tmp >>= 3;
        }
    }
    return Mtrin;
}

std::string MtrinToMbin(const Polynomial::clsPoly *_mtrin) {
    std::string res;
    u_int16_t c1, c2, c3, i = 0;
    int coef1,coef2,coef3,coef4,coef5,coef6;
    char data[3] = {0,0,0};
    while (i < _mtrin->Degree) {
        coef1 = _mtrin->Coef[i++];
        coef2 = _mtrin->Coef[i++];
        coef3 = _mtrin->Coef[i++];
        coef4 = _mtrin->Coef[i++];
        coef5 = _mtrin->Coef[i++];
        coef6 = _mtrin->Coef[i++];
//        if (coeff1==2 && coeff2==2)
//            valid = 0;
        c1 = 3*coef1 + coef2;
        c2 = 3*coef3 + coef4;
        c3 = 3*coef5 + coef6;
        data[0] = (c1<<5) | (c2<<2) | (c3>>1);
        data[1] = (c3<<7);

        coef1 = _mtrin->Coef[i++];
        coef2 = _mtrin->Coef[i++];
        coef3 = _mtrin->Coef[i++];
        coef4 = _mtrin->Coef[i++];
        coef5 = _mtrin->Coef[i++];
        coef6 = _mtrin->Coef[i++];
//        if (coeff1==2 && coeff2==2)
//            valid = 0;
        c1 = 3*coef1 + coef2;
        c2 = 3*coef3 + coef4;
        c3 = 3*coef5 + coef6;
        data[1] |= (c1<<4) | (c2<<1) | (c3>>2);
        data[2] = (c3 << 6);
        coef1 = _mtrin->Coef[i++];
        coef2 = _mtrin->Coef[i++];
        coef3 = _mtrin->Coef[i++];
        coef4 = _mtrin->Coef[i++];
//        if (coeff1==2 && coeff2==2)
//            valid = 0;
        c1 = 3*coef1 + coef2;
        c2 = 3*coef3 + coef4;
        data[2] |=  (c1<<3) | c2;
        res.append(data);
    }
    return res;
}

} // namespace Converse

namespace Config {

params_t __EES401EP1__() {
    params_t _p;
    _p.N = 401;
    _p.q = 2048;
    _p.df = 113;
    _p.dg = 133;
    _p.db = 112;
    _p.maxMsgLen = 60;
    _p.dr = 113;
    _p.c = 11;
    return _p;
}

params_t __EES449EP1__() {
    params_t _p;
    _p.N = 449;
    _p.q = 2048;
    _p.df = 134;
    _p.dg = 149;
    _p.db = 128;
    _p.maxMsgLen = 67;
    _p.dr = 134;
    _p.c = 9;
    return _p;
}

params_t __EES653EP1__() {
    params_t _p;
    _p.N = 653;
    _p.q = 2048;
    _p.df = 194;
    _p.dg = 217;
    _p.db = 192;
    _p.maxMsgLen = 97;
    _p.dr = 194;
    _p.c = 11;
    return _p;
}

params_t __EES853EP1__() {
    params_t _p;
    _p.N = 853;
    _p.q = 2048;
    _p.df = 268;
    _p.dg = 284;
    _p.db = 256;
    _p.maxMsgLen = 126;
    _p.dr = 268;
    _p.c = 10;
    return _p;
}

params_t __EES541EP1__() {
    params_t _p;
    _p.N = 541;
    _p.q = 2048;
    _p.df = 49;
    _p.dg = 180;
    _p.db = 112;
    _p.maxMsgLen = 86;
    _p.dr = 49;
    _p.c = 12;
    return _p;
}

params_t __EES613EP1__() {
    params_t _p;
    _p.N = 613;
    _p.q = 2048;
    _p.df = 55;
    _p.dg = 204;
    _p.db = 128;
    _p.maxMsgLen = 97;
    _p.dr = 55;
    _p.c = 11;
    return _p;
}

params_t __EES887EP1__() {
    params_t _p;
    _p.N = 887;
    _p.q = 2048;
    _p.df = 81;
    _p.dg = 295;
    _p.db = 192;
    _p.maxMsgLen = 141;
    _p.dr = 81;
    _p.c = 10;
    return _p;
}

params_t __EES659EP1__() {
    params_t _p;
    _p.N = 659;
    _p.q = 2048;
    _p.df = 38;
    _p.dg = 219;
    _p.db = 112;
    _p.maxMsgLen = 108;
    _p.dr = 38;
    _p.c = 11;
    return _p;
}
params_t __EES1171EP1__() {
    params_t _p;
    _p.N = 1171;
    _p.q = 2048;
    _p.df = 106;
    _p.dg = 390;
    _p.db = 356;
    _p.maxMsgLen = 186;
    _p.dr = 106;
    _p.c = 10;
    return _p;
}

params_t __EES761EP1__() {
    params_t _p;
    _p.N = 761;
    _p.q = 2048;
    _p.df = 42;
    _p.dg = 253;
    _p.db = 128;
    _p.maxMsgLen = 125;
    _p.dr = 42;
    _p.c = 12;
    return _p;
}


params_t __EES1087EP1__() {
    params_t _p;
    _p.N = 1087;
    _p.q = 2048;
    _p.df = 63;
    _p.dg = 362;
    _p.db = 192;
    _p.maxMsgLen = 178;
    _p.dr = 63;
    _p.c = 13;
    return _p;
}

params_t __EES1499EP1__() {
    params_t _p;
    _p.N = 1499;
    _p.q = 2048;
    _p.df = 79;
    _p.dg = 499;
    _p.db = 256;
    _p.maxMsgLen = 247;
    _p.dr = 79;
    _p.c = 13;
    return _p;
}


} //namespace Config
