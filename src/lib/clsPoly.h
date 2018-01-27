#ifndef CLSPOLY_H
#define CLSPOLY_H
#include <vector>
#include <stdlib.h>
#include <cstring>
namespace Polynomial {
class clsPoly { // TRUNCATED POLYNOMIAL OBJECTS
public:
    clsPoly();
    clsPoly(unsigned int _d);    
    void refine();
    void decreaseDeg();
    void zero();    
    inline bool isZero() {
        return this->Degree == 0 && this->Coef[0] ==0;
    }
    unsigned int Degree; // N-1
    std::vector<int> Coef; // a_[0 ~ N-1]
};
clsPoly addPoly_mod(clsPoly _p1, clsPoly _p2, int _m);
clsPoly subPoly_mod(clsPoly _p1, clsPoly _p2, int _m);
clsPoly mulPoly_mod(clsPoly _p1, clsPoly _p2, int _m, unsigned int _d);
clsPoly mulPoly(clsPoly *_p1, clsPoly *_p2);
clsPoly addPoly_mod(int _a, clsPoly _p, int _m);
clsPoly mulPoly_mod(int _a, clsPoly _p, int _m);
clsPoly inverse(clsPoly _p, unsigned int _a);
clsPoly inverse(clsPoly _p, unsigned int _a);
void print_poly(clsPoly _p);










} // namespace Polynomial
#endif // CLSPOLY_H
