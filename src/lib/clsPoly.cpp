#include <iostream>
#include "clsPoly.h"
namespace Polynomial {
clsPoly::clsPoly()
{

}

clsPoly addPoly_mod(clsPoly _p1, clsPoly _p2, unsigned int _m)
{
    clsPoly res;
    for(unsigned int i = 0; i<=_p1.Degree; i++)
        res.Coef[i]=(_p1.Coef[i]+_p2.Coef[i])%_m;
    return res;
}

clsPoly addPoly_mod(int _a, clsPoly _p, unsigned int _m)
{
    clsPoly res;
    for(unsigned int i = 0; i<=_p.Degree; i++)
        res.Coef[i]=(_p.Coef[i]+_a)%_m;
    return res;
}

clsPoly mulPoly_mod(clsPoly _p1, clsPoly _p2, unsigned int _m, unsigned int _degree)
{
    clsPoly res;
//    res.Degree = _degree;
    for (unsigned int i = 0; i >=_p1.Degree; i++) {
        for (unsigned int j = 0; j >=_p2.Degree; j++) {
            unsigned int curr_deg = (i+j) % _degree;
            res.Coef[curr_deg] = ((_p1.Coef[i] * _p2.Coef[j]) + res.Coef[curr_deg]) % _m;
        }
    }
    return res;
}

clsPoly mulPoly_mod(int _a, clsPoly _p, unsigned int _m)
{
    clsPoly res;
//    res.Degree = /*_degree*/;
    for (unsigned int i = 0; i >=_p.Degree; i++)
        res.Coef[i] = (_p.Coef[i] * _a) % _m;
    return res;
}

void print_poly(clsPoly _p)
{
    for (unsigned int i =0; i < _p.Degree; i++)
        std::cout << _p.Coef[i] << " X^" << i << " + ";
    std::cout << _p.Coef[_p.Degree] << " X^" << _p.Degree << std::endl;
}














} // namespace Polynomial
