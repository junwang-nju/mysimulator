
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
    G.initmask();
    G.PeriodCertification();
    *(G.idx)=dSFMT<LoopFac>::N64;
#ifdef HAVE_SSE2
    G.initConst();
#endif
  }

  template <unsigned int LoopFac>
  void GenRandAll(dSFMT<LoopFac>& G) {
    unsigned int i;
    UniqueParameter128b lung;
    G.DoRecursion(G[0],G[dSFMT<LoopFac>::Pos1],G[0],lung);
    for(i=1;i<dSFMT<LoopFac>::N-dSFMT<LoopFac>::Pos1;++i)
      DoRecursion(G[i],G[i+dSFMT<LoopFac>::Pos1],G[i],lung);
    for(;i<dSFMT<LoopFac>::N;++i)
      DoRecursion(G[i],G[i+dSFMT<LoopFac>::Pos1-dSFMT<LoopFac>::N],G[i],lung);
    copy(G[dSFMT<LoopFac>::N],lung);
  }

  template <typename T, unsigned int LoopFac>
  const T& rand(dSFMT<LoopFac>& G) {
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

}

#endif
