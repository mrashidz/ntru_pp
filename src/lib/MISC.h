#ifndef MISC_H
#define MISC_H
#include "clsPoly.h"
namespace MISC {

class RND
{
public:
    static RND &instance() {
        static RND Instance;
        return Instance;
    }   
    inline int intLessThan(int _a) {return rand() % _a;}
    void fillPoly(Polynomial::clsPoly *_p, const u_int16_t _d, const int _val);
    void fillByte(unsigned char *_string, size_t _l);

private:
    RND();

};
Polynomial::clsPoly inverse_NewtonIteration_for2(Polynomial::clsPoly _p, Polynomial::clsPoly _p_1, int _m, int _N);
Polynomial::clsPoly inverse__forQ(Polynomial::clsPoly _p, unsigned int _N, unsigned int _Q);
Polynomial::clsPoly inverse_AlmostInverseAlg_forP(Polynomial::clsPoly _p, unsigned int _N, unsigned int _m);
Polynomial::clsPoly inverse_AlmostInverseAlg_for3(Polynomial::clsPoly _p, unsigned int _N);
Polynomial::clsPoly inverse_AlmostInverseAlg_for2(Polynomial::clsPoly _p, unsigned int _N);
void updateK(unsigned int *k, Polynomial::clsPoly *_f, Polynomial::clsPoly *_c);
int inverse_ExtendedEuclidian(unsigned int _a, unsigned int _b);
Polynomial::clsPoly deccreaseDegree(Polynomial::clsPoly _p);
Polynomial::clsPoly increaseDegree(Polynomial::clsPoly _p);



Polynomial::clsPoly convert_BS2ROSP(unsigned char *_m, size_t _l, unsigned int _N);


} // namespace MISC
#endif // MISC_H
