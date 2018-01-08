#ifndef CLSPOLY_H
#define CLSPOLY_H
#include <vector>
namespace Polynomial {
class clsPoly { // TRUNCATED POLYNOMIAL OBJECTS
public:
    clsPoly();
    unsigned int Degree; // N-1
    std::vector<unsigned int> Coef; // a_[0 ~ N-1]
};
clsPoly addPoly_mod(clsPoly _p1, clsPoly _p2, unsigned int _m);
clsPoly mulPoly_mod(clsPoly _p1, clsPoly _p2, unsigned int _m, unsigned int _degree);
clsPoly addPoly_mod(int _a, clsPoly _p, unsigned int _m);
clsPoly mulPoly_mod(int _a, clsPoly _p, unsigned int _m);

void print_poly(clsPoly _p);










} // namespace Polynomial
#endif // CLSPOLY_H
