#include "NTRU.h"
#include <iostream>

namespace NTRU {

key_pair_t generateKeyPair(const Config::params_t _param) {
    key_pair_t keyPair;
    keyPair.Pk.Param = _param;
    int p = 3;
    Polynomial::clsPoly f_p(_param.N-1),f_q(_param.N-1),tmp(_param.N-1),
            f(_param.N-1),g(_param.N-1),h(_param.N-1),g_q(_param.N-1);    
    while (true){ //when shall we termiante?!
        f_p.clearCoef(_param.N-1);
        //generating random polynomial f_p
        MISC::RND::instance().fillPoly(&f_p,_param.df,1);
        MISC::RND::instance().fillPoly(&f_p,_param.df,-1);

        f_p.refine();        
        //calculating polynomial f, multiplicative invers of f_p in mod p
        f = Polynomial::mulPoly_mod(3,f_p,_param.q);
        f.Coef[0]++;
        //calculating polynomial f_q, multiplicative invers of f in mod q
        f_q = Inverese::forQ(f,_param.N,_param.q);
        if (!f_q.isZero())
            break;        
    }
    while (true) { //when shall we termiante?!
        g.clearCoef(_param.N-1);
        MISC::RND::instance().fillPoly(&g,_param.dg,1);
        MISC::RND::instance().fillPoly(&g,_param.dg,-1);
        g.refine();
        g.Coef[0]=1;
        //calculating polynomial g_q, multiplicative invers of g in mod q
        g_q = Inverese::forQ(g,_param.N,_param.q);
        if (!g_q.isZero())
            break;

    }    
//    f_q.applyMod(3);
    tmp = Polynomial::mulPoly_mod(f_q,g,_param.q,_param.N-1);
    h = Polynomial::mulPoly_mod(3,tmp,_param.q);
//    tmp = Polynomial::mulPoly_mod(f,h,_param.q,_param.N-1);
//    tmp = f;
//    tmp.applyMod(3);
    h.refine();
//    h.applyMod(3);
//    h.refine();
//    Polynomial::print_poly(tmp);
//    if (tmp.Degree() == 0)
//        exit(-1);

    keyPair.Pk.h = h;
    keyPair.Sk = f;
//    Polynomial::clsPoly test(0);
//    test.Coef[0]=1;

//    keyPair.Sk.f_p = test;
    return keyPair;
}


Polynomial::clsPoly chie;
Polynomial::clsPoly encrypt(const unsigned char *_m, const size_t _l, const pub_key_t _pk) {

    u_int16_t maxLen = _pk.Param.maxMsgLen; //uint8_t ntru_max_msg_len(const NtruEncParams *params) {
//    if (_l>maxLen||maxLen>255);//error
    Polynomial::clsPoly Mtrin = Converse::MbinToMtrin(_m,_l,_pk.Param,maxLen);
    chie = Mtrin;
    std::cout << "\t Mtrin" << std::endl;
//    Mtrin.refine();
    Polynomial::print_poly(Mtrin);
    //random polynomial generation constant c
//    Polynomial::clsPoly r(_pk.Param.N-1);
//    MISC::RND::instance().fillPoly(&r,_pk.Param.dr,_pk.Param.c);
//    Polynomial::clsPoly R = Polynomial::mulPoly_mod(r,_pk.h,_pk.Param.q,_pk.Param.N-1);
    Polynomial::clsPoly e = Polynomial::addPoly_mod(Mtrin,/*R*/_pk.h,_pk.Param.q);
    return e;
}

std::string decrypt(Polynomial::clsPoly _e, key_pair_t _k) {

    Polynomial::clsPoly f,a,b,c;
    f=_k.Sk;
    Polynomial::mulPoly(3,&f);
    f.Coef[0]++;

    a = Polynomial::mulPoly_mod(_e,f,_k.Pk.Param.q,_k.Pk.Param.N-1);
    a.applyMod(3);
//    c = a;
    //    b = Polynomial::mulPoly_mod(1,a,3);
    c = Polynomial::mulPoly_mod(a,_k.Sk,3,_k.Pk.Param.N-1);
//    for (u_int16_t i = 0; i <= c.Degree(); i++)
//        if (c.Coef[i]==-1)
//            c.Coef[i]=2;

    return Converse::MtrinToMbin(&a);
}

poly_F_t generateF(const Config::params_t _param)
{
    poly_F_t f_t;
    Polynomial::clsPoly g,tmp;
    while (true){ //when shall we termiante?!
        Polynomial::clsPoly a(_param.N-1);
        //generating random polynomial f_p
        MISC::RND::instance().fillPoly(&a,_param.df,1);
        MISC::RND::instance().fillPoly(&a,_param.df,-1);
        f_t.f_q = inv(a,_param);
        if (!f_t.f_q.isZero()){
            f_t.F = a;
            break;
        }
    }
    return f_t;
}

Polynomial::clsPoly inv(const Polynomial::clsPoly _a, const Config::params_t _param)
{
    Polynomial::clsPoly b,c,f,f_2,f_q,g(_param.N),tmp,x(1);
    x.Coef[1]=b.Coef[0]=1;
    f=_a;
    f.Coef[0]= (_a.Coef[0]+1)%2;
    g.Coef[0]=1;
    g.Coef[_param.N] =1;
    u_int16_t k = 0;
    for (;;) {
        u_int16_t z = 0;
        while(f.Coef[0]==0 &&!f.isZero()) {
            k++;
            if (++z>=_param.N) {
                std::cout << "AMAD be SARAM" << std::endl;
                exit (-1);
            }
            f.Coef.erase(f.Coef.begin());
            c = Polynomial::mulPoly(&c,&x);
        }
        if(f.Degree()==0) {
            if(f.isZero()) {
                break;
            } else {
                while (k>_param.N) k-=_param.N;
                Polynomial::clsPoly x(_param.N-k);
                x.Coef[_param.N-k] = 1;
                f_2 = Polynomial::mulPoly_mod(x,b,2,_param.N-1);
                u_int32_t i = 2;
                while (i < _param.q)
                {
                    i*=i;
                    f = Polynomial::mulPoly_mod(_a,f_2,_param.q,_param.N-1);
                    for (u_int16_t j =0; j <= f.Degree(); j++) {
                        f.Coef[j]*=3;
                        f.Coef[j]+=f_2.Coef[j];
                        f.Coef[j]=_param.q-f.Coef[j];
                    }
                    f.Coef[0]+=2;
                    f_2=Polynomial::mulPoly_mod(f,f_2,_param.q,_param.N-1);
                }
                f_q = f_2;
                break;
            }
        }
        if (g.Degree() > f.Degree()) {
            tmp = g;
            g = f;
            f = tmp;
            tmp = c;
            c = b;
            b = tmp;
        }
        f = Polynomial::addPoly_mod(f,g,2);
        b = Polynomial::addPoly_mod(b,c,2);
        f.refine();
        b.refine();
    }

    return f_q;
}

Polynomial::clsPoly generateG(const Config::params_t _param)
{
    Polynomial::clsPoly g,tmp;
    while (true){ //when shall we termiante?!
        Polynomial::clsPoly a(_param.N-1);
        //generating random polynomial f_p
        MISC::RND::instance().fillPoly(&a,_param.dg,1);
        MISC::RND::instance().fillPoly(&a,_param.dg,-1);
        tmp = inv(a,_param);
        if (!tmp.isZero()){
            //or a+1?
            g = a;
            g.Coef[0]++;
            break;
        }
    }
    return g;
}

key_pair_t generateKeyPair2(const Config::params_t _param)
{
    key_pair_t kp;
    kp.Pk.Param = _param;
    poly_F_t fz = generateF(_param);
    Polynomial::clsPoly g = generateG(_param);
    kp.Pk.h = Polynomial::mulPoly_mod(g,fz.f_q,_param.q,_param.N-1);
    Polynomial::mulPoly(3,&kp.Pk.h);//or mod?
    kp.Sk = fz.F;
    Polynomial::mulPoly(3,&kp.Sk);//or mod?
    kp.Sk.Coef[0]++;
    return kp;

}



} // namespace NTRU
