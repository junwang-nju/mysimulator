
#ifndef _Random_Generator_MT_SFMT_H_
#define _Random_Generator_MT_SFMT_H_

#include "data/basic/vector.h"
#include "data/basic/unique-parameter-128bit.h"

namespace std {

#ifdef HAVE_SSE2
  __m128i SFMT_SSE2_ParamMask;
#endif

  template <unsigned int LoopFac=19937>
  struct SFMT : public Vector<UniqueParameter128b> {
    static const unsigned int MExp;
    static const unsigned int N;
    static const unsigned int NStatus;
    static const unsigned int NStatusByte;
    static const unsigned int N32;
    static const unsigned int N64;
    static const unsigned int Lag;
    static const unsigned int Mid;
    static const unsigned int LagMid;
    static const unsigned int Pos1;
    static const unsigned int SL1;
    static const unsigned int SL2;
    static const unsigned int SR1;
    static const unsigned int SR2;
    static const unsigned int Msk1;
    static const unsigned int Msk2;
    static const unsigned int Msk3;
    static const unsigned int Msk4;
    static const unsigned int Parity1;
    static const unsigned int Parity2;
    static const unsigned int Parity3;
    static const unsigned int Parity4;
    static const unsigned int Parity[4];

    typedef SFMT<LoopFac>   Type;
    typedef Vector<UniqueParameter128b> ParentType;

    unsigned int *idx;
    UniqueParameter128b output;
    
    SFMT() : ParentType(), idx(NULL), output() {}
    SFMT(const Type& G) { Error("Cannot create SFMT Generator"); }
    Type& operator=(const Type& G) {
      Error("Cannot copy SFMT Generator");
      return *this;
    }
    ~SFMT() { release(*this); }

    void PeriodCertification() {
      unsigned int inner=0,i,j,work,*pSFMT32=&(this->operator[](0).u[0]);
      for(i=0;i<4;++i)  inner^=pSFMT32[i]&Parity[i];
      for(i=16;i>0;i>>=1)  inner^=inner>>i;
      inner&=1;
      if(inner==1)  return;
      for(i=0;i<4;++i) {
        work=1;
        for(j=0;j<32;++j) {
          if((work&Parity[i])!=0) {
            pSFMT32[i]^=work;
            return;
          }
          work=work<<1;
        }
      }
    }
    unsigned int func1(const unsigned int x){ return (x^(x>>27))*1664525UL; }
    unsigned int func2(const unsigned int x){ return (x^(x>>27))*1566083941UL; }

#ifdef HAVE_SSE2
    void InitConst() {
      static bool first=true;
      if(!first)  return;
      _mm_storeu_si128(&SFMT_SSE2_ParamMask,_mm_set_epi32(Msk4,Msk3,Msk2,Msk1));
      first=false;
    }
    __m128i DoRecursion(const __m128i& a, const __m128i& b, const __m128i& c,
                        const __m128i& d) {
      __m128i v,x,y,z;
      x=_mm_loadu_si128(&a);
      y=_mm_loadu_si128(&b);
      z=_mm_loadu_si128(&c);
      v=_mm_loadu_si128(&d);
      y=_mm_srli_epi32(y,SR1);
      z=_mm_srli_si128(z,SR2);
      v=_mm_slli_epi32(v,SL1);
      z=_mm_xor_si128(z,x);
      z=_mm_xor_si128(z,v);
      x=_mm_slli_si128(x,SL2);
      y=_mm_and_si128(y,SFMT_SSE2_ParamMask);
      z=_mm_xor_si128(z,x);
      z=_mm_xor_si128(z,y);
      return z;
    }
#else
    const UniqueParameter128b& DoRecursion(const UniqueParameter128b& a,
                                           const UniqueParameter128b& b,
                                           const UniqueParameter128b& c,
                                           const UniqueParameter128b& d) {
      static UniqueParameter128b r,x,y;
      lshift128(x,a,SL2);
      rshift128(y,c,SR2);
      r.u[0]=a.u[0]^x.u[0]^((b.u[0]>>SR1)&Msk1)^y.u[0]^(d.u[0]<<SL1);
      r.u[1]=a.u[1]^x.u[1]^((b.u[1]>>SR1)&Msk2)^y.u[1]^(d.u[1]<<SL1);
      r.u[2]=a.u[2]^x.u[2]^((b.u[2]>>SR1)&Msk3)^y.u[2]^(d.u[2]<<SL1);
      r.u[3]=a.u[3]^x.u[3]^((b.u[3]>>SR1)&Msk4)^y.u[3]^(d.u[3]<<SL1);
      return r;
    }
#endif

    private:
    
    void rshift128(UniqueParameter128b& out, const UniqueParameter128b& in,
                   const int shift) {
      unsigned long long int th,tl,oh,ol;
      th=(static_cast<unsigned long long int>(in.u[3])<<32)|
         (static_cast<unsigned long long int>(in.u[2]));
      tl=(static_cast<unsigned long long int>(in.u[1])<<32)|
         (static_cast<unsigned long long int>(in.u[0]));
      oh=th>>(shift*8);
      ol=tl>>(shift*8);
      ol|=th<<(64-shift*8);
      out.u[1]=static_cast<unsigned int>(ol>>32);
      out.u[0]=static_cast<unsigned int>(ol);
      out.u[3]=static_cast<unsigned int>(oh>>32);
      out.u[2]=static_cast<unsigned int>(oh);
    }
    
    void lshift128(UniqueParameter128b& out, const UniqueParameter128b& in,
                   const int shift) {
      unsigned long long int th,tl,oh,ol;
      th=(static_cast<unsigned long long int>(in.u[3])<<32)|
         (static_cast<unsigned long long int>(in.u[2]));
      tl=(static_cast<unsigned long long int>(in.u[1])<<32)|
         (static_cast<unsigned long long int>(in.u[0]));
      oh=th<<(shift*8);
      ol=tl<<(shift*8);
      oh|=tl>>(64-shift*8);
      out.u[1]=static_cast<unsigned int>(ol>>32);
      out.u[0]=static_cast<unsigned int>(ol);
      out.u[3]=static_cast<unsigned int>(oh>>32);
      out.u[2]=static_cast<unsigned int>(oh);
    }

  };

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::MExp=LoopFac;
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::N=SFMT<LoopFac>::MExp/128+1;
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::NStatus=SFMT<LoopFac>::N;
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::NStatusByte=SFMT<LoopFac>::N*16;
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::N32=SFMT<LoopFac>::N*4;
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::N64=SFMT<LoopFac>::N*2;
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Lag=(SFMT<LoopFac>::N32>=623?11:
                                        (SFMT<LoopFac>::N32>=68?7:
                                        (SFMT<LoopFac>::N32>=39?5:3)));
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Mid=(SFMT<LoopFac>::N-SFMT<LoopFac>::Lag)/2;
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::LagMid=
      SFMT<LoopFac>::Lag+SFMT<LoopFac>::Mid;
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Parity[4]={
    SFMT<LoopFac>::Parity1, SFMT<LoopFac>::Parity2,
    SFMT<LoopFac>::Parity3, SFMT<LoopFac>::Parity4
  };
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Pos1=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::SL1=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::SL2=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::SR1=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::SR2=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Msk1=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Msk2=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Msk3=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Msk4=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Parity1=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Parity2=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Parity3=0;
  template <unsigned int LoopFac> const unsigned int SFMT<LoopFac>::Parity4=0;

  template <> const unsigned int SFMT<607>::Pos1=2;
  template <> const unsigned int SFMT<607>::SL1=15;
  template <> const unsigned int SFMT<607>::SL2=3;
  template <> const unsigned int SFMT<607>::SR1=13;
  template <> const unsigned int SFMT<607>::SR2=3;
  template <> const unsigned int SFMT<607>::Msk1=0xFDFF37FFU;
  template <> const unsigned int SFMT<607>::Msk2=0xEF7F3F7DU;
  template <> const unsigned int SFMT<607>::Msk3=0xFF777B7DU;
  template <> const unsigned int SFMT<607>::Msk4=0x7FF7FB2FU;
  template <> const unsigned int SFMT<607>::Parity1=0x00000001U;
  template <> const unsigned int SFMT<607>::Parity4=0x5986F054U;

  template <> const unsigned int SFMT<1279>::Pos1=7;
  template <> const unsigned int SFMT<1279>::SL1=14;
  template <> const unsigned int SFMT<1279>::SL2=3;
  template <> const unsigned int SFMT<1279>::SR1=5;
  template <> const unsigned int SFMT<1279>::SR2=1;
  template <> const unsigned int SFMT<1279>::Msk1=0xF7FFEF7FU;
  template <> const unsigned int SFMT<1279>::Msk2=0x7FEFCFFFU;
  template <> const unsigned int SFMT<1279>::Msk3=0xAFF3EF3FU;
  template <> const unsigned int SFMT<1279>::Msk4=0xB5FFFF7FU;
  template <> const unsigned int SFMT<1279>::Parity1=0x00000001U;
  template <> const unsigned int SFMT<1279>::Parity4=0x20000000U;

  template <> const unsigned int SFMT<11213>::Pos1=68;
  template <> const unsigned int SFMT<11213>::SL1=14;
  template <> const unsigned int SFMT<11213>::SL2=3;
  template <> const unsigned int SFMT<11213>::SR1=7;
  template <> const unsigned int SFMT<11213>::SR2=3;
  template <> const unsigned int SFMT<11213>::Msk1=0xEFFFF7F8U;
  template <> const unsigned int SFMT<11213>::Msk2=0xFFFFFFEFU;
  template <> const unsigned int SFMT<11213>::Msk3=0xDFDFBFFFU;
  template <> const unsigned int SFMT<11213>::Msk4=0x7FFFDBFDU;
  template <> const unsigned int SFMT<11213>::Parity1=0x00000001U;
  template <> const unsigned int SFMT<11213>::Parity3=0xE8148000U;
  template <> const unsigned int SFMT<11213>::Parity4=0xD0C7AFA3U;

  template <> const unsigned int SFMT<19937>::Pos1=122;
  template <> const unsigned int SFMT<19937>::SL1=18;
  template <> const unsigned int SFMT<19937>::SL2=1;
  template <> const unsigned int SFMT<19937>::SR1=11;
  template <> const unsigned int SFMT<19937>::SR2=1;
  template <> const unsigned int SFMT<19937>::Msk1=0xDFFFFFEFU;
  template <> const unsigned int SFMT<19937>::Msk2=0xDDFECB7FU;
  template <> const unsigned int SFMT<19937>::Msk3=0xBFFAFFFFU;
  template <> const unsigned int SFMT<19937>::Msk4=0xBFFFFFF6U;
  template <> const unsigned int SFMT<19937>::Parity1=0x00000001U;
  template <> const unsigned int SFMT<19937>::Parity4=0x13C9E684U;

  template <> const unsigned int SFMT<132049>::Pos1=110;
  template <> const unsigned int SFMT<132049>::SL1=19;
  template <> const unsigned int SFMT<132049>::SL2=1;
  template <> const unsigned int SFMT<132049>::SR1=21;
  template <> const unsigned int SFMT<132049>::SR2=1;
  template <> const unsigned int SFMT<132049>::Msk1=0xFFFFBB5FU;
  template <> const unsigned int SFMT<132049>::Msk2=0xFB6EBF95U;
  template <> const unsigned int SFMT<132049>::Msk3=0xFFFEFFFAU;
  template <> const unsigned int SFMT<132049>::Msk4=0xCFF77FFFU;
  template <> const unsigned int SFMT<132049>::Parity1=0x00000001U;
  template <> const unsigned int SFMT<132049>::Parity3=0xCB520000U;
  template <> const unsigned int SFMT<132049>::Parity4=0xC7E91C7DU;

  template <> const unsigned int SFMT<216091>::Pos1=627;
  template <> const unsigned int SFMT<216091>::SL1=11;
  template <> const unsigned int SFMT<216091>::SL2=3;
  template <> const unsigned int SFMT<216091>::SR1=10;
  template <> const unsigned int SFMT<216091>::SR2=1;
  template <> const unsigned int SFMT<216091>::Msk1=0xBFF7BFF7U;
  template <> const unsigned int SFMT<216091>::Msk2=0xBFFFFFFFU;
  template <> const unsigned int SFMT<216091>::Msk3=0xBFFFFA7FU;
  template <> const unsigned int SFMT<216091>::Msk4=0xFFDDFBFBU;
  template <> const unsigned int SFMT<216091>::Parity1=0xF8000001U;
  template <> const unsigned int SFMT<216091>::Parity2=0x89E80709U;
  template <> const unsigned int SFMT<216091>::Parity3=0x3BD2B64BU;
  template <> const unsigned int SFMT<216091>::Parity4=0x0C64B1E4U;

  template <> const unsigned int SFMT<2281>::Pos1=12;
  template <> const unsigned int SFMT<2281>::SL1=19;
  template <> const unsigned int SFMT<2281>::SL2=1;
  template <> const unsigned int SFMT<2281>::SR1=5;
  template <> const unsigned int SFMT<2281>::SR2=1;
  template <> const unsigned int SFMT<2281>::Msk1=0xBFF7FFBFU;
  template <> const unsigned int SFMT<2281>::Msk2=0xFDFFFFFEU;
  template <> const unsigned int SFMT<2281>::Msk3=0xF7FFEF7FU;
  template <> const unsigned int SFMT<2281>::Msk4=0xF2F7CBBFU;
  template <> const unsigned int SFMT<2281>::Parity1=0x00000001U;
  template <> const unsigned int SFMT<2281>::Parity4=0x41DFA600U;

  template <> const unsigned int SFMT<4253>::Pos1=17;
  template <> const unsigned int SFMT<4253>::SL1=20;
  template <> const unsigned int SFMT<4253>::SL2=1;
  template <> const unsigned int SFMT<4253>::SR1=7;
  template <> const unsigned int SFMT<4253>::SR2=1;
  template <> const unsigned int SFMT<4253>::Msk1=0x9F7BFFFFU;
  template <> const unsigned int SFMT<4253>::Msk2=0x9FFFFF5FU;
  template <> const unsigned int SFMT<4253>::Msk3=0x3EFFFFFBU;
  template <> const unsigned int SFMT<4253>::Msk4=0xFFFFF7BBU;
  template <> const unsigned int SFMT<4253>::Parity1=0x00000001U;
  template <> const unsigned int SFMT<4253>::Parity2=0xAF5390A3U;
  template <> const unsigned int SFMT<4253>::Parity3=0xB740B3F8U;
  template <> const unsigned int SFMT<4253>::Parity4=0x6C11486DU;

  template <> const unsigned int SFMT<44497>::Pos1=330;
  template <> const unsigned int SFMT<44497>::SL1=5;
  template <> const unsigned int SFMT<44497>::SL2=3;
  template <> const unsigned int SFMT<44497>::SR1=9;
  template <> const unsigned int SFMT<44497>::SR2=3;
  template <> const unsigned int SFMT<44497>::Msk1=0xEFFFFFFBU;
  template <> const unsigned int SFMT<44497>::Msk2=0xDFBEBFFFU;
  template <> const unsigned int SFMT<44497>::Msk3=0xBFBF7BEFU;
  template <> const unsigned int SFMT<44497>::Msk4=0x9FFD7BFFU;
  template <> const unsigned int SFMT<44497>::Parity1=0x00000001U;
  template <> const unsigned int SFMT<44497>::Parity3=0xA3AC4000U;
  template <> const unsigned int SFMT<44497>::Parity4=0xECC1327AU;

  template <> const unsigned int SFMT<86243>::Pos1=366;
  template <> const unsigned int SFMT<86243>::SL1=6;
  template <> const unsigned int SFMT<86243>::SL2=7;
  template <> const unsigned int SFMT<86243>::SR1=19;
  template <> const unsigned int SFMT<86243>::SR2=1;
  template <> const unsigned int SFMT<86243>::Msk1=0xFDBFFBFFU;
  template <> const unsigned int SFMT<86243>::Msk2=0xBFF7FF3FU;
  template <> const unsigned int SFMT<86243>::Msk3=0xFD77EFFFU;
  template <> const unsigned int SFMT<86243>::Msk4=0xBF9FF3FFU;
  template <> const unsigned int SFMT<86243>::Parity1=0x00000001U;
  template <> const unsigned int SFMT<86243>::Parity4=0xE9528D85U;

  template <unsigned int LoopFac>
  bool IsAvailable(const SFMT<LoopFac>& G) {
    return IsAvailable(static_cast<const Vector<UniqueParameter128b>&>(G));
  }
  template <unsigned int LoopFac>
  bool IsRandomGenerator(const SFMT<LoopFac>& G) { return true; }

  template <unsigned int LoopFac>
  void init(SFMT<LoopFac>&, const unsigned int);

  template <unsigned int LoopFac>
  void release(SFMT<LoopFac>& G) {
    if(G.state==Allocated)  safe_delete(G.idx);
    else G.idx=NULL;
    release(static_cast<Vector<UniqueParameter128b>&>(G));
    copy(G.output,0);
  }
  template <unsigned int LoopFac>
  void copy(SFMT<LoopFac>& G, const SFMT<LoopFac>& cG) {
    assert(IsAvailable(G));
    assert(IsAvailable(cG));
    copy(static_cast<Vector<UniqueParameter128b>&>(G),
         static_cast<const Vector<UniqueParameter128b>&>(cG));
    copy(*(G.idx),*(cG.idx));
    copy(G.output,cG.output);
  }
  template <unsigned int LoopFac>
  void allocate(SFMT<LoopFac>& G) {
    release(G);
    allocate(static_cast<Vector<UniqueParameter128b>&>(G),
             SFMT<LoopFac>::NStatus);
    G.idx=new unsigned int;
    init(G,5489U);
  }
  template <unsigned int LoopFac>
  void refer(SFMT<LoopFac>& G, const SFMT<LoopFac>& rG) {
    assert(IsAvailable(rG));
    release(G);
    refer(static_cast<Vector<UniqueParameter128b>&>(G),
          static_cast<const Vector<UniqueParameter128b>&>(rG));
    G.idx=rG.idx;
  }

}

#endif
