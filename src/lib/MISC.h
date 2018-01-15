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
    Polynomial::clsPoly inverse_AlmostInverseAlg_for2(Polynomial::clsPoly _p, unsigned int _N);
    Polynomial::clsPoly inverse_AlmostInverseAlg_forP(Polynomial::clsPoly _p, unsigned int _N, unsigned int _m);


    Polynomial::clsPoly inverse_NewtonIteration_for2(Polynomial::clsPoly _p,
                                                Polynomial::clsPoly _p_1,
                                                int _m, int _N);
    int inverse_ExtendedEuclidian(unsigned int _a, unsigned int _b);
    Polynomial::clsPoly increaseDegree(Polynomial::clsPoly _p);
    Polynomial::clsPoly deccreaseDegree(Polynomial::clsPoly _p);
    void updateK(unsigned int *k, Polynomial::clsPoly *_f, Polynomial::clsPoly *_c);

private:
    MISC();

};
} // namespace MISC
#endif // MISC_H
