
#ifndef _Random_Generator_MT_SFMT_H_
#define _Random_Generator_MT_SFMT_H_

#include "unique-parameter-128bit.h"
#include "vector.h"
#include <cstring>

#ifdef HAVE_SSE2
#include <emmintrin.h>
#endif

namespace std {

#ifdef HAVE_SSE2
  __m128i SFMT_SSE2_ParamMask;
#endif

  template <unsigned int LoopFac=19937>
  struct SFMT {
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

    UniqueParameter128b *status;
    unsigned int *idx;
    UniqueParameter128b *output;
    unsigned int state;

    typedef SFMT<LoopFac> Type;

    SFMT()
      : status(NULL), idx(NULL), output(NULL), state(Unused) {}
    SFMT(const Type&) { myError("Cannot create from SFMT generator"); }
    Type& operator=(const Type& sg) { assign(*this,sg); return *this; }
    ~SFMT() { release(*this); }

    void Init(const unsigned int seed) { init(*this,seed); }
    void Init(const unsigned int* key, const unsigned int len,
              const unsigned int off=uZero, const unsigned int step=uOne) {
      init(*this,key,len,off,step);
    }
    void Init(const Vector<unsigned int>& key) { init(*this,key); }

    const unsigned int& UInt32() {
      if(*idx>=SFMT<LoopFac>::N32) { GenRandAll(); *idx=0; }
      return status->u[(*idx)++];
    }

    const unsigned long long int& UInt64() {
      assert(((*idx)&1)==0);
      if(*idx>=SFMT<LoopFac>::N32) { GenRandAll(); *idx=0; }
      output->ull[0]=status->ull[(*idx)>>1];
      *idx+=2;
      return output->ull[0];
    }

    const double& DoubleClose0Close1() {
      output->d[0]=static_cast<double>(static_cast<int>(UInt32()))
                  *(1./4294967295.0)+(0.5+0.5/4294967295.0);
      return output->d[0];
    }
    const double& DoubleClose0Open1() {
      output->d[0]=static_cast<double>(static_cast<int>(UInt32()))
                  *(1./4294967296.0)+0.5;
      return output->d[0];
    }
    const double& DoubleOpen0Open1() {
      output->d[0]=static_cast<double>(static_cast<int>(UInt32()))
                  *(1./4294967296.0)+(0.5+0.5/4294967296.0);
      return output->d[0];
    }
    const double& Double53Close0Open1() {
      long x,y;
      x=static_cast<long>(UInt32()>>5);
      y=static_cast<long>(UInt32()>>6);
      output->d[0]=(x*67108864.0+y)*(1./9007199254740992.0);
      return output->d[0];
    }
    const double& Double53Close0Open1Slow() {
      unsigned int x,y;
      x=UInt32()>>5;
      y=UInt32()>>6;
      output->d[0]=(x*67108864.0+y)*(1./9007199254740992.0);
      return output->d[0];
    }
    const long double& LDouble63Close0Open1() {
      output->ld=static_cast<long double>(static_cast<long long>(UInt64()))
                *(1./18446744073709551616.0L)+0.5;
      return output->ld;
    }
    const long double& LDouble63Close0Open1Slow() {
      unsigned int x,y;
      x=UInt32();
      y=UInt32();
      output->ld=(x|(static_cast<unsigned long long int>(y)<<32))
                *(1./18446744073709551616.0L);
      return output->ld;
    }

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
    void GenRandAll() {
      unsigned int i;
      __m128i r,r1,r2;
      r1=_mm_loadu_si128(&(status[N-2].si));
      r2=_mm_loadu_si128(&(status[N-1].si));
      for(i=0;i<N-Pos1;++i) {
        r=DoRecursion(status[i].si,status[i+Pos1].si,r1,r2);
        _mm_storeu_si128(&(status[i].si),r);
        r1=r2;
        r2=r;
      }
      for(;i<N;++i) {
        r=DoRecursion(status[i].si,status[i+Pos1-N].si,r1,r2);
        _mm_storeu_si128(&(status[i].si),r);
        r1=r2;
        r2=r;
      }
    }
    void GenRandArray(UniqueParameter128b* array, const unsigned int size) {
      assert(size>=N);
      unsigned int i,j;
      __m128i r,r1,r2;
      r1=_mm_loadu_si128(&(status[N-2].si));
      r2=_mm_loadu_si128(&(status[N-1].si));
      for(i=0;i<N-Pos1;++i) {
        r=DoRecursion(status[i].si,status[i+Pos1].si,r1,r2);
        _mm_storeu_si128(&(array[i].si),r);
        r1=r2;
        r2=r;
      }
      for(;i<N;++i) {
        r=DoRecursion(status[i].si,array[i+Pos1-N].si,r1,r2);
        _mm_storeu_si128(&(array[i].si),r);
        r1=r2;
        r2=r;
      }
      for(;i+N<size;++i) {
        r=DoRecursion(array[i-N].si,array[i+Pos1-N].si,r1,r2);
        _mm_storeu_si128(&(array[i].si),r);
        r1=r2;
        r2=r;
      }
      for(j=0;j+size<N+N;++j) {
        r=_mm_loadu_si128(&(array[j+size-N].si));
        _mm_storeu_si128(&(status[j].si),r);
      }
      for(;i<size;++i) {
        r=DoRecursion(array[i-N].si,array[i+Pos1-N].si,r1,r2);
        _mm_storeu_si128(&(array[i].si),r);
        _mm_storeu_si128(&(status[j++].si),r);
        r1=r2;
        r2=r;
      }
    }
#else
    UniqueParameter128b& DoRecursion(
        const UniqueParameter128b& a, const UniqueParameter128b& b,
        const UniqueParameter128b& c, const UniqueParameter128b& d) {
      static UniqueParameter128b r,x,y;
      lshift128(x,a,SL2);
      rshift128(y,c,SR2);
      r.u[0]=a.u[0]^x.u[0]^((b.u[0]>>SR1)&Msk1)^y.u[0]^(d.u[0]<<SL1);
      r.u[1]=a.u[1]^x.u[1]^((b.u[1]>>SR1)&Msk2)^y.u[1]^(d.u[1]<<SL1);
      r.u[2]=a.u[2]^x.u[2]^((b.u[2]>>SR1)&Msk3)^y.u[2]^(d.u[2]<<SL1);
      r.u[3]=a.u[3]^x.u[3]^((b.u[3]>>SR1)&Msk4)^y.u[3]^(d.u[3]<<SL1);
    }
    void GenRandAll() {
      unsigned int i;
      UniqueParameter128b *r1=&status[N-2];
      UniqueParameter128b *r2=&status[N-1];
      for(i=0;i<N-Pos1;++i) {
        status[i]=DoRecursion(status[i],status[i+Pos1],*r1,*r2);
        r1=r2;
        r2=&status[i];
      }
      for(;i<N;++i) {
        status[i]=DoRecursion(status[i],status[i+Pos1-N],*r1,*r2);
        r1=r2;
        r2=&status[i];
      }
    }
    void GenRandArray(UniqueParameter128b* array, const unsigned int size) {
      unsigned int i,j;
      UniqueParameter128b *r1=&status[N-2];
      UniqueParameter128b *r2=&status[N-1];
      for(i=0;i<N-Pos1;++i) {
        array[i]=DoRecursion(status[i],status[i+Pos1],*r1,*r2);
        r1=r2;
        r2=&array[i];
      }
      for(;i<N;++i) {
        array[i]=DoRecursion(status[i],array[i+Pos1],*r1,*r2);
        r1=r2;
        r2=&array[i];
      }
      for(;i<size-N;++i) {
        array[i]=DoRecursion(array[i-N],array[i+Pos1-N],r1,r2);
        r1=r2;
        r2=&array[i];
      }
      for(j=0;j<N+N-size;++j) status[j]=array[j+size-N];
      for(;i<size;++i,++j) {
        array[i]=DoRecursion(array[i-N],array[i+Pos1-N],r1,r2);
        r1=r2;
        r2=&array[i];
        status[j]=array[i];
      }
    }
#endif
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
    unsigned int func1(const unsigned int x) {
      return (x^(x>>27))*static_cast<unsigned int>(1664525UL);
    }
    unsigned int func2(const unsigned int x) {
      return (x^(x>>27))&static_cast<unsigned int>(1566083941UL);
    }
    void PeriodCertification() {
      unsigned int inner=0;
      unsigned int i,j,work;
      unsigned int *pSFMT32=&(status[0].u[0]);
      for(i=0;i<4;++i)  inner^=pSFMT32[i]&Parity[i];
      for(i=16;i>0;i>>=1) inner^=inner>>i;
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
  const unsigned int SFMT<LoopFac>::Lag=(SFMT<LoopFac>::N32>=263?11:
                                        (SFMT<LoopFac>::N32>68?7:
                                        (SFMT<LoopFac>::N32>=39?5:3))); 
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Mid=
    (SFMT<LoopFac>::N32-SFMT<LoopFac>::Lag)/2;
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::LagMid=
    SFMT<LoopFac>::Lag+SFMT<LoopFac>::Mid;
  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Parity[4]={
    SFMT<LoopFac>::Parity1, SFMT<LoopFac>::Parity2,
    SFMT<LoopFac>::Parity3, SFMT<LoopFac>::Parity4 };

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
  template <> const unsigned int SFMT<1279>::Msk1=0xF7FEFFFDU;
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
  bool IsAvailable(const SFMT<LoopFac>& sg) { return IsAvailable(sg.status); }

  template <unsigned int LoopFac>
  void IsRandomGenerator(const SFMT<LoopFac>&) { return true; }

  template <unsigned int LoopFac>
  void release(SFMT<LoopFac>& sg) {
    if(sg.state==Allocated) {
      safe_delete_array(sg.status);
      safe_delete(sg.idx);
      safe_delete(sg.output);
    } else {
      sg.status=NULL;
      sg.idx=NULL;
      sg.output=NULL;
    }
    sg.state=Unused;
  }

  template <unsigned int LoopFac>
  void allocate(SFMT<LoopFac>& sg) {
    release(sg);
    sg.status=new UniqueParameter128b[SFMT<LoopFac>::NStatus];
    sg.idx=new unsigned int;
    sg.output=new UniqueParameter128b;
    sg.state=Allocated;
    init(sg,5489U);
  }

  template <unsigned int LoopFac>
  void assign(SFMT<LoopFac>& dest, const SFMT<LoopFac>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.status.src.status,SFMT<LoopFac>::NStatus);
    *dest.idx=*src.idx;
  }

  template <unsigned int LoopFac>
  void refer(SFMT<LoopFac>& dest, const SFMT<LoopFac>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.status=src.status;
    dest.idx=src.idx;
    dest.output=src.output;
    dest.state=Reference;
  }

  template <unsigned int LoopFac>
  void init(SFMT<LoopFac>& sg, const unsigned int seed) {
    assert(IsAvailable(sg));
    unsigned int *pSFMT32=&(sg.status[0].u[0]),work;
    pSFMT32[0]=seed;
    work=pSFMT32[0];
    for(unsigned int i=1;i<SFMT<LoopFac>::N32;++i) {
      work=1812433253UL*(work^(work>>30))+i;
      pSFMT32[i]=work;
    }
    *(sg.idx)=SFMT<LoopFac>::N32;
    sg.PeriodCertification();
  }

  template <unsigned int LoopFac>
  void init(SFMT<LoopFac>& sg,
            const unsigned int *key, const unsigned int len,
            const unsigned int off=uZero, const unsigned int step=uOne) {
    unsigned int i,j,g,count,r,tmid,*pSFMT32;
    pSFMT32=&(sg.status[0].u[0]);
    memset(sg.status,0x8B,SFMT<LoopFac>::NStatusByte);
    count=(len+1>SFMT<LoopFac>::N32?len+1:SFMT<LoopFac>::N32);
    r=sg.func1(pSFMT32[0]^pSFMT32[SFMT<LoopFac>::Mid]
                         ^pSFMT32[SFMT<LoopFac>::N32-1]);
    pSFMT32[SFMT<LoopFac>::Mid]+=r;
    r+=len;
    pSFMT32[SFMT<LoopFac>::LagMid]+=r;
    pSFMT32[0]=r;
    --count;
    for(i=1,j=0,g=off;j<len;++j,g+=step) {
      tmid=(i+SFMT<LoopFac>::Mid)%SFMT<LoopFac>::N32;
      r=sg.func1(pSFMT32[i]^pSFMT32[tmid]
          ^pSFMT32[(i+SFMT<LoopFac>::N32-1)%SFMT<LoopFac>::N32]);
      pSFMT32[tmid]+=r;
      r+=key[g]+i;
      pSFMT32[(i+SFMT<LoopFac>::LagMid)%SFMT<LoopFac>::N32]+=r;
      pSFMT32[i]=r;
      i=(i+1)%SFMT<LoopFac>::N32;
    }
    for(;j<count;++j) {
      tmid=(i+SFMT<LoopFac>::Mid)%SFMT<LoopFac>::N32;
      r=sg.func1(pSFMT32[i]^pSFMT32[tmid]
          ^pSFMT32[(i+SFMT<LoopFac>::N32-1)%SFMT<LoopFac>::N32]);
      pSFMT32[tmid]+=r;
      r+=i;
      pSFMT32[(i+SFMT<LoopFac>::LagMid)%SFMT<LoopFac>::N32]+=r;
      pSFMT32[i]=r;
      i=(i+1)%SFMT<LoopFac>::N32;
    }
    for(j=0;j<SFMT<LoopFac>::N32;++j) {
      tmid=(i+SFMT<LoopFac>::Mid)%SFMT<LoopFac>::N32;
      r=sg.func2(pSFMT32[i]^pSFMT32[tmid]
          ^pSFMT32[(i+SFMT<LoopFac>::N32-1)%SFMT<LoopFac>::N32]);
      pSFMT32[tmid]^=r;
      r-=i;
      pSFMT32[(i+SFMT<LoopFac>::LagMid)%SFMT<LoopFac>::N32]^=r;
      pSFMT32[i]=r;
      i=(i+1)%SFMT<LoopFac>::N32;
    }
    *(sg.idx)=SFMT<LoopFac>::N32;
    sg.PeriodCertification();
  }

  template <unsigned int LoopFac>
  void init(SFMT<LoopFac>& sg, const Vector<unsigned int>& key) {
    init(sg,key(),key.size);
  }

  template <unsigned int LoopFac>
  void fillarray(SFMT<LoopFac>& sg,
                 unsigned int* array, const unsigned int size) {
    assert(*(sg.idx)==SFMT<LoopFac>::N32);
    assert(size%4==0);
    assert(size>=SFMT<LoopFac>::N32);
    sg.GenRandArray(reinterpret_cast<UniqueParameter128b*>(array),size>>2);
    *(sg.idx)=SFMT<LoopFac>::N32;
  }

  template <unsigned int LoopFac>
  void fillarray(SFMT<LoopFac>& sg,
                 unsigned long long int* array, const unsigned int size) {
    assert(*(sg.idx)==SFMT<LoopFac>::N32);
    assert(size%2==0);
    assert(size>=SFMT<LoopFac>::N64);
    sg.GenRandArray(reinterpret_cast<UniqueParameter128b*>(array),size>>1);
    *(sg.idx)=SFMT<LoopFac>::N32;
  }

  template <unsigned int LoopFac>
  const unsigned int& rand(SFMT<LoopFac>& sg) { return sg.UInt32(); }

  template <typename T>
  const T& rand(SFMT<607>&) { myError("Default form is prohibited!"); }
  template <typename T>
  const T& rand(SFMT<1279>&) { myError("Default form is prohibited!"); }
  template <typename T>
  const T& rand(SFMT<2281>&) { myError("Default form is prohibited!"); }
  template <typename T>
  const T& rand(SFMT<4253>&) { myError("Default form is prohibited!"); }
  template <typename T>
  const T& rand(SFMT<11213>&) { myError("Default form is prohibited!"); }
  template <typename T>
  const T& rand(SFMT<19937>&) { myError("Default form is prohibited!"); }
  template <typename T>
  const T& rand(SFMT<44497>&) { myError("Default form is prohibited!"); }
  template <typename T>
  const T& rand(SFMT<86243>&) { myError("Default form is prohibited!"); }
  template <typename T>
  const T& rand(SFMT<132049>&) { myError("Default form is prohibited!"); }
  template <typename T>
  const T& rand(SFMT<216091>&) { myError("Default form is prohibited!"); }

  template <>
  const unsigned int& rand<unsigned int>(SFMT<607>& sg) { return rand(sg); }
  template <>
  const unsigned int& rand<unsigned int>(SFMT<1279>& sg) { return rand(sg); }
  template <>
  const unsigned int& rand<unsigned int>(SFMT<2281>& sg) { return rand(sg); }
  template <>
  const unsigned int& rand<unsigned int>(SFMT<4253>& sg) { return rand(sg); }
  template <>
  const unsigned int& rand<unsigned int>(SFMT<11213>& sg) { return rand(sg); }
  template <>
  const unsigned int& rand<unsigned int>(SFMT<19937>& sg) { return rand(sg); }
  template <>
  const unsigned int& rand<unsigned int>(SFMT<44497>& sg) { return rand(sg); }
  template <>
  const unsigned int& rand<unsigned int>(SFMT<86243>& sg) { return rand(sg); }
  template <>
  const unsigned int& rand<unsigned int>(SFMT<132049>& sg) { return rand(sg); }
  template <>
  const unsigned int& rand<unsigned int>(SFMT<216091>& sg) { return rand(sg); }

  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<607>& sg) {
    return sg.UInt64();
  }
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<1279>& sg) {
    return sg.UInt64();
  }
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<2281>& sg) {
    return sg.UInt64();
  }
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<4253>& sg) {
    return sg.UInt64();
  }
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<11213>& sg) {
    return sg.UInt64();
  }
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<19937>& sg) {
    return sg.UInt64();
  }
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<44497>& sg) {
    return sg.UInt64();
  }
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<86243>& sg) {
    return sg.UInt64();
  }
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<132049>& sg) {
    return sg.UInt64();
  }
  template <>
  const unsigned long long int& rand<unsigned long long int>(SFMT<216091>& sg) {
    return sg.UInt64();
  }

  template <>
  const double& rand<double>(SFMT<607>& sg) {
    return sg.Double53Close0Open1();
  }
  template <>
  const double& rand<double>(SFMT<1279>& sg) {
    return sg.Double53Close0Open1();
  }
  template <>
  const double& rand<double>(SFMT<2281>& sg) {
    return sg.Double53Close0Open1();
  }
  template <>
  const double& rand<double>(SFMT<4253>& sg) {
    return sg.Double53Close0Open1();
  }
  template <>
  const double& rand<double>(SFMT<11213>& sg) {
    return sg.Double53Close0Open1();
  }
  template <>
  const double& rand<double>(SFMT<19937>& sg) {
    return sg.Double53Close0Open1();
  }
  template <>
  const double& rand<double>(SFMT<44497>& sg) {
    return sg.Double53Close0Open1();
  }
  template <>
  const double& rand<double>(SFMT<86243>& sg) {
    return sg.Double53Close0Open1();
  }
  template <>
  const double& rand<double>(SFMT<132049>& sg) {
    return sg.Double53Close0Open1();
  }
  template <>
  const double& rand<double>(SFMT<216091>& sg) {
    return sg.Double53Close0Open1();
  }

  template <>
  const long double& rand<long double>(SFMT<607>& sg) {
    return sg.LDouble63Close0Open1();
  }
  template <>
  const long double& rand<long double>(SFMT<1279>& sg) {
    return sg.LDouble63Close0Open1();
  }
  template <>
  const long double& rand<long double>(SFMT<2281>& sg) {
    return sg.LDouble63Close0Open1();
  }
  template <>
  const long double& rand<long double>(SFMT<4253>& sg) {
    return sg.LDouble63Close0Open1();
  }
  template <>
  const long double& rand<long double>(SFMT<11213>& sg) {
    return sg.LDouble63Close0Open1();
  }
  template <>
  const long double& rand<long double>(SFMT<19937>& sg) {
    return sg.LDouble63Close0Open1();
  }
  template <>
  const long double& rand<long double>(SFMT<44497>& sg) {
    return sg.LDouble63Close0Open1();
  }
  template <>
  const long double& rand<long double>(SFMT<86243>& sg) {
    return sg.LDouble63Close0Open1();
  }
  template <>
  const long double& rand<long double>(SFMT<132049>& sg) {
    return sg.LDouble63Close0Open1();
  }
  template <>
  const long double& rand<long double>(SFMT<216091>& sg) {
    return sg.LDouble63Close0Open1();
  }

  template <unsigned int LoopFac>
  ostream& operator<<(ostream& os, const SFMT<LoopFac>& sg) {
    assert(IsAvailable(sg));
    os<<LoopFac<<"\t";
    for(unsigned int i=0;i<SFMT<LoopFac>::NStatus;++i) os<<sg.status[i]<<"\t";
    os<<*(sg.idx);
    return os;
  }

  template <unsigned int LoopFac>
  istream& operator>>(istream& is, SFMT<LoopFac>& sg) {
    assert(IsAvailable(sg));
    unsigned int expLoopFac;
    is>>expLoopFac;
    if(expLoopFac!=LoopFac) myError("Imcompatible data for SFMT generator");
    for(unsigned int i=0;i<SFMT<LoopFac>::NStatus;++i) is>>sg.status[i];
    is>>*(sg.idx);
    return is;
  }

}

#endif

