#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "clsPoly.h"
namespace Polynomial {
clsPoly::clsPoly()
{
    this->Degree = 0;
    this->Coef.resize(1);
    this->Coef[0]=0;
}

clsPoly::clsPoly(unsigned int _d):Degree(_d)
{
    this->Coef.resize(_d+1);//constant coef +1
    for (unsigned int i = 0; i <= this->Degree; i++)
        this->Coef[i]=0;

}

void clsPoly::refine()
{
    std::vector<int> tmp = this->Coef;
    int deg = this->Degree;
    while (deg>=0&&this->Coef[deg]==0) --deg;
    if (this->Degree != deg) {
        this->Coef.clear();
        if (deg > -1) {
            this->Degree = deg;
            this->Coef.resize(this->Degree+1);
            for (unsigned int i = 0; i <= this->Degree; i++)
                this->Coef[i] = tmp[i];
        } else {
            this->Coef.resize(1);
            this->Degree = 0;
            this->Coef[0]=0;
        }
    }

}

void clsPoly::decreaseDeg()
{
    if (this->Degree == 0) return; //shouldnt end up here!
    std::vector<int> tmp = this->Coef;

    for (unsigned int i = 1; i <= this->Degree; i++)
        this->Coef[i-1] = tmp[i];
    this->Degree--;
}

//void clsPoly::randInit()
//{
////    srand (time(NULL));
//    int a = rand();
//    std::cout << "\n***started" << std::endl;
//    (a & 1) ? this->Coef[0] = 1 : this->Coef[0] = -1;
//    std::cout << a << std::endl;


//    for (unsigned int i = 1; i < this->Degree; i++) {
//        a = rand()%3;
//        if (a==2)a=-1;
//        std::cout << a << std::endl;
//        this->Coef[i] = a;

////        if (a % 7) {
////            a = rand();
////            std::cout << a << std::endl;
////            (a % 4) ? this->Coef[i] = 1 : this->Coef[i] = -1;
////        } else {
////        }
//    }
//    a = rand();
//    (a & 1) ? this->Coef[this->Degree] = 1 : this->Coef[this->Degree] = -1;
//}

clsPoly addPoly_mod(clsPoly _p1, clsPoly _p2, int _m)
{
    clsPoly *a,*b;
    if (_p1.Degree > _p2.Degree) {
        a = &_p1;
        b = &_p2;
    } else {
        b = &_p1;
        a = &_p2;
    }
    clsPoly res(a->Degree);
    for(unsigned int i = 0; i<= b->Degree; i++) {
        res.Coef[i]=(a->Coef[i]+b->Coef[i])%_m;
//        std::cout <<a->Coef[i] << " " <<b->Coef[i]<< " " << res.Coef[i]<< " " << (a->Coef[i]+b->Coef[i]) << " " <<(a->Coef[i]+b->Coef[i])%3<<" " <<_m<< std::endl;
    }
    for(unsigned int j = b->Degree+1; j<= a->Degree; j++)
        res.Coef[j]=(a->Coef[j])%_m;
    return res;
}

clsPoly addPoly_mod(int _a, clsPoly _p, int _m)
{
    clsPoly res = _p;
    res.Coef[0]=(_p.Coef[0]+_a)%_m;
    return res;
}

clsPoly mulPoly_mod(clsPoly _p1, clsPoly _p2, int _m, unsigned int _N)
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

clsPoly mulPoly_mod(int _a, clsPoly _p, int _m)
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

clsPoly minPoly_mod(clsPoly _p1, clsPoly _p2, int _m)
{
    clsPoly minus_p2(_p2.Degree);
    for(unsigned int i = 0; i<=_p2.Degree; i++)
        minus_p2.Coef[i]= -1*_p2.Coef[i];
    return addPoly_mod(_p1,minus_p2,_m);
}

clsPoly mulPoly(clsPoly _p1, clsPoly _p2)
{
    clsPoly res(_p1.Degree+_p2.Degree);
//    res.Degree = _degree;
    for (unsigned int i = 0; i <=_p1.Degree; i++) {
        for (unsigned int j = 0; j <=_p2.Degree; j++) {
            unsigned int curr_deg = (i+j);
            res.Coef[curr_deg] = ((_p1.Coef[i] * _p2.Coef[j]) + res.Coef[curr_deg]) ;
        }
    }
    return res;

}














} // namespace Polynomial
