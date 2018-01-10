#include <iostream>
#include "lib/clsPoly.h"
using namespace std;

int main()
{

    Polynomial::clsPoly f(10),g(10),c,d,a(2),b(2),e;
    f.Coef[0]=5;
    f.Coef[1]=9;
    f.Coef[2]=6;
    f.Coef[3]=16;
    f.Coef[4]=4;
    f.Coef[5]=15;
    f.Coef[6]=16;
    f.Coef[7]=22;
    f.Coef[8]=20;
    f.Coef[9]=18;
    f.Coef[10]=30;

    g.Coef[0]=-1;
    g.Coef[1]=0;
    g.Coef[2]=1;
    g.Coef[3]=1;
    g.Coef[4]=0;
    g.Coef[5]=1;
    g.Coef[6]=0;
    g.Coef[7]=0;
    g.Coef[8]=-1;
    g.Coef[9]=0;
    g.Coef[10]=-1;
//    a.Degree = b.Degree = 3;
    Polynomial::print_poly(f);
    Polynomial::print_poly(g);
    c = Polynomial::mulPoly_mod(3,f,32);
    Polynomial::print_poly(c);
    d = Polynomial::mulPoly_mod(c,g,32,10);
    Polynomial::print_poly(d);

    cout << "Hello World!" << endl;



    a.Coef[0]=2;
    a.Coef[1]=-1;
    a.Coef[2]=3;
    b.Coef[0]=1;
    b.Coef[1]=2;
    b.Coef[2]=-1;
    e = Polynomial::mulPoly_mod(a,b,32,2);
    Polynomial::print_poly(e);

    return 0;
}
