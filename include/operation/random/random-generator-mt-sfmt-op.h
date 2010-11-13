
#ifndef _Random_Generator_MT_SFMT_Operation_H_
#define _Random_Generator_MT_SFMT_Operation_H_

#include "data/random/random-generator-mt-sfmt.h"
#include <cstring>

namespace std {

#ifdef HAVE_SSE2
  template <unsigned int LoopFac>
  void GenRandAll(SFMT<LoopFac>& G) {
    unsigned int i;
    __m128i r,r1,r2;
    r1=_mm_loadu_si128(&(G[SFMT<LoopFac>::N-2].si));
    r2=_mm_loadu_si128(&(G[SFMT<LoopFac>::N-1].si));
    for(i=0;i<SFMT<LoopFac>::N-SFMT<LoopFac>::Pos1;++i) {
      r=G.DoRecursion(G[i].si,G[i+SFMT<LoopFac>::Pos1].si,r1,r2);
      _mm_storeu_si128(&(G[i].si),r);
      r1=r2;
      r2=r;
    }
    for(;i<SFMT<LoopFac>::N;++i) {
      r=G.DoRecursion(G[i].si,G[i+SFMT<LoopFac>::Pos1-SFMT<LoopFac>::N].si,
                      r1,r2);
      _mm_storeu_si128(&(G[i].si),r);
      r1=r2;
      r2=r;
    }
  }
  template <unsigned int LoopFac>
  void GenRandArray(SFMT<LoopFac>& G,
                    UniqueParameter128b* array, const unsigned int size) {
    assert(size>=SFMT<LoopFac>::N);
    unsigned i,j;
    __m128i r,r1,r2;
    r1=_mm_loadu_si128(&(G[SFMT<LoopFac>::N-2].si));
    r2=_mm_loadu_si128(&(G[SFMT<LoopFac>::N-1].si));
    for(i=0;i<SFMT<LoopFac>::N-SFMT<LoopFac>::Pos1;++i) {
      r=G.DoRecursion(G[i].si,G[i+SFMT<LoopFac>::Pos1].si,r1,r2);
      _mm_storeu_si128(&(array[i].si),r);
      r1=r2;
      r2=r;
    }
    for(;i<SFMT<LoopFac>::N;++i) {
      r=G.DoRecursion(G[i].si,array[i+SFMT<LoopFac>::Pos1-SFMT<LoopFac>::N].si,
                      r1,r2);
      _mm_storeu_si128(&(array[i].si),r);
      r1=r2;
      r2=r;
    }
    for(;i+SFMT<LoopFac>::N<size;++i) {
      r=G.DoRecursion(array[i-SFMT<LoopFac>::N].si,
                      array[i+SFMT<LoopFac>::Pos1-SFMT<LoopFac>::N].si,r1,r2);
      _mm_storeu_si128(&(array[i].si),r);
      r1=r2;
      r2=r;
    }
    for(j=0;j+size<SFMT<LoopFac>::N*2;++j) {
      r=_mm_loadu_si128(&(array[j+size-SFMT<LoopFac>::N].si));
      _mm_storeu_si128(&(G[j].si),r);
    }
    for(;i<size;++i) {
      r=G.DoRecursion(array[i-SFMT<LoopFac>::N].si,
                      array[i+SFMT<LoopFac>::Pos1-SFMT<LoopFac>::N].si,r1,r2);
      _mm_storeu_si128(&(array[i].si),r);
      _mm_storeu_si128(&(G[j++].si),r);
      r1=r2;
      r2=r;
    }
  }
#else
  template <unsigned int LoopFac>
  void GenRandAll(SFMT<LoopFac>& G) {
    unsigned int i;
    UniqueParameter128b *r1=&(G[SFMT<LoopFac>::N-2]);
    UniqueParameter128b *r2=&(G[SFMT<LoopFac>::N-1]);
    for(i=0;i<SFMT<LoopFac>::N-SFMT<LoopFac>::Pos1;++i) {
      G[i]=G.DoRecursion(G[i],G[i+SFMT<LoopFac>::Pos1],*r1,*r2);
      r1=r2;
      r2=&(G[i]);
    }
    for(;i<N;++i) {
      G[i]=G.DoRecursion(G[i],G[i+SFMT<LoopFac>::Pos1-SFMT<LoopFac>::N],
                         *r1,*r2);
      r1=r2;
      r2=r;
    }
  }
  template <unsigned int LoopFac>
  void GenRandArray(SFMT<LoopFac>& G,
                    UniqueParameter128b* array, const unsigned int size) {
    unsigned int i,j;
    UniqueParameter128b *r1=&(G[SFMT<LoopFac>::N-2]);
    UniqueParameter128b *r2=&(G[SFMT<LoopFac>::N-1]);
    for(i=0;i<SFMT<LoopFac>::N-SFMT<LoopFac>::Pos1;++i) {
      copy(array[i],G.DoRecursion(G[i],G[i+SFMT<LoopFac>::Pos1],*r1,*r2));
      r1=r2;
      r2=&array[i];
    }
    for(;i<SFMT<LoopFac>::N;++i) {
      copy(array[i],G.DoRecursion(G[i],array[i+SFMT<LoopFac>::Pos1],*r1,*r2));
      r1=r2;
      r2=&array[i];
    }
    for(;i+SFMT<LoopFac>::N<size;++i) {
      copy(array[i],
           G.DoRecursion(array[i-SFMT<LoopFac>::N],
                         array[i+SFMT<LoopFac>::Pos1-SFMT<LoopFac>::N],
                         *r1,*r2));
      r1=r2;
      r2=&array[i];
    }
    for(j=0;j+size<SFMT<LoopFac>::N*2;++j)
      G[j]=array[j+size-SFMT<LoopFac>::N];
    for(;i<size;++i,++j) {
      copy(array[i],
           G.DoRecursion(array[i-N],
                         array[i+SFMT<LoopFac>::Pos1-SFMT<LoopFac>::N],
                         *r1,*r2));
           r1=r2;
           r2=&array[i];
           G[j]=array[i];
    }
  }
#endif

  template <unsigned int LoopFac>
  void init(SFMT<LoopFac>& G, const unsigned int seed) {
    assert(IsAvailable(G));
#ifdef HAVE_SSE2
    G.InitConst();
#endif
    unsigned int *pSFMT32=&(G[0].u[0]), work;
    pSFMT32[0]=seed;
    work=pSFMT32[0];
    for(unsigned int i=1;i<SFMT<LoopFac>::N32;++i) {
      work=1812433253UL*(work^(work>>30))+i;
      pSFMT32[i]=work;
    }
    *(G.idx)=SFMT<LoopFac>::N32;
    G.PeriodCertification();
  }

  template <unsigned int LoopFac>
  void init(SFMT<LoopFac>& G, const unsigned int *key, const unsigned int len,
                              const int off=iZero, const long step=lOne) {
#ifdef HAVE_SSE2
    G.InitConst();
#endif
    unsigned int i,j,g,count,r,tmid,*pSFMT32=&(G[0].u[0]);
    memset(G.data,0x8B,SFMT<LoopFac>::NStatusByte);
    count=(len+1>SFMT<LoopFac>::N32?len+1:SFMT<LoopFac>::N32);
    r=G.func1(pSFMT32[0]^pSFMT32[SFMT<LoopFac>::Mid]
                        ^pSFMT32[SFMT<LoopFac>::N32-1]);
    pSFMT32[SFMT<LoopFac>::Mid]+=r;
    r+=len;
    pSFMT32[SFMT<LoopFac>::LagMid]+=r;
    pSFMT32[0]=r;
    --count;
    for(i=1,j=0,g=off;j<len;++j,g+=step) {
      tmid=(i+SFMT<LoopFac>::Mid)%SFMT<LoopFac>::N32;
      r=G.func1(pSFMT32[i]^pSFMT32[tmid]
               ^pSFMT32[(i+SFMT<LoopFac>::N32-1)%SFMT<LoopFac>::N32]);
      pSFMT32[tmid]+=r;
      r+=key[g]+i;
      pSFMT32[(i+SFMT<LoopFac>::LagMid)%SFMT<LoopFac>::N32]+=r;
      pSFMT32[i]=r;
      i=(i+1)%SFMT<LoopFac>::N32;
    }
    for(;j<count;++j) {
      tmid=(i+SFMT<LoopFac>::Mid)%SFMT<LoopFac>::N32;
      r=G.func1(pSFMT32[i]^pSFMT32[tmid]
               ^pSFMT32[(i+SFMT<LoopFac>::N32-1)%SFMT<LoopFac>::N32]);
      pSFMT32[tmid]+=r;
      r+=i;
      pSFMT32[(i+SFMT<LoopFac>::LagMid)%SFMT<LoopFac>::N32]+=r;
      pSFMT32[i]=r;
      i=(i+1)%SFMT<LoopFac>::N32;
    }
    for(j=0;j<SFMT<LoopFac>::N32;++j) {
      tmid=(i+SFMT<LoopFac>::Mid)%SFMT<LoopFac>::N32;
      r=G.func2(pSFMT32[i]^pSFMT32[tmid]
               ^pSFMT32[(i+SFMT<LoopFac>::N32-1)%SFMT<LoopFac>::N32]);
      pSFMT32[tmid]^=r;
      r-=i;
      pSFMT32[(i+SFMT<LoopFac>::LagMid)%SFMT<LoopFac>::N32]^=r;
      pSFMT32[i]=r;
      i=(i+1)%SFMT<LoopFac>::N32;
    }
    *(G.idx)=SFMT<LoopFac>::N32;
    G.PeriodCertification();
  }

  template <unsigned int LoopFac>
  void init(SFMT<LoopFac>& G, const Vector<unsigned int>& key) {
    init(G,key.data,key.size);
  }

  template <typename T, unsigned int LoopFac>
  const T& rand(SFMT<LoopFac>& G) {
    myError("Prohibited for unknown type");
    return static_cast<T>(0);
  } 

  template <unsigned int LoopFac>
  const unsigned int& irand(SFMT<LoopFac>& G) {
    if(*(G.idx)>=SFMT<LoopFac>::N32) { GenRandAll(G); *(G.idx)=0; }
    G.output.u[0]=G[0].u[*(G.idx)];
    ++(*(G.idx));
    return G.output.u[0];
  }
  template <>
  const unsigned int& rand<unsigned int,607>(SFMT<607>& G) { return irand(G); }
  template <>
  const unsigned int& rand<unsigned int,1279>(SFMT<1279>& G){
    return irand(G);
  }
  template <>
  const unsigned int& rand<unsigned int,11213>(SFMT<11213>& G) {
    return irand(G);
  }
  template <>
  const unsigned int& rand<unsigned int,19937>(SFMT<19937>& G) {
    return irand(G);
  }
  template <>
  const unsigned int& rand<unsigned int,132049>(SFMT<132049>& G) {
    return irand(G);
  }
  template <>
  const unsigned int& rand<unsigned int,216091>(SFMT<216091>& G) {
    return irand(G);
  }
  template <>
  const unsigned int& rand<unsigned int,2281>(SFMT<2281>& G) {
    return irand(G);
  }
  template <>
  const unsigned int& rand<unsigned int,4253>(SFMT<4253>& G) {
    return irand(G);
  }
  template <>
  const unsigned int& rand<unsigned int,44497>(SFMT<44497>& G) {
    return irand(G);
  }
  template <>
  const unsigned int& rand<unsigned int,86243>(SFMT<86243>& G) {
    return irand(G);
  }

  template <unsigned int LoopFac>
  const unsigned long long int& lirand(SFMT<LoopFac>& G) {
    assert(((*(G.idx))&1)==0);
    if(*(G.idx)>=SFMT<LoopFac>::N32) { GenRandAll(G); *(G.idx)=0; }
    G.output.ull[0]=G[0].ull[(*(G.idx))>>1];
    *(G.idx)+=2;
    return G.output.ull[0];
  }

  template <>
  const unsigned long long int& rand<unsigned long long int,607>(
      SFMT<607>& G){ return lirand(G); }
  template <>
  const unsigned long long int& rand<unsigned long long int,1279>(
      SFMT<1279>& G){ return lirand(G); }
  template <>
  const unsigned long long int& rand<unsigned long long int,11213>(
      SFMT<11213>& G){ return lirand(G); }
  template <>
  const unsigned long long int& rand<unsigned long long int,19937>(
      SFMT<19937>& G){ return lirand(G); }
  template <>
  const unsigned long long int& rand<unsigned long long int,132049>(
      SFMT<132049>& G){ return lirand(G); }
  template <>
  const unsigned long long int& rand<unsigned long long int,216091>(
      SFMT<216091>& G){ return lirand(G); }
  template <>
  const unsigned long long int& rand<unsigned long long int,2281>(
      SFMT<2281>& G){ return lirand(G); }
  template <>
  const unsigned long long int& rand<unsigned long long int,4253>(
      SFMT<4253>& G){ return lirand(G); }
  template <>
  const unsigned long long int& rand<unsigned long long int,44497>(
      SFMT<44497>& G){ return lirand(G); }
  template <>
  const unsigned long long int& rand<unsigned long long int,86243>(
      SFMT<86243>& G){ return lirand(G); }

  template <unsigned int LoopFac>
  const double& drand(SFMT<LoopFac>& G) {
    long x=static_cast<long>(irand(G)>>5);
    long y=static_cast<long>(irand(G)>>6);
    G.output.d[0]=(x*67108864.0+y)*(1./9007199254740992.0);
    return G.output.d[0];
  }

  template <>
  const double& rand<double,607>(SFMT<607>& G) { return drand(G); }
  template <>
  const double& rand<double,1279>(SFMT<1279>& G) { return drand(G); }
  template <>
  const double& rand<double,11213>(SFMT<11213>& G) { return drand(G); }
  template <>
  const double& rand<double,19937>(SFMT<19937>& G) { return drand(G); }
  template <>
  const double& rand<double,132049>(SFMT<132049>& G) { return drand(G); }
  template <>
  const double& rand<double,216091>(SFMT<216091>& G) { return drand(G); }
  template <>
  const double& rand<double,2281>(SFMT<2281>& G) { return drand(G); }
  template <>
  const double& rand<double,4253>(SFMT<4253>& G) { return drand(G); }
  template <>
  const double& rand<double,44497>(SFMT<44497>& G) { return drand(G); }
  template <>
  const double& rand<double,86243>(SFMT<86243>& G) { return drand(G); }

  template <unsigned int LoopFac>
  const long double& ldrand(SFMT<LoopFac>& G) {
    G.output.ld=static_cast<long double>(static_cast<long long>(lirand(G)))
               *(1./18446744073709551616.0L)+0.5;
    return G.output.ld;
  }

  template <>
  const long double& rand<long double,607>(SFMT<607>& G) { return ldrand(G); }
  template <>
  const long double& rand<long double,1279>(SFMT<1279>& G) {
    return ldrand(G);
  }
  template <>
  const long double& rand<long double,11213>(SFMT<11213>& G) {
    return ldrand(G);
  }
  template <>
  const long double& rand<long double,19937>(SFMT<19937>& G) {
    return ldrand(G);
  }
  template <>
  const long double& rand<long double,132049>(SFMT<132049>& G) {
    return ldrand(G);
  }
  template <>
  const long double& rand<long double,216091>(SFMT<216091>& G) {
    return ldrand(G);
  }
  template <>
  const long double& rand<long double,2281>(SFMT<2281>& G) {
    return ldrand(G);
  }
  template <>
  const long double& rand<long double,4253>(SFMT<4253>& G) {
    return ldrand(G);
  }
  template <>
  const long double& rand<long double,44497>(SFMT<44497>& G) {
    return ldrand(G);
  }
  template <>
  const long double& rand<long double,86243>(SFMT<86243>& G) {
    return ldrand(G);
  }

  template <unsigned int LoopFac>
  const double& doubleClose0Close1(SFMT<LoopFac>& G) {
    G.output.d[0]=static_cast<double>(static_cast<int>(irand(G)))
                 *(1./4294967295.0)+(0.5+0.5/4294967295.0);
    return G.output.d[0];
  }
  template <unsigned int LoopFac>
  const double& doubleClose0Open1(SFMT<LoopFac>& G) {
    G.output.d[0]=static_cast<double>(static_cast<int>(irand(G)))
                 *(1./4294967296.0)+0.5;
    return G.output.d[0];
  }
  template <unsigned int LoopFac>
  const double& doubleOpen0Open1(SFMT<LoopFac>& G) {
    G.output.d[0]=static_cast<double>(static_cast<int>(irand(G)))
                 *(1./4294967296.0)+(0.5+0.5/4294967296.0);
    return G.output.d[0];
  }
  template <unsigned int LoopFac>
  const double& double53bitSlow(SFMT<LoopFac>& G) {
    unsigned int x,y;
    x=irand(G)>>5;
    y=irand(G)>>6;
    G.output.d[0]=(x*67108864.0+y)*(1./9007199254740992.0);
    return G.output.d[0];
  }
  template <unsigned int LoopFac>
  const long double& longdouble63bitSlow(SFMT<LoopFac>& G) {
    unsigned int x,y;
    x=irand(G);
    y=irand(G);
    G.output.ld=(x|(static_cast<unsigned long long int>(y)<<32))
               *(1./18446744073709551616.0L);
    return G.output.ld;
  }

  template <unsigned int LoopFac>
  void fillarray(SFMT<LoopFac>& G,
                 unsigned int *array, const unsigned int size) {
    assert(*(G.idx)==SFMT<LoopFac>::N32);
    assert(size%4==0);
    assert(size>=SFMT<LoopFac>::N32);
    GenRandArray(G,reinterpret_cast<UniqueParameter128b*>(array),size>>2);
    *(G.idx)=SFMT<LoopFac>::N32;
  }

}

#endif
