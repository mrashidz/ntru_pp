#include "MISC.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

namespace MISC {

Polynomial::clsPoly MISC::inverse_AlmostInverseAlg_for3(Polynomial::clsPoly _p, unsigned int _N)
{
    int k = 0;
    Polynomial::clsPoly b(0),c(0),f,g(_N),tmp;
    f = _p;
    g.Coef[_N] = 1;
    g.Coef[0] = -1;
    b.Coef[0] = 1;
    Polynomial::clsPoly x(1);
    x.Coef[1] = 1;
    std::cout << "Inverse of polynomial" << std::endl;
    Polynomial::print_poly(f);
    std::cout << "in mod 3 for g(x):" << std::endl;
    Polynomial::print_poly(g);
    std::cout << "b(x):" << std::endl;
    Polynomial::print_poly(b);
    std::cout << "c(x):" << std::endl;
    Polynomial::print_poly(c);
    std::cout << "x(x):" << std::endl;
    Polynomial::print_poly(x);
    std::cout << "---------------" << std::endl;//found


    int asd = 0;
    do {
        ++asd;
        std::cout << "........................................................"<< std::endl;//found
        while (f.Coef[0]==0) {
            std::cout << ">>> K:" << k << std::endl;//found
            k++;
            f.decreaseDeg();
            f.refine();
            std::cout << "+++ f decreased:" << std::endl;
            Polynomial::print_poly(f);

            c = Polynomial::mulPoly(c,x);
            c.refine();
            std::cout << "+++ c times x:" << std::endl;
            Polynomial::print_poly(c);
        }


        if (f.Degree == 0) {
            if (f.Coef[0])
                std::cout << "?!?!?!?!?!?!?!?!?!?!?!?\n\n\n\n\n\n\n\n\nfound" << std::endl;//found
            else
                std::cout << "?!?!?!?!?!?!?!?!?!?!?!?\n\n\n\n\n\n\n\n\nnot invertable" << std::endl;//found
            break;
        }
        if (f.Degree < g.Degree) {
            std::cout << "--- SWAP ---" << std::endl;
            tmp = f;
            f = g;
            g = tmp;
            tmp = c;
            c = b;
            b = tmp;
            std::cout << "f(x)" << std::endl;
            Polynomial::print_poly(f);
            std::cout << "g(x):" << std::endl;
            Polynomial::print_poly(g);
            std::cout << "b(x):" << std::endl;
            Polynomial::print_poly(b);
            std::cout << "c(x):" << std::endl;
            Polynomial::print_poly(c);

        }
        if (f.Coef[0] == g.Coef[0]) {
            std::cout << ".:: EQUL ::." << g.Coef[0]<< f.Coef[0] << std::endl;
            f = Polynomial::minPoly_mod(f,g,3);
            f.refine();
            b = Polynomial::minPoly_mod(b,c,3);
            b.refine();
            std::cout << "f(x)" << std::endl;
            Polynomial::print_poly(f);
            std::cout << "b(x):" << std::endl;
            Polynomial::print_poly(b);
        } else {
            std::cout << "!!! NEQUL !!!" <<  g.Coef[0]<< f.Coef[0] << std::endl;
            f = Polynomial::addPoly_mod(f,g,3);
            b = Polynomial::addPoly_mod(b,c,3);
            f.refine();
            b.refine();
            std::cout << "f(x)" << std::endl;
            Polynomial::print_poly(f);
            std::cout << "b(x):" << std::endl;
            Polynomial::print_poly(b);
        }
    } while (asd < 20);
//    std::cout << "f " <<  f.Degree << std::endl;//found
    return Polynomial::clsPoly(1);
}

Polynomial::clsPoly MISC::inverse_AlmostInverseAlg_forP(Polynomial::clsPoly _p, unsigned int _N, unsigned int _m)
{
    int k = 0;
    Polynomial::clsPoly b(0),c(0),f,g(_N),tmp;
    f = _p;
    g.Coef[_N] = 1;
    g.Coef[0] = -1;
    b.Coef[0] = 1;
    do {
        f = this->deccreaseDegree(f);
        c = this->increaseDegree(c);
        k++;
        if (f.Degree == 0) std::cout << "found" << std::endl;//found
        if (f.Degree < g.Degree) {
            tmp = f;
            f = g;
            g = tmp;
            tmp = c;
            c = b;
            b = tmp;
        }
        int u = (this->inverse_ExtendedEuclidian(g.Coef[0],_m)*f.Coef[0])%_m;
        tmp = Polynomial::mulPoly_mod(u,g,_m);
        f = Polynomial::minPoly_mod(f,tmp,_m);
        tmp = Polynomial::mulPoly_mod(u,c,_m);
        b = Polynomial::minPoly_mod(b,tmp,_m);
    } while (f.Coef[0]==0);
}

int MISC::inverse_ExtendedEuclidian(unsigned int _a, unsigned int _b) {
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

MISC::MISC()
{
    srand (time(NULL));

}

Polynomial::clsPoly MISC::increaseDegree(Polynomial::clsPoly _p)
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

Polynomial::clsPoly MISC::deccreaseDegree(Polynomial::clsPoly _p)
{
    if (_p.Degree == 0) return _p; //shouldnt end up here!
    Polynomial::clsPoly res(_p.Degree-1);
    for (unsigned int i = 1; i <= _p.Degree; i++)
        res.Coef[i-1]=_p.Coef[i];
    return res;
}



} // namespace MISC
