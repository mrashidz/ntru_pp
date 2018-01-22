#include <iostream>
#include "lib/NTRU.h"
using namespace std;

int main()
{

    Polynomial::clsPoly f(10),g(10),c,d,a(2),b(2),e;
    f.Coef[0]=-1;
    f.Coef[1]=1;
    f.Coef[2]=1;
    f.Coef[3]=0;
    f.Coef[4]=-1;
    f.Coef[5]=0;
    f.Coef[6]=1;
    f.Coef[7]=0;
    f.Coef[8]=0;
    f.Coef[9]=1;
    f.Coef[10]=-1;

    a.Coef[0] = -1;
//    a.Coef[1] = 1;
//    a.Coef[2] = 1;
//    b.Coef[0] = 0;
//    b.Coef[1] = 1;
//    a.Coef[3] = 1;
//    Polynomial::print_poly(a);
//    Polynomial::print_poly(b);
//    Polynomial::print_poly(Polynomial::addPoly_mod(a,b,3));
//    int wa=-1,wb=0;

//    cout << "inv: "<<(wa+wb)%3<< endl;
//    return 0;


//    int afv = MISC::inverse_ExtendedEuclidian(7,26);
//    cout << "inv: "<<afv << endl;

//    cout << "inv: "<< endl;
//    Polynomial::print_poly(MISC::inverse_AlmostInverseAlg_for3(f,11));
////    Polynomial::print_poly(MISC::MISC::instance().inverse_AlmostInverseAlg_forP(f,11,3));
//    Polynomial::clsPoly asasaaa, inv2 = MISC::inverse_AlmostInverseAlg_for2(f,11);
//    asasaaa = MISC::inverse_AlmostInverseAlg_for3(f,11);
//    Polynomial::print_poly(Polynomial::mulPoly_mod(f,asasaaa,3,10));
////    return 0;
//    asasaaa = Polynomial::mulPoly_mod(f,inv2,2,10);
//    Polynomial::print_poly(asasaaa);
//    Polynomial::print_poly(MISC::inverse_NewtonIteration_for2(f,inv2,32,11));

    return 0;
}
