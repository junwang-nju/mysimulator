
#ifndef _Random_Generator_MT_dSFMT_Operation_H_
#define _Random_Generator_MT_dSFMT_Operation_H_

#include "data/random/random-generator-mt-dsfmt.h"
#include <cstring>

namespace std {

  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& G, const unsigned int seed) {
    assert(IsAvailable(G));
    unsigned int *pSFMT=&(G[0].u[0]),rmt;
    pSFMT[0]=seed;
    rmt=seed;
    for(unsigned int i=1;i<dSFMT<LoopFac>::NStatusU32;++i) {
      rmt=1812433253UL*(rmt^(rmt>>30))+i;
      pSFMT[i]=rmt;
    }
    G.initMask();
    G.PeriodCertification();
    *(G.idx)=dSFMT<LoopFac>::N64;
#ifdef HAVE_SSE2
    G.initConst();
#endif 
  }

  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& G, const unsigned int *key, const unsigned int len,
                               const int off=iZero, const long step=lOne) {
    assert(IsAvailable(G));
    assert(IsAvailable(key));
    unsigned int i,j,g,count,tmid,r,*pSFMT=&(G[0].u[0]);
    memset(G.data,0x8B,dSFMT<LoopFac>::NStatusByte);
    count=(len+1>dSFMT<LoopFac>::NStatusU32?len+1:dSFMT<LoopFac>::NStatusU32);
    tmid=dSFMT<LoopFac>::Mid%dSFMT<LoopFac>::NStatusU32;
    r=G.initfunc1(pSFMT[0]^pSFMT[tmid]^pSFMT[dSFMT<LoopFac>::NStatusU32-1]);
    pSFMT[tmid]+=r;
    r+=len;
    pSFMT[dSFMT<LoopFac>::LagMid%dSFMT<LoopFac>::NStatusU32]+=r;
    pSFMT[0]=r;
    --count;
    for(i=0,j=0,g=off;j<len;++j,g+=step) {
      tmid=(i+dSFMT<LoopFac>::Mid)%dSFMT<LoopFac>::NStatusU32;
      r=G.initfunc1(pSFMT[i]^pSFMT[tmid]
        ^pSFMT[(i+dSFMT<LoopFac>::NStatusU32-1)%dSFMT<LoopFac>::NStatusU32]);
      pSFMT[tmid]+=r;
      r+=key[g]+i;
      pSFMT[(i+dSFMT<LoopFac>::LagMid)%dSFMT<LoopFac>::NStatusU32]+=r;
      pSFMT[i]=r;
      i=(i+1)%dSFMT<LoopFac>::NStatusU32;
    }
    for(;j<count;++j) {
      tmid=(i+dSFMT<LoopFac>::Mid)%dSFMT<LoopFac>::NStatusU32;
      r=G.initfunc1(pSFMT[i]^pSFMT[tmid]
        ^pSFMT[(i+dSFMT<LoopFac>::NStatusU32-1)%dSFMT<LoopFac>::NStatusU32]);
      pSFMT[tmid]+=r;
      r+=i;
      pSFMT[(i+dSFMT<LoopFac>::LagMid)%dSFMT<LoopFac>::NStatusU32]+=r;
      pSFMT[i]=r;
      i=(i+1)%dSFMT<LoopFac>::NStatusU32;
    }
    for(j=0;j<dSFMT<LoopFac>::NStatusU32;++j) {
      tmid=(i+dSFMT<LoopFac>::Mid)%dSFMT<LoopFac>::NStatusU32;
      r=G.initfunc2(pSFMT[i]+pSFMT[tmid]
        +pSFMT[(i+dSFMT<LoopFac>::NStatusU32-1)%dSFMT<LoopFac>::NStatusU32]);
      pSFMT[tmid]^=r;
      r-=i;
      pSFMT[(i+dSFMT<LoopFac>::LagMid)%dSFMT<LoopFac>::NStatusU32]^=r;
      pSFMT[i]=r;
      i=(i+1)%dSFMT<LoopFac>::NStatusU32;
    }
    G.initMask();
    G.PeriodCertification();
    *(G.idx)=dSFMT<LoopFac>::N64;
#ifdef HAVE_SSE2
    G.initConst();
#endif
  }

  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& G, const Vector<unsigned int>& key) {
    init(G,key.data,key.size);
  }

  template <unsigned int LoopFac>
  void GenRandAll(dSFMT<LoopFac>& G) {
    unsigned int i;
    UniqueParameter128b lung;
    G.DoRecursion(G[0],G[dSFMT<LoopFac>::Pos1],G[0],lung);
    for(i=1;i<dSFMT<LoopFac>::N-dSFMT<LoopFac>::Pos1;++i)
      G.DoRecursion(G[i],G[i+dSFMT<LoopFac>::Pos1],G[i],lung);
    for(;i<dSFMT<LoopFac>::N;++i)
      G.DoRecursion(G[i],G[i+dSFMT<LoopFac>::Pos1-dSFMT<LoopFac>::N],G[i],lung);
    copy(G[dSFMT<LoopFac>::N],lung);
  }

  template <typename T>
  const T& rand(dSFMT<521>& G) {
    myError("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(dSFMT<1279>& G) {
    myError("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(dSFMT<2203>& G) {
    myError("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(dSFMT<4253>& G) {
    myError("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(dSFMT<11213>& G) {
    myError("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(dSFMT<19937>& G) {
    myError("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(dSFMT<44497>& G) {
    myError("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(dSFMT<86243>& G) {
    myError("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(dSFMT<132049>& G) {
    myError("Prohibit unknown type");
    return static_cast<T>(0);
  }
  template <typename T>
  const T& rand(dSFMT<216091>& G) {
    myError("Prohibit unknown type");
    return static_cast<T>(0);
  }

  template <unsigned int LoopFac>
  const unsigned int& irand(dSFMT<LoopFac>& G) {
    unsigned long long int *pSFMT=&(G[0].ull[0]);
    if(*(G.idx)>=dSFMT<LoopFac>::N64) { GenRandAll(G); *(G.idx)=0; }
    G.output.u[0]=pSFMT[*(G.idx)]&0xFFFFFFFFUL;
    ++(*(G.idx));
    return G.output.u[0];
  }

  template <>
  const unsigned int& rand<unsigned int>(dSFMT<521>& G){ return irand(G); }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<1279>& G){ return irand(G); }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<2203>& G){ return irand(G); }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<4253>& G){ return irand(G); }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<11213>& G){ return irand(G); }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<19937>& G){ return irand(G); }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<44497>& G){ return irand(G); }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<86243>& G){ return irand(G); }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<132049>& G){ return irand(G); }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<216091>& G){ return irand(G); }

  template <unsigned int LoopFac>
  const double& drand(dSFMT<LoopFac>& G) {
    G.output.d[1]=doubleClose1Open2(G)-1.0;
    return G.output.d[1];
  }

  template <>
  const double& rand<double>(dSFMT<521>& G) { return drand(G); }
  template <>
  const double& rand<double>(dSFMT<1279>& G) { return drand(G); }
  template <>
  const double& rand<double>(dSFMT<2203>& G) { return drand(G); }
  template <>
  const double& rand<double>(dSFMT<4253>& G) { return drand(G); }
  template <>
  const double& rand<double>(dSFMT<11213>& G) { return drand(G); }
  template <>
  const double& rand<double>(dSFMT<19937>& G) { return drand(G); }
  template <>
  const double& rand<double>(dSFMT<44497>& G) { return drand(G); }
  template <>
  const double& rand<double>(dSFMT<86243>& G) { return drand(G); }
  template <>
  const double& rand<double>(dSFMT<132049>& G) { return drand(G); }
  template <>
  const double& rand<double>(dSFMT<216091>& G) { return drand(G); }

  template <unsigned int LoopFac>
  const double& doubleClose1Open2(dSFMT<LoopFac>& G) {
    double* pSFMT=&(G[0].d[0]);
    if(*(G.idx)>=dSFMT<LoopFac>::N64) { GenRandAll(G); *(G.idx)=0; }
    G.output.d[0]=pSFMT[*(G.idx)];
    ++(*(G.idx));
    return G.output.d[0];
  }

  template <unsigned int LoopFac>
  const double& doubleOpen0Close1(dSFMT<LoopFac>& G) {
    G.output.d[1]=2.0-doubleClose1Open2(G);
    return G.output.d[1];
  }

  template <unsigned int LoopFac>
  const double& doubleOpen0Open1(dSFMT<LoopFac>& G) {
    doubleClose1Open2(G);
    G.output.ull[0]|=1;
    G.output.d[1]=G.output.d[0]-1.0;
    return G.output.d[1];
  }

  typedef void (*ConvertFuncType)(UniqueParameter128b&);

  void ConvertClose1Open2(UniqueParameter128b& w) {}
#ifdef HAVE_SSE2
  void ConvertClose0Open1(UniqueParameter128b& w) {
    __m128d wd,cd;
    wd=_mm_loadu_pd(w.d);
    cd=_mm_loadu_pd(reinterpret_cast<double*>(&dSFMT_SSE2_DoubleMOne));
    _mm_storeu_pd(w.d,_mm_add_pd(wd,cd));
  }
  void ConvertOpen0Close1(UniqueParameter128b& w) {
    __m128d wd,cd;
    wd=_mm_loadu_pd(w.d);
    cd=_mm_loadu_pd(reinterpret_cast<double*>(&dSFMT_SSE2_DoubleTwo));
    _mm_storeu_pd(w.d,_mm_sub_pd(cd,wd));
  }
  void ConvertOpen0Open1(UniqueParameter128b& w) {
    __m128i wi,ci;
    wi=_mm_loadu_si128(&(w.si));
    ci=_mm_loadu_si128(&dSFMT_SSE2_IntOne);
    _mm_storeu_si128(&(w.si),_mm_or_si128(wi,ci));
    __m128d wd,cd;
    wd=_mm_loadu_pd(w.d);
    cd=_mm_loadu_pd(reinterpret_cast<double*>(&dSFMT_SSE2_DoubleMOne));
    _mm_storeu_pd(w.d,_mm_add_pd(wd,cd));
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

  template <unsigned int LoopFac>
  void GenRandArray(dSFMT<LoopFac>& G,
                    UniqueParameter128b* array, const unsigned int size,
                    const ConvertFuncType& cvfunc) {
    unsigned int i,j;
    UniqueParameter128b lung;
    copy(lung,G[dSFMT<LoopFac>::N]);
    G.DoRecursion(G[0],G[dSFMT<LoopFac>::Pos1],array[0],lung);
    for(i=0;i<dSFMT<LoopFac>::N-dSFMT<LoopFac>::Pos1;++i)
      G.DoRecursion(G[i],G[i+dSFMT<LoopFac>::Pos1],array[i],lung);
    for(;i<dSFMT<LoopFac>::N;++i)
      G.DoRecursion(G[i],array[i+dSFMT<LoopFac>::Pos1-dSFMT<LoopFac>::N],
                    array[i],lung);
    for(;i+dSFMT<LoopFac>::N<size;++i) {
      G.DoRecursion(array[i-dSFMT<LoopFac>::N],
                    array[i+dSFMT<LoopFac>::Pos1-dSFMT<LoopFac>::N],
                    array[i],lung);
      cvfunc(array[i-dSFMT<LoopFac>::N]);
    }
    for(j=0;j+size<dSFMT<LoopFac>::N*2;++j)
      copy(G[j],array[j+size-dSFMT<LoopFac>::N]);
    for(;i<size;++i,++j) {
      G.DoRecursion(array[i-dSFMT<LoopFac>::N],
                    array[i+dSFMT<LoopFac>::Pos1-dSFMT<LoopFac>::N],
                    array[i],lung);
      copy(G[j],array[i]);
      cvfunc(array[i-dSFMT<LoopFac>::N]);
    }
    for(i=size-dSFMT<LoopFac>::N;i<size;++i)  cvfunc(array[i]);
    copy(G[dSFMT<LoopFac>::N],lung);
  }

  template <unsigned int LoopFac>
  void FillArrayImpl(dSFMT<LoopFac>& G, double* array, const unsigned int size,
                     const ConvertFuncType& cvf) {
    assert((size&1)==0);
    assert(size>=dSFMT<LoopFac>::N64);
    GenRandArray(G,reinterpret_cast<UniqueParameter128b*>(array),size>>1,cvf);
  }

  template <unsigned int LoopFac>
  void fillarray(dSFMT<LoopFac>& G, double* array, const unsigned int size) {
    FillArrayImpl(G,array,size,ConvertClose0Open1);
  }

  template <unsigned int LoopFac>
  void fillarrayClose1Open2(dSFMT<LoopFac>& G,
                            double* array, const unsigned int size) {
    FillArrayImpl(G,array,size,ConvertClose1Open2);
  }

  template <unsigned int LoopFac>
  void fillarrayOpen0Close1(dSFMT<LoopFac>& G,
                            double* array, const unsigned int size) {
    FillArrayImpl(G,array,size,ConvertOpen0Close1);
  }

  template <unsigned int LoopFac>
  void fillarrayOpen0Open1(dSFMT<LoopFac>& G,
                            double* array, const unsigned int size) {
    FillArrayImpl(G,array,size,ConvertOpen0Open1);
  }

}

#endif
