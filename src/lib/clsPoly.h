#ifndef CLSPOLY_H
#define CLSPOLY_H
#include <vector>
#include <stdlib.h>
#include <cstring>
namespace Polynomial {
class clsPoly { // TRUNCATED POLYNOMIAL OBJECTS
public:
    clsPoly() {
        this->Coef.resize(1);
        this->Coef[0]=0;
    }
    clsPoly(const u_int16_t _d) {
        this->Coef.resize(_d+1);//constant coef +1
        for (unsigned int i = 0; i <= this->Degree(); i++)
            this->Coef[i]=0;
    }
    inline void refine() {
        while (this->Degree()>0 && this->Coef[this->Degree()]==0)
            this->Coef.pop_back();
    }
    inline void decreaseDeg() {
            this->Coef.erase(this->Coef.begin());
    }
    inline void zero() {
        this->Coef.resize(1);
        this->Coef [0] = 0;
    }
    inline void clearCoef(u_int16_t _d) {
        this->Coef.clear();
        this->Coef.resize(_d+1);        
    }
    inline bool isZero() {
        return this->Degree() == 0 && this->Coef[0] ==0;
    }
    inline u_int16_t Degree(){
        size_t a = this->Coef.size();
        if (a) a--;
        return a;
    } // N-1
    inline void applyMod(const u_int16_t _mod) {
        for (u_int16_t i = 0; i <=this->Degree(); i++)
            this->Coef[i]%=_mod;
        this->refine();
    }
    inline void applyMod_pos(const u_int16_t _mod) {
        for (u_int16_t i = 0; i <=this->Degree(); i++) {
            int a = this->Coef[i]%_mod;
            while (a<0)a+=_mod;
            this->Coef[i] =a;
        }
        this->refine();
    }
    std::vector<int> Coef; // a_[0 ~ N-1]
};
clsPoly addPoly_mod(clsPoly _p1, clsPoly _p2, int _m);
clsPoly subPoly_mod(clsPoly _p1, clsPoly _p2, int _m);
clsPoly mulPoly_mod(clsPoly _p1, clsPoly _p2, int _m, u_int16_t _d);
clsPoly mulPoly(clsPoly *_p1, clsPoly *_p2);
void mulPoly(int _a, clsPoly *_p2);
clsPoly mulPoly_mod(int _a, clsPoly _p, int _m);

void print_poly(clsPoly _p);










} // namespace Polynomial
#endif // CLSPOLY_H
