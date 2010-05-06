
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
    static const unsigned int N32;
    static const unsigned int N64;
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

    UniqueParameter128b *status;
    unsigned int *idx;
    UniqueParameter128b *output;
    unsigned int state;

    typedef SFMT<LoopFac> Type;

    SFMT()
      : status(NULL), idx(NULL), output(NULL), first(NULL), state(Unused) {}
    SFMT(const Type&) { myError("Cannot create from SFMT generator"); }
    Type& operator=(const Type& sg) { assign(*this,sg); return *this; }
    ~SFMT() { release(*this); }

#ifdef HAVE_SSE2
    void InitConst() {
      static bool first=true;
      if(!first)  return;
      SFMT_SSE2_ParamMask=_mm_set_epi32(Msk4,Msk3,Msk2,Msk1);
      first=false;
    }
    __m128i DoRecursion(const __m128i& a, const __m128i& b, const __m128i& c
                        const __m128i& d) {
      __m128i v,x,y,z;
      x=_mm_load_si128(&a);
      y=_mm_srli_epi32(b,SR1);
      z=_mm_srli_si128(c,SR2);
      v=_mm_slli_epi32(d,SL1);
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
      r1=_mm_load_si128(&(status[N-2].si));
      r2=_mm_load_si128(&(status[N-1].si));
      for(i=0;i<N-Pos1;++i) {
        r=DoRecursion(status[i].si,status[i+Pos1].si,r1,r2);
        _mm_store_si128(&(status[i].si),r);
        r1=r2;
        r2=r;
      }
      for(;i<N;++i) {
        r=DoRecursion(status[i].si,status[i+Pos1-N].si,r1,r2);
        _mm_store_si128(&(status[i].si),r);
        r1=r2;
        r2=r;
      }
    }
    void GenRandArray(UniqueParameter128b* array, const unsigned int size) {
      assert(size>=N);
      unsigned int i,j;
      __m128i r,r1,r2;
      r1=_mm_load_si128(&(status[N-2].si));
      r2=_mm_load_si128(&(status[N-1].si));
      for(i=0;i<N-Pos1;++i) {
        r=DoRecursion(status[i].si,status[i+Pos1].si,r1,r2);
        _mm_store_si128(&(array[i].si),r);
        r1=r2;
        r2=r;
      }
      for(;i<N;++i) {
        r=DoRecursion(status[i].si,array[i+Pos1-N].si,r1,r2);
        _mm_store_si128(&(array[i].si),r);
        r1=r2;
        r2=r;
      }
      for(;i<size-N;++i) {
        r=_DoRecursion(array[i-N].si,array[i+Pos1-N].si,r1,r2);
        _mm_store_si128(&(array[i].si),r);
        r1=r2;
        r2=r;
      }
      for(j=0;j<N+N-size;++j) {
        r=_mm_load_si128(&(array[j+size-N].si));
        _mm_store_si128(&(status[j].si),r);
      }
      for(;i<size;++i) {
        r=DoRecursion(array[i-N].si,array[i+po1-N].si,r1,r2);
        _mm_store_si128(&(array[i].si),r);
        _mm_store_si128(&(array[j++].si),r);
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
      rshift124(y,c,SR2);
      r.u[0]=a.u[0]^x.u[0]^((b.u[0]>>SR1)&Msk1)^y.u[0]^(d.u[0]<<SL1);
      r.u[1]=a.u[1]^x.u[1]^((b.u[1]>>SR1)&Msk1)^y.u[1]^(d.u[1]<<SL1);
      r.u[2]=a.u[2]^x.u[2]^((b.u[2]>>SR1)&Msk1)^y.u[2]^(d.u[2]<<SL1);
      r.u[3]=a.u[3]^x.u[3]^((b.u[3]>>SR1)&Msk1)^y.u[3]^(d.u[3]<<SL1);
    }
#endif

  };

}

#endif

