
#ifndef _Random_Generator_MT_DSFMT_H_
#define _Random_Generator_MT_DSFMT_H_

#include "unique-parameter-128bit.h"
#include "vector.h"

namespace std {

#ifdef HAVE_SSE2
  __m128i   SSE2_ParamMask;
  __m128i   SSE2_IntOne;
  __m128d   SSE2_DoubleTwo;
  __m128d   SSE2_DoubleMOne;  
#endif

  void ConvertClose1Open2(UniqueParameter128b&) {}
#ifdef HAVE_SSE2
  void ConvertClose0Open1(UniqueParameter128b& w) {
    w.sd=_mm_add_pd(w.sd,SSE2_DoubleMOne);
  }
  void ConvertOpen0Close1(UniqueParameter128b& w) {
    w.sd=_mm_sub_pd(SSE2_DoubleTwo,w.sd);
  }
  void ConvertOpen0Open1(UniqueParameter128b& w) {
    w.si=_mm_or_si128(w.si,SSE2_IntOne);
    w.sd=_mm_add_pd(w.sd,SSE2_DoubleMOne);
  }
#else
  void ConvertClose0Open1(UniqueParameter128b& w) { w.d[0]-=1.0; w.d[1]-=1.0; }
  void ConvertOpen0Close1(UniqueParameter128b& w) {
    w.d[0]=2.0-w.d[0];
    w.d[1]=2.0-w.d[1];
  }
  void ConvertOpen0Open1(UniqueParameter128b& w) {
    w.ull[0]|=1;
    w.ull[1]|=1;
    w.d[0]-=1.0;
    w.d[1]-=1.0;
  }
#endif

  template <unsigned int LoopFac=19937>
  struct dSFMT {

    static const unsigned int MExp;
    static const unsigned int N;
    static const unsigned int NStatus;
    static const unsigned int N32;
    static const unsigned int N64;
    static const unsigned long long int LowMask;
    static const unsigned long long int HighConst;
    static const unsigned int SR;
#ifdef HAVE_SSE2
    static const unsigned int SSE2_Shuff;
#endif
    static const unsigned int Pos1;
    static const unsigned int SL1;
    static const unsigned long long int Msk1;
    static const unsigned long long int Msk2;
    static const unsigned int Msk32_1;
    static const unsigned int Msk32_2;
    static const unsigned int Msk32_3;
    static const unsigned int Msk32_4;
    static const unsigned long long int Fix1;
    static const unsigned long long int Fix2;
    static const unsigned long long int Pcv1;
    static const unsigned long long int Pcv2;
    static const unsigned int IsFacAvailable;

    UniqueParameter128b *status;
    unsigned int *idx;
    UniqueParameter128b *output;
    unsigned int state;

    typedef dSFMT<LoopFac>    Type;
    typedef void (*ConvertFuncType)(UniqueParameter128b&);

    dSFMT() : status(NULL), idx(NULL), output(NULL), state(Unused) {
      assert(IsFacAvailable!=0);
    }
    dSFMT(const Type&) { myError("Cannot create from dSFMT generator"); }
    Type& operator=(const Type& dg) { assign(*this,dg); return *this; }
    ~dSFMT() { release(*this); }

#ifdef HAVE_SSE2
    void InitConst() {
      static bool first=true;
      if(!first)  return;
      SSE2_ParamMask=_mm_set_epi32(Msk32_3,Msk32_4,Msk32_1,Msk32_2); // Endian?
      SSE2_IntOne=_mm_set_epi32(0,1,0,1);
      SSE2_DoubleTwo=_mm_set_pd(2.0,2.0);
      SSE2_DoubleMOne=_mm_set_pd(-1.0,-1.0);
      first=false;
    }
    void DoRecursion(const UniqueParameter128b& a,
                     const UniqueParameter128b& b,
                     UniqueParameter128b& r, UniqueParameter128b& u) {
      __m128i v,w,x,y,z;
      x=a.si;
      z=_mm_slli_epi64(x,SL1);
      y=_mm_shuffle_epi32(u.si,SSE2_Shuff);
      z=_mm_xor_si128(z,b.si);
      y=_mm_xor_si128(y,z);
      v=_mm_srli_epi64(y,SR);
      w=_mm_and_si128(y,SSE2_ParamMask);
      v=_mm_xor_si128(v,x);
      v=_mm_xor_si128(v,w);
      r.si=v;
      u.si=y;
    }
#else
    void DoRecursion(const UniqueParameter128b& a,
                     const UniqueParameter128b& b,
                     UniqueParameter128b& r, UniqueParameter128b& u) {
      unsigned long long int t0,t1,L0,L1;
      t0=a.ull[0];
      t1=a.ull[1];
      L0=u.ull[0];
      L1=u.ull[1];
      u.ull[0]=(t0<<SL1)^(L1>>32)^(L1<<32)^b.ull[0];
      u.ull[1]=(t1<<SL1)^(L0>>32)^(L0<<32)^b.ull[1];
      r.ull[0]=(u.ull[0]>>SR)^(u.ull[0]&Msk1)^t0;
      r.ull[1]=(u.ull[1]>>SR)^(u.ull[1]&Msk1)^t1;
    }
#endif

    void init(const unsigned int seed) { init(*this,seed); }
    void init(const unsigned int* key, const unsigned int len,
              const unsigned int off=uZero, const unsigned int step=uOne) {
      init(*this,key,len,off,step);
    }
    void init(const Vector<unsigned int>& key) { init(*this,key); }

  };

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::MExp=LoopFac;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N=((dSFMT<LoopFac>::MExp-128)/104+1);
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::NStatus=dSFMT<LoopFac>::N+1;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N32=dSFMT<LoopFac>::N*4;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N64=dSFMT<LoopFac>::N*2;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::LowMask=0x000FFFFFFFFFFFFFULL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::HighConst=0x3FF0000000000000ULL;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SR=12;
#ifdef HAVE_SSE2
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SSE2_Shuff=0x1BU;
#endif 

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Pos1=0U;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SL1=0U;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Msk1=0ULL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Msk2=0ULL;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_1=
    (dSFMT<LoopFac>::Msk1>>32)&0xFFFFFFFFUL;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_2=dSFMT<LoopFac>::Msk1&0xFFFFFFFFUL;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_3=
    (dSFMT<LoopFac>::Msk2>>32)&0xFFFFFFFFUL;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_4=dSFMT<LoopFac>::Msk1&0xFFFFFFFFUL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Fix1=0ULL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Fix2=0ULL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Pcv1=0ULL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Pcv2=0ULL;

  template <unsigned int LoopFac>
  bool IsAvailable(const dSFMT<LoopFac>& dg) { return IsAvailable(dg.status); }

  template <unsigned int LoopFac>
  bool IsRandomGenerator(const dSFMT<LoopFac>&) { return false; }

  template <unsigned int LoopFac>
  void assign(dSFMT<LoopFac>& dest, const dSFMT<LoopFac>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.status.src.status,dSFMT<LoopFac>::N+1);
    *dest.idx=*src.idx;
  }

  template <unsigned int LoopFac>
  void release(dSFMT<LoopFac>& dg) {
    if(dg.state==Allocated) {
      safe_delete_array(dg.status);
      safe_delete(dg.idx);
      safe_delete(dg.output);
    } else {
      dg.status=NULL;
      dg.idx=NULL;
      dg.output=NULL;
    }
    dg.status=Unused;
  }

  template <unsigned int LoopFac>
  void allocate(dSFMT<LoopFac>& dg) {
    release(dg);
    dg.status=new UniqueParameter128b[dSFMT<LoopFac>::N+1];
    dg.idx=new unsigned int;
    dg.output=new UniqueParameter128b;
    dg.state=Allocated;
  }

  template <unsigned int LoopFac>
  void refer(dSFMT<LoopFac>& dest, const dSFMT<LoopFac>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.status=src.status;
    dest.idx=src.idx;
    dest.output=src.output;
    dest.state=Reference;
  }

  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& dg, const unsigned int seed) {
  }

  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& dg,
            const unsigned int* key, const unsigned int len,
            const unsigned int off=uZero, const unsigned int step=uOne) {
  }

  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& dg, const Vector<unsigned int>& key) {
  }

}

#endif
