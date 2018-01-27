#include "NTRU.h"


namespace NTRU {

key_pair_t generateKeyPair(const Config::params_t _param) {
    key_pair_t keyPair;
    keyPair.Pk.Param = _param;
    u_int16_t p = 3;
    Polynomial::clsPoly f_p(_param.N-1),f_q(_param.N-1),
            f(_param.N-1),g(_param.N-1),h(_param.N-1),g_q(_param.N-1);
    while (true){ //when shall we termiante?!
        f_p.zero();
        //generating random polynomial f_p
        MISC::RND::instance().fillPoly(&f_p,_param.df,1);
        MISC::RND::instance().fillPoly(&f_p,_param.df,-1);
        //calculating polynomial f, multiplicative invers of f_p in mod p
        f = Polynomial::mulPoly_mod(p,f_p,_param.q);
        f.Coef[0]=(f.Coef[0]+1)%_param.q;
        //calculating polynomial f_q, multiplicative invers of f in mod q
        f_q = Inverese::forQ(f,_param.N,_param.q);
        if (!f_q.isZero())
            break;
    }
    while (true) { //when shall we termiante?!
        g.zero();
        MISC::RND::instance().fillPoly(&g,_param.dg,1);
        MISC::RND::instance().fillPoly(&g,_param.dg,-1);
        //calculating polynomial f_q, multiplicative invers of f in mod q
        g_q = Inverese::forQ(g,_param.N,_param.q);
        if (!g_q.isZero())
            break;
    }
    h = Polynomial::mulPoly_mod(f_q,g,_param.q,_param.N-1);
    keyPair.Pk.h = h;
    keyPair.Sk.f = f;
    keyPair.Sk.f_p = f_p;
    return keyPair;
}


Polynomial::clsPoly MbinToMtrin(unsigned char *_m,  size_t _l, const Config::params_t *_param, const u_int16_t _max_len) {

    Polynomial::clsPoly Mtrin(_param->N-1);
    u_int16_t db_byte = _param->db/8;
    u_int16_t Mbin_len = db_byte + 1 + _max_len + 1;
    // creat M and b
    u_int8_t b[db_byte],Mbin[Mbin_len];
    MISC::RND::instance().fillByte(b,db_byte);
    memcpy(&Mbin,&b,db_byte);
    u_int8_t *M_head = (u_int8_t*)&Mbin + db_byte;
    *M_head = _l;
    M_head++;
    memcpy(M_head, _m, _l);
    M_head += _l;
    memset(M_head, 0, _max_len+1-_l);
    //convert Mbin to Mtrin
    u_int16_t Mtrin_idx = 0;
    //32 > 3*8=24
    int32_t tmp;
    uint16_t i = 0;
    while (i<(Mbin_len+2)/3*3 && Mtrin_idx<_param->N-1) { //wtf
        tmp = (unsigned char)Mbin[i+2];
        tmp <<= 8;
        tmp += (unsigned char)Mbin[i+1];
        tmp <<= 8;
        tmp += (unsigned char)Mbin[i];
        i += 3;
        uint8_t j;
        for (j=0; j<8 && Mtrin_idx<_param->N-1; j++) {
            unsigned char k = tmp & 7;
            Mtrin.Coef[Mtrin_idx++] = BIN_TO_TRIN_POLY_1[k];
            Mtrin.Coef[Mtrin_idx++] = BIN_TO_TRIN_POLY_2[k];
            tmp >>= 3;
        }
    }
    return Mtrin;
}

std::string MtrinToMbin(const Polynomial::clsPoly *_mtrin) {
    std::string res;
    u_int16_t c1, c2, c3, i = 0;
    int coef1,coef2,coef3,coef4,coef5,coef6;
    char data[3] = {0,0,0};
    while (i < _mtrin->Degree) {
        coef1 = _mtrin->Coef[i++];
        coef2 = _mtrin->Coef[i++];
        coef3 = _mtrin->Coef[i++];
        coef4 = _mtrin->Coef[i++];
        coef5 = _mtrin->Coef[i++];
        coef6 = _mtrin->Coef[i++];
//        if (coeff1==2 && coeff2==2)
//            valid = 0;
        c1 = 3*coef1 + coef2;
        c2 = 3*coef3 + coef4;
        c3 = 3*coef5 + coef6;
        data[0] = (c1<<5) | (c2<<2) | (c3>>1);
        data[1] = (c3<<7);

        coef1 = _mtrin->Coef[i++];
        coef2 = _mtrin->Coef[i++];
        coef3 = _mtrin->Coef[i++];
        coef4 = _mtrin->Coef[i++];
        coef5 = _mtrin->Coef[i++];
        coef6 = _mtrin->Coef[i++];
//        if (coeff1==2 && coeff2==2)
//            valid = 0;
        c1 = 3*coef1 + coef2;
        c2 = 3*coef3 + coef4;
        c3 = 3*coef5 + coef6;
        data[1] |= (c1<<4) | (c2<<1) | (c3>>2);
        data[2] = (c3 << 6);
        coef1 = _mtrin->Coef[i++];
        coef2 = _mtrin->Coef[i++];
        coef3 = _mtrin->Coef[i++];
        coef4 = _mtrin->Coef[i++];
//        if (coeff1==2 && coeff2==2)
//            valid = 0;
        c1 = 3*coef1 + coef2;
        c2 = 3*coef3 + coef4;
        data[2] |=  (c1<<3) | c2;
        res.append(data);
    }
    return res;
}

//uint8_t ntru_max_msg_len(const NtruEncParams *params) {
//    uint16_t N = params->N;
//    uint8_t llen = 1;   /* ceil(log2(max_len)) */
//    uint16_t db = params->db;
//    uint16_t max_msg_len;
//    max_msg_len = N/2*3/8 - llen - db/8;
//    return max_msg_len;
//}
Polynomial::clsPoly encrypt(const unsigned char *_m, const size_t _l, const pub_key_t _pk) {

    u_int16_t maxLen = _pk.Param.maxMsgLen; //uint8_t ntru_max_msg_len(const NtruEncParams *params) {
    if (_l>maxLen||maxLen>255);//error
    Polynomial::clsPoly Mtrin = Converse::MbinToMtrin(_m,_l,_pk.Param,maxLen);
    //random polynomial generation constant c
    Polynomial::clsPoly r(_pk.Param.N-1);
    MISC::RND::instance().fillPoly(&r,_pk.Param.dr,_pk.Param.c);
    Polynomial::clsPoly R = Polynomial::mulPoly_mod(r,_pk.h,_pk.Param.q,_pk.Param.N-1);
    Polynomial::clsPoly e = Polynomial::addPoly_mod(Mtrin,R,_pk.Param.q);
    return e;
}

std::string decrypt(Polynomial::clsPoly _e, key_pair_t _k) {

    Polynomial::clsPoly res,a,b,c;
    a = Polynomial::mulPoly_mod(_e,_k.Sk.f,_k.Pk.Param.q,_k.Pk.Param.N-1);
    b = Polynomial::mulPoly_mod(1,a,3);
    c = Polynomial::mulPoly_mod(a,_k.Sk.f_p,_k.Pk.Param.q,_k.Pk.Param.N-1);

    return Converse::MtrinToMbin(&c);
}



} // namespace NTRU
