#ifndef MISC_H
#define MISC_H
#include "clsPoly.h"

namespace MISC {

class MISC
{
public:
    static MISC &instance() {
        static MISC Instance;
        return Instance;
    }
    Polynomial::clsPoly generateRandomPoly();
    Polynomial::clsPoly inverse_AlmostInverseAlg_for3(Polynomial::clsPoly _p, unsigned int _N);
    Polynomial::clsPoly inverse_AlmostInverseAlg_forP(Polynomial::clsPoly _p, unsigned int _N, unsigned int _m);
    int inverse_ExtendedEuclidian(unsigned int _a, unsigned int _b);
    Polynomial::clsPoly increaseDegree(Polynomial::clsPoly _p);
    Polynomial::clsPoly deccreaseDegree(Polynomial::clsPoly _p);

private:
    MISC();

};
} // namespace MISC
#endif // MISC_H
