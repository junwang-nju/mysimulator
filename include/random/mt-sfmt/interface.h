
#ifndef _Random_MT_SFMT_Interface_H_
#define _Random_MT_SFMT_Interface_H_

#include "random/base/interface.h"
#include "unique-parameter/128bit/interface.h"

namespace mysimulator {

  template <unsigned int LFac=19937>
  struct MT_SFMT : public RandomBase {

    typedef MT_SFMT   Type;
    typedef RandomBase  ParentType;

    static const unsigned int N=LFac/128+1;
    static const unsigned int NStatus=N;
    static const unsigned int NStatusByte=N*16;
    static const unsigned int N32=N*4;
    static const unsigned int N64=N*2;
    static const unsigned int Lag=(N32>=623?11:(N32>=68?7:(N32>=39?5:3)));
    static const unsigned int Mid=(N-Lag)/2;
    static const unsigned int LagMid=Lag+Mid;
    static const unsigned int Pos1;
    static const unsigned int SL1;
    static const unsigned int SL2;
    static const unsigned int SR1;
    static const unsigned int SR2;
    static const UniqueParameter128Bit Msk;
    static const UniqueParameter128Bit Parity;

    Vector<UniqueParameter128Bit> s;
    unsigned int idx;
    UniqueParameter128Bit u;

    MT_SFMT() : s(), idx(0), u() {}
    MT_SFMT(const Type&) { Error("Copier of MT_SFMT Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for MT_SFMT Disabled!");
      return *this;
    }
    ~MT_SFMT() {} { clearData(); }

    void clearData() { release(s); idx=0; }
    void _PeriodCertification() {
      unsigned int inner=0;
      unsigned int *p=s[0].u;
      for(unsigned int i=0;i<4;++i) inner^=p[i]&Parity.u[i];
      for(unsigned int i=16;i>0;i>>=1)  inner^=inner>>i;
      inner&=1;
      if(inner==1)  return;
      for(unsigned int i=0,work=1;i<4;++i)
      for(unsigned int j=0;j<32;++j) {
        if((work&Parity.u[i])!=0) { p[i]^=work; return; }
        work<<=1;
      }
    }
    unsigned int _Op1(const unsigned int x) { return (x^(x>>27))*1664525UL; }
    unsigned int _Op2(const unsigned int x) { return (x^(x>>27))*1566083941UL; }
    void _rshift128(UniqueParameter128Bit& out,const UniqueParameter128Bit& in,
                    const int shift) {
      out.ull[1]=(in.ull[1])>>(shift*8);
      out.ull[0]=(in.ull[0])>>(shift*8);
      out.ull[0]|=(in.ull[1])<<(64-shift*8);
    }
    void _lshift128(UniqueParameter128Bit& out,const UniqueParameter128Bit& in,
                    const int shift) {
      out.ull[1]=(in.ull[1])<<(shift*8);
      out.ull[0]=(in.ull[0])<<(shift*8);
      out.ull[1]|=(in.ull[0])>>(64-shift*8);
    }

    const UniqueParameter128Bit&
    _Recursion(const UniqueParameter128Bit& a, const UniqueParameter128Bit& b,
               const UniqueParameter128Bit& c, const UniqueParameter128Bit& d) {
      UniqueParameter128Bit x,y;
#ifdef _Have_SSE2
      UniqueParameter128Bit v;
      y.si=_mm_srli_epi32(b.si,SR1);
      u.si=_mm_srli_si128(c.si,SR2);
      v.si=_mm_slli_epi32(d.si,SL1);
      x.si=_mm_slli_si128(a.si,SL2);
      u.si=_mm_xor_si128(u.si,a.si);
      u.si=_mm_xor_si128(u.si,v.si);
      y.si=_mm_and_si128(y.si,Msk.si);
      u.si=_mm_xor_si128(u.si,x.si);
      u.si=_mm_xor_si128(u.si,y.si);
#else
      _lshift128(x,a,SL2);
      _rshift128(y,c,SR2);
      u.u[0]=a.u[0]^x.u[0]^((b.u[0]>>SR1)&Msk.u[0])^y.u[0]^(d.u[0]<<SL1);
      u.u[1]=a.u[1]^x.u[1]^((b.u[1]>>SR1)&Msk.u[1])^y.u[1]^(d.u[1]<<SL1);
      u.u[2]=a.u[2]^x.u[2]^((b.u[2]>>SR1)&Msk.u[2])^y.u[2]^(d.u[2]<<SL1);
      u.u[3]=a.u[3]^x.u[3]^((b.u[3]>>SR1)&Msk.u[3])^y.u[3]^(d.u[3]<<SL1);
#endif
      return u;
    }

  };

  template <unsigned int LFac>
  const unsigned int MT_SFMT<LFac>::N;
  template <unsigned int LFac>
  const unsigned int MT_SFMT<LFac>::NStatus;
  template <unsigned int LFac>
  const unsigned int MT_SFMT<LFac>::NStatusByte;
  template <unsigned int LFac>
  const unsigned int MT_SFMT<LFac>::N32;
  template <unsigned int LFac>
  const unsigned int MT_SFMT<LFac>::N64;
  template <unsigned int LFac>
  const unsigned int MT_SFMT<LFac>::Lag;
  template <unsigned int LFac>
  const unsigned int MT_SFMT<LFac>::Mid;
  template <unsigned int LFac>
  const unsigned int MT_SFMT<LFac>::LagMid;

  template <> const unsigned int MT_SFMT<607>::Pos1=2;
  template <> const unsigned int MT_SFMT<607>::SL1=15;
  template <> const unsigned int MT_SFMT<607>::SL2=3;
  template <> const unsigned int MT_SFMT<607>::SR1=13;
  template <> const unsigned int MT_SFMT<607>::SR2=3;
  template <>
  const UniqueParameter128Bit MT_SFMT<607>::Msk(0xFDFF37FFEF7F3F7DULL,
                                                0xFF777B7D7FF7FB2FULL);
  template <>
  const UniqueParameter128Bit MT_SFMT<607>::Parity(0x0000000100000000ULL,
                                                   0x000000005986F054ULL);

  template <> const unsigned int MT_SFMT<1279>::Pos1=7;
  template <> const unsigned int MT_SFMT<1279>::SL1=14;
  template <> const unsigned int MT_SFMT<1279>::SL2=3;
  template <> const unsigned int MT_SFMT<1279>::SR1=5;
  template <> const unsigned int MT_SFMT<1279>::SR2=1;
  template <>
  const UniqueParameter128Bit MT_SFMT<1279>::Msk(0xF7FFEF7F7FEFCFFFULL,
                                                 0xAFF3EF3FB5FFFF7FULL);
  template <>
  const UniqueParameter128Bit MT_SFMT<1279>::Parity(0x0000000100000000ULL,
                                                    0x0000000020000000ULL);

  template <> const unsigned int MT_SFMT<11213>::Pos1=68;
  template <> const unsigned int MT_SFMT<11213>::SL1=14;
  template <> const unsigned int MT_SFMT<11213>::SL2=3;
  template <> const unsigned int MT_SFMT<11213>::SR1=7;
  template <> const unsigned int MT_SFMT<11213>::SR2=3;
  template <>
  const UniqueParameter128Bit MT_SFMT<11213>::Msk(0xEFFFF7F8FFFFFFEFULL,
                                                  0xDFDFBFFF7FFFDBFDULL);
  template <>
  const UniqueParameter128Bit MT_SFMT<11213>::Parity(0x0000000100000000ULL,
                                                     0xE8148000D0C7AFA3ULL);

  template <> const unsigned int MT_SFMT<19937>::Pos1=122;
  template <> const unsigned int MT_SFMT<19937>::SL1=18;
  template <> const unsigned int MT_SFMT<19937>::SL2=1;
  template <> const unsigned int MT_SFMT<19937>::SR1=11;
  template <> const unsigned int MT_SFMT<19937>::SR2=1;
  template <>
  const UniqueParameter128Bit MT_SFMT<19937>::Msk(0xDFFFFFEFDDFECB7FULL,
                                                  0xBFFAFFFFBFFFFFF6ULL);
  template <>
  const UniqueParameter128Bit MT_SFMT<19937>::Parity(0x0000000100000000ULL,
                                                     0x0000000013C9E684ULL);

  template <> const unsigned int MT_SFMT<132049>::Pos1=110;
  template <> const unsigned int MT_SFMT<132049>::SL1=19;
  template <> const unsigned int MT_SFMT<132049>::SL2=1;
  template <> const unsigned int MT_SFMT<132049>::SR1=21;
  template <> const unsigned int MT_SFMT<132049>::SR2=1;
  template <>
  const UniqueParameter128Bit MT_SFMT<132049>::Msk(0xFFFFBB5FFB6EBF95ULL,
                                                   0xFFFEFFFACFF77FFFULL);
  template <>
  const UniqueParameter128Bit MT_SFMT<132049>::Parity(0x0000000100000000ULL,
                                                      0xCB520000C7E91C7DULL);

  template <> const unsigned int MT_SFMT<216091>::Pos1=627;
  template <> const unsigned int MT_SFMT<216091>::SL1=11;
  template <> const unsigned int MT_SFMT<216091>::SL2=3;
  template <> const unsigned int MT_SFMT<216091>::SR1=10;
  template <> const unsigned int MT_SFMT<216091>::SR2=1;
  template <>
  const UniqueParameter128Bit MT_SFMT<216091>::Msk(0xBFF7BFF7BFFFFFFFULL,
                                                   0xBFFFFA7FFFDDFBFBULL);
  template <>
  const UniqueParameter128Bit MT_SFMT<216091>::Parity(0xF800000189E80709ULL,
                                                      0x3BD2B64B0C64B1E4ULL);

  template <> const unsigned int MT_SFMT<2281>::Pos1=12;
  template <> const unsigned int MT_SFMT<2281>::SL1=19;
  template <> const unsigned int MT_SFMT<2281>::SL2=1;
  template <> const unsigned int MT_SFMT<2281>::SR1=5;
  template <> const unsigned int MT_SFMT<2281>::SR2=1;
  template <>
  const UniqueParameter128Bit MT_SFMT<2281>::Msk(0xBFF7FFBFFDFFFFFEULL,
                                                 0xF7FFEF7FF2F7CBBFULL);
  template <>
  const UniqueParameter128Bit MT_SFMT<2281>::Parity(0x0000000100000000ULL,
                                                    0x0000000041DFA600ULL);

  template <> const unsigned int MT_SFMT<4253>::Pos1=17;
  template <> const unsigned int MT_SFMT<4253>::SL1=20;
  template <> const unsigned int MT_SFMT<4253>::SL2=1;
  template <> const unsigned int MT_SFMT<4253>::SR1=7;
  template <> const unsigned int MT_SFMT<4253>::SR2=1;
  template <>
  const UniqueParameter128Bit MT_SFMT<4253>::Msk(0x9F7BFFFF9FFFFF5FULL,
                                                 0x3EFFFFFBFFFFF7BBULL);
  template <>
  const UniqueParameter128Bit MT_SFMT<4253>::Parity(0x00000001AF5390A3ULL,
                                                    0xB740B3F86C11486DULL);

  template <> const unsigned int MT_SFMT<44497>::Pos1=330;
  template <> const unsigned int MT_SFMT<44497>::SL1=5;
  template <> const unsigned int MT_SFMT<44497>::SL2=3;
  template <> const unsigned int MT_SFMT<44497>::SR1=9;
  template <> const unsigned int MT_SFMT<44497>::SR2=3;
  template <>
  const UniqueParameter128Bit MT_SFMT<44497>::Msk(0xEFFFFFFBDFBEBFFFULL,
                                                  0xBFBF7BEF9FFD7BFFULL);
  template <>
  const UniqueParameter128Bit MT_SFMT<44497>::Parity(0x0000000100000000ULL,
                                                     0xA3AC4000ECC1327AULL);

  template <> const unsigned int MT_SFMT<86243>::Pos1=366;
  template <> const unsigned int MT_SFMT<86243>::SL1=6;
  template <> const unsigned int MT_SFMT<86243>::SL2=7;
  template <> const unsigned int MT_SFMT<86243>::SR1=19;
  template <> const unsigned int MT_SFMT<86243>::SR2=1;
  template <>
  const UniqueParameter128Bit MT_SFMT<86243>::Msk(0xFDBFFBFFBFF7FF3FULL,
                                                  0xFD77EFFFBF9FF3FFULL);
  template <>
  const UniqueParameter128Bit MT_SFMT<86243>::Parity(0x0000000100000000ULL,
                                                     0x00000000E9528D85ULL);

  template <unsigned int LFac>
  bool IsValid(const MT_SFMT& G) { return IsValid(G.s)&&(G.idx!=0); }

  template <unsigned int LFac>
  void release(MT_SFMT& G) { G.clearData(); }

}

#endif

