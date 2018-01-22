#include "MISC.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include <cstring>

namespace MISC {

Polynomial::clsPoly
inverse_AlmostInverseAlg_for3(Polynomial::clsPoly _p, unsigned int _N) {
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

Polynomial::clsPoly inverse_AlmostInverseAlg_for2(Polynomial::clsPoly _p, unsigned int _N)
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

Polynomial::clsPoly inverse__forQ(Polynomial::clsPoly _p, unsigned int _N, unsigned int _Q)
{
    Polynomial::clsPoly p_2 = inverse_AlmostInverseAlg_for2(_p,_N);
    return inverse_NewtonIteration_for2(_p,p_2,_Q,_N);
}

Polynomial::clsPoly
inverse_NewtonIteration_for2(Polynomial::clsPoly _p,
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

Polynomial::clsPoly inverse_AlmostInverseAlg_forP(Polynomial::clsPoly _p, unsigned int _N, unsigned int _m)
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
            int u = inverse_ExtendedEuclidian(f.Coef[0],_m);
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
        int u = (inverse_ExtendedEuclidian(g.Coef[0],_m)*f.Coef[0])%_m;
        tmp = Polynomial::mulPoly_mod(u,g,_m);
        f = Polynomial::subPoly_mod(f,tmp,_m);
        tmp = Polynomial::mulPoly_mod(u,c,_m);
        b = Polynomial::subPoly_mod(b,tmp,_m);
        b.refine();
        f.refine();
    } while (true);
    return tmp;
}

int inverse_ExtendedEuclidian(unsigned int _a, unsigned int _b) {
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

Polynomial::clsPoly increaseDegree(Polynomial::clsPoly _p)
{
    Polynomial::clsPoly res(_p.Degree+1);
    if (_p.Degree == 0) {
        res.Coef[1]=1;
    } else {
        for (unsigned int i = 0; i <= _p.Degree; i++)
            res.Coef[i+1]=_p.Coef[i];
    }
    return res;
}

Polynomial::clsPoly deccreaseDegree(Polynomial::clsPoly _p)
{
    if (_p.Degree == 0) return _p; //shouldnt end up here!
    Polynomial::clsPoly res(_p.Degree-1);
    for (unsigned int i = 1; i <= _p.Degree; i++)
        res.Coef[i-1]=_p.Coef[i];
    return res;
}






} // namespace MISC
