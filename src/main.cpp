#include <iostream>
#include "lib/NTRU.h"
#include <bitset>
using namespace std;

bool check_wikiExample() {
    Polynomial::clsPoly f(10),g(10),f_p(10),f_q(10),h,e,r(7),m(10),a,b,c;
    u_int16_t p=3,q=32,N=11;
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

    f_p.Coef[0]=1;
    f_p.Coef[1]=2;
    f_p.Coef[2]=0;
    f_p.Coef[3]=2;
    f_p.Coef[4]=2;
    f_p.Coef[5]=1;
    f_p.Coef[6]=0;
    f_p.Coef[7]=2;
    f_p.Coef[8]=1;
    f_p.Coef[9]=2;
    f_p.Coef[10]=0;
    f_p.refine();//removing the last zero

    f_q.Coef[0]=5;
    f_q.Coef[1]=9;
    f_q.Coef[2]=6;
    f_q.Coef[3]=16;
    f_q.Coef[4]=4;
    f_q.Coef[5]=15;
    f_q.Coef[6]=16;
    f_q.Coef[7]=22;
    f_q.Coef[8]=20;
    f_q.Coef[9]=18;
    f_q.Coef[10]=30;
    Polynomial::clsPoly f_q2=Inverese::forQ(f,N,q);
//    f_q.applyMod(q);
    cout << "f_q:" << endl;
    Polynomial::print_poly(f_q2);
    Polynomial::clsPoly f_3;
    f_3 = Inverese::AI_for3(f,N);
    cout << "f_3:" << endl;
    Polynomial::print_poly(f_3);
//    if (f_q.Coef != f_q2.Coef || f_3.Coef != f_p.Coef)
//        exit (-1);

    h = Polynomial::mulPoly_mod(3,f_q,q);
    h = Polynomial::mulPoly_mod(h,g,q,N-1);
    cout << "PUBLIC KEY:" << endl;
    Polynomial::print_poly(h);

    m.Coef[0]=-1;
    m.Coef[1]=0;
    m.Coef[2]=0;
    m.Coef[3]=1;
    m.Coef[4]=-1;
    m.Coef[5]=0;
    m.Coef[6]=0;
    m.Coef[7]=0;
    m.Coef[8]=-1;
    m.Coef[9]=1;
    m.Coef[10]=1;

    r.Coef[0]=-1;
    r.Coef[1]=0;
    r.Coef[2]=1;
    r.Coef[3]=1;
    r.Coef[4]=1;
    r.Coef[5]=-1;
    r.Coef[6]=0;
    r.Coef[7]=-1;

    e = Polynomial::mulPoly_mod(r,h,q,N-1);
    e = Polynomial::addPoly_mod(e,m,q);
    cout << "ENCRYPTED:" << endl;
    Polynomial::print_poly(e);
    a = Polynomial::mulPoly_mod(f,e,q,N-1);
    cout << "a:" << endl;
    Polynomial::print_poly(a);
    a.applyMod_pos(q);
    b = a;
    b.applyMod(p);
    cout << "b:" << endl;
    Polynomial::print_poly(a);
    Polynomial::print_poly(b);
    c = Polynomial::mulPoly_mod(b,f_3,3,N-1);
//    c.refine();
    cout << "DECRYPTED:" << endl;
    Polynomial::print_poly(c);
    return c.Coef == m.Coef;
//    Polynomial::print_poly(Polynomial::subPoly_mod(b,a,3));
////    return 0;
//    int wa=-1,wb=0;

//    cout << "inv: "<<(wa+wb)%3<< endl;
////    return 0;
}

int main()
{
    if (check_wikiExample())
    cout << "result: " << check_wikiExample()<< endl;
    return 0;



















//    int afv = Inverese::ExtendedEuclidian(7,26);
//    cout << "inv Euclidian: "<<afv << endl;
//    Polynomial::print_poly(f);
//    cout << "inv for 3: "<< endl;
//    Polynomial::print_poly(Inverese::AI_for3(f,11));
////    return 0;
//////    Polynomial::print_poly(MISC::MISC::instance().inverse_AlmostInverseAlg_forP(f,11,3));
//    Polynomial::clsPoly asasaaa, inv2 = Inverese::AI_for2(f,11);
//    asasaaa = Inverese::AI_for3(f,11);
//    cout << "f and f_3 "<< endl;
//    Polynomial::print_poly(Polynomial::mulPoly_mod(f,asasaaa,3,10));
//    cout << "f and f_2: "<< endl;
//    Polynomial::print_poly(Polynomial::mulPoly_mod(f,inv2,2,10));

//    asasaaa = Polynomial::mulPoly_mod(f,inv2,2,10);
//    Polynomial::print_poly(asasaaa);
//    cout << "iter32: "<< endl;
//    asasaaa = Inverese::NewtonIteration_for2(f,inv2,32,11);
//    Polynomial::print_poly(Polynomial::mulPoly_mod(f,asasaaa,32,10));
//    return 0;

    Config::params_t p = Config::__TEST__();
    NTRU::key_pair_t pair = NTRU::generateKeyPair(p);
    NTRU::key_pair_t pair2 = NTRU::generateKeyPair2(p);

//    Polynomial::clsPoly s = Polynomial::mulPoly_mod(pair.Sk,pair.Sk.f,3,p.N-1);
//    Polynomial::print_poly(s);

//    return 0;


    std::string plain = "ra";
//    std::bitset<8> h1 = bitset<8>(plain.c_str()[0]);
//    std::bitset<8> h2 = bitset<8>(plain.c_str()[1]);
//    std::bitset<8> h3 = bitset<8>(plain.c_str()[2]);
//    std::bitset<3> yek;
////    cout << h1<<h2<<h3<< endl;
//    std::bitset<24> llls(h1.to_string()+h2.to_string()+h3.to_string());
////    cout << llls << endl;
//    for (int i =0; i < llls.size(); ) {
//        yek[0]=llls[i];
//        yek[1]=llls[i+1];
//        yek[2]=llls[i+2];
////        cout << yek << endl;
//        i+=3;
//    }
//    return 0;

    //    u_int8_t *M_head = (u_int8_t*)&Mbin + db_byte;
//    Polynomial::clsPoly ac = Converse::MbinToMtrin((const unsigned char*)plain.c_str(),plain.size(),p,100);
//    Polynomial::print_poly(ac);

//    Polynomial::print_poly(ac);
//    for (u_int16_t i = 0; i <= ac.Degree(); i++)
//        if (ac.Coef[i]==-1)
//            ac.Coef[i]=2;
//    std::string aasd = Converse::MtrinToMbin(&ac);
//    std::cout << aasd << "\t" << plain << std::endl;
//    return 0;
//    Config::params_t p = Config::__TEST__();
    std::cout << "Config loaded! generating key pair..." << std::endl;
    std::cout << "Key pair generated! encrypting..." << std::endl;

    Polynomial::clsPoly cipher = NTRU::encrypt((const unsigned char *)plain.c_str(),plain.size(),pair.Pk);
    std::cout << "Encrypted! Decrypting..." << std::endl;
    std::string decipher = NTRU::decrypt(cipher,pair);
    std::cout << decipher << " --- " << plain << std::endl;








    Polynomial::clsPoly cipher2 = NTRU::encrypt((const unsigned char *)plain.c_str(),plain.size(),pair2.Pk);
    std::cout << "Encrypted! Decrypting..." << std::endl;
    std::string decipher2 = NTRU::decrypt(cipher2,pair2);
    std::cout << decipher2 << " -2-2- " << plain << std::endl;



    return 0;
}
