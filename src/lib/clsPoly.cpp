#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "clsPoly.h"
namespace Polynomial {
clsPoly addPoly_mod(clsPoly _p1, clsPoly _p2, int _m)
{
    clsPoly *a,*b;
    if (_p1.Degree() > _p2.Degree()) {
        a = &_p1;
        b = &_p2;
    } else {
        b = &_p1;
        a = &_p2;
    }
    clsPoly res(a->Degree());
    for(unsigned int i = 0; i<= b->Degree(); i++) {        
        res.Coef[i]=(a->Coef[i]+b->Coef[i])%_m;
    }
    for(unsigned int j = b->Degree()+1; j<= a->Degree(); j++)
        res.Coef[j]=(a->Coef[j])%_m;
    return res;
}

clsPoly mulPoly_mod(clsPoly _p1, clsPoly _p2, int _m, u_int16_t _d)
{
    clsPoly res(_d);
    for (u_int16_t i = 0; i <=_p1.Degree(); i++) {
        for (u_int16_t j = 0; j <=_p2.Degree(); j++) {
            int curr_deg = (i+j) % (_d+1);
            while (curr_deg<0) curr_deg+=(_d+1);
            res.Coef[curr_deg] = ((_p1.Coef[i] * _p2.Coef[j]) + res.Coef[curr_deg]) % _m;
        }
    }
    res.refine();
    return res;
}

clsPoly mulPoly_mod(int _a, clsPoly _p, int _m)
{
    clsPoly res(_p.Degree());
    for (unsigned int i = 0; i <=_p.Degree(); i++)
        res.Coef[i] = (_p.Coef[i] * _a) % _m;
    return res;
}

void print_poly(clsPoly _p)
{
    for (unsigned int i =0; i < _p.Degree(); i++)
        std::cout << _p.Coef[i] << " X^" << i << " + ";
    std::cout << _p.Coef[_p.Degree()] << " X^" << _p.Degree() << std::endl;
}


void mulPoly(int _a, clsPoly *_p2)
{
    for(u_int16_t i=0; i<=_p2->Degree(); i++)
        _p2->Coef[i]*=_a;
}
clsPoly subPoly_mod(clsPoly _p1, clsPoly _p2, int _m)
{
    clsPoly minus_p2 = _p2;
    mulPoly(-1,&minus_p2);
    clsPoly res = addPoly_mod(_p1,minus_p2,_m);
    return res;
}

clsPoly mulPoly(clsPoly *_p1, clsPoly *_p2)
{
    clsPoly res(_p1->Degree()+_p2->Degree());
//    res.Degree = _degree;
    for (unsigned int i = 0; i <=_p1->Degree(); i++) {
        for (unsigned int j = 0; j <=_p2->Degree(); j++) {
            unsigned int curr_deg = (i+j);
            res.Coef[curr_deg] = ((_p1->Coef[i] * _p2->Coef[j]) + res.Coef[curr_deg]) ;
        }
    }    
    return res;
}















} // namespace Polynomial
