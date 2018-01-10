#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "clsPoly.h"
namespace Polynomial {
clsPoly::clsPoly()
{
    this->Degree = 0;
    this->Coef.resize(0);
}

clsPoly::clsPoly(unsigned int _d):Degree(_d)
{
    this->Coef.resize(_d+1);//constant coef +1
    for (unsigned int i = 0; i <= this->Degree; i++)
        this->Coef[i]=0;

}

void clsPoly::randInit(unsigned int _m)
{
    srand (time(NULL));
    for (unsigned int i = 0; i <= this->Degree; i++)
        this->Coef[i] = rand() % _m;
}

clsPoly addPoly_mod(clsPoly _p1, clsPoly _p2, unsigned int _m)
{
    clsPoly res(_p1.Degree);
    for(unsigned int i = 0; i<=_p1.Degree; i++)
        res.Coef[i]=(_p1.Coef[i]+_p2.Coef[i])%_m;
    return res;
}

clsPoly addPoly_mod(int _a, clsPoly _p, unsigned int _m)
{
    clsPoly res(_p.Degree);
    for(unsigned int i = 0; i<=_p.Degree; i++)
        res.Coef[i]=(_p.Coef[i]+_a)%_m;
    return res;
}

clsPoly mulPoly_mod(clsPoly _p1, clsPoly _p2, unsigned int _m, unsigned int _N)
{
    clsPoly res(_N);
//    res.Degree = _degree;
    for (unsigned int i = 0; i <=_p1.Degree; i++) {
        for (unsigned int j = 0; j <=_p2.Degree; j++) {
            unsigned int curr_deg = (i+j) % (_N+1);
            res.Coef[curr_deg] = ((_p1.Coef[i] * _p2.Coef[j]) + res.Coef[curr_deg]) % _m;
        }
    }
    return res;
}

clsPoly mulPoly_mod(int _a, clsPoly _p, unsigned int _m)
{
    clsPoly res(_p.Degree);
//    res.Degree = /*_degree*/;
    for (unsigned int i = 0; i <=_p.Degree; i++)
        res.Coef[i] = (_p.Coef[i] * _a) % _m;
    return res;
}

void print_poly(clsPoly _p)
{
    for (unsigned int i =0; i < _p.Degree; i++)
        std::cout << _p.Coef[i] << " X^" << i << " + ";
    std::cout << _p.Coef[_p.Degree] << " X^" << _p.Degree << std::endl;
}

clsPoly inverse(clsPoly _p, unsigned int _a)
{
    clsPoly res;
    return res;
}














} // namespace Polynomial
