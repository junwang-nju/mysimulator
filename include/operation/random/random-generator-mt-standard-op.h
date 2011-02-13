
#ifndef _Random_Generator_MT_Standard_Operation_H_
#define _Random_Generator_MT_Standard_Operation_H_

#include "data/random/random-generator-mt-standard.h"

namespace std {

  void init(MT_Standard& G, const unsigned int seed) {
    assert(IsAvailable(G));
    unsigned int &ri=*(G.mti);
    unsigned int rmt;
    G[0]=seed&MT_Standard::Mask32b;
    rmt=G[0];
    for(ri=1;ri<MT_Standard::N;++ri) {
      rmt=1812433253UL*(rmt^(rmt>>30))+ri;
      rmt&=MT_Standard::Mask32b;
      G[ri]=rmt;
    }
    *(G.mti)=1;
  }
  void init(MT_Standard& G, const unsigned int* key, const unsigned int len,
                            const int off=iZero, const long step=lOne) {
    assert(IsAvailable(G));
    assert(IsAvailable(key));
    unsigned int i,j,k,g,rmt;
    init(G,19650218UL);
    i=1;  j=0;  g=off;
    rmt=G[0];
    k=(MT_Standard::N>len?MT_Standard::N:len);
    for(;k;--k) {
      rmt=(G[i]^((rmt^(rmt>>30))*1664525UL))+key[g]+j;
      rmt&=MT_Standard::Mask32b;
      G[i]=rmt;
      ++i;    ++j;    g+=step;
      if(i>=MT_Standard::N) { G[0]=rmt; i=1; }
      if(j>=len)  { j=0; g=off; }
    }
    for(k=MT_Standard::NmOne;k;--k) {
      rmt=(G[i]^((rmt^(rmt>>30))*1566083941UL))-i;
      rmt&=MT_Standard::Mask32b;
      G[i]=rmt;
      ++i;
      if(i>=MT_Standard::N) { G[0]=rmt; i=1; }
    }
    G[0]=MT_Standard::UppMask;
    *(G.mti)=1;
  }
  void init(MT_Standard& G, const Vector<unsigned int>& key) {
    init(G,key.data,key.size);
  }

  template <typename T>
  const T& rand(MT_Standard& G) {
    Error("Prohibited for unknown type");
    return static_cast<T>(0);
  }

  template <>
  const unsigned int& rand<unsigned int>(MT_Standard& G) {
    unsigned int& ri=*(G.mti);
    unsigned int& u=G.output.u[0];
    if(ri>=MT_Standard::N) {
      unsigned int kk;
      for(kk=0;kk<MT_Standard::dNM;++kk) {
        u=(G[kk]&MT_Standard::UppMask)|(G[kk+1]&MT_Standard::LowMask);
        G[kk]=G[kk+MT_Standard::M]^(u>>1)^MT_Standard::Mag01[u&0x1UL];
      }
      for(;kk<MT_Standard::NmOne;++kk) {
        u=(G[kk]&MT_Standard::UppMask)|(G[kk+1]&MT_Standard::LowMask);
        G[kk]=G[kk-MT_Standard::dNM]^(u>>1)^MT_Standard::Mag01[u&0x1UL];
      }
      u=(G[MT_Standard::NmOne]&MT_Standard::UppMask)|
        (G[0]&MT_Standard::LowMask);
      G[MT_Standard::NmOne]=G[MT_Standard::MmOne]^
                            (u>>1)^MT_Standard::Mag01[u&0x1UL];
      ri=0;
    }
    u=G[ri++];
    u^=(u>>11);
    u^=(u<<7)&0x9D2C5680UL;
    u^=(u<<15)&0xEFC60000UL;
    u^=(u>>18);
    return u;
  }

  template <>
  const int& rand<int>(MT_Standard& G) {
    G.output.i[0]=static_cast<int>(rand<unsigned int>(G)>>1);
    return G.output.i[0];
  }

  template <>
  const double& rand<double>(MT_Standard& G) {
    long x,y;
    x=static_cast<long>(rand<unsigned int>(G)>>5);
    y=static_cast<long>(rand<unsigned int>(G)>>6);
    G.output.d[0]=(x*67108864.0+y)*(1.0/9007199254740992.0);
    return G.output.d[0];
  }

  template <>
  const long double& rand<long double>(MT_Standard& G) {
    long x,y;
    x=static_cast<long>(rand<unsigned int>(G));
    y=static_cast<long>(rand<unsigned int>(G));
    G.output.ld=static_cast<long double>(x*(1.0/4294967296.0))+
                static_cast<long double>(y*(1.0/18446744073709551616.0))+
                (0.5+0.5/4294967296.0);
    return G.output.ld;
  }

  const double& doubleClose0Close1(MT_Standard& G) {
    rand<unsigned int>(G);
    G.output.d[0]=static_cast<double>(G.output.i[0])*(1.0/4294967295.0)+
                  (0.5+0.5/4294967295.0);
    return G.output.d[0];
  }
  const double& doubleClose0Open1(MT_Standard& G) {
    rand<unsigned int>(G);
    G.output.d[0]=static_cast<double>(G.output.i[0])*(1.0/4294967296.0)+0.5;
    return G.output.d[0];
  }
  const double& doubleOpen0Open1(MT_Standard& G) {
    rand<unsigned int>(G);
    G.output.d[0]=static_cast<double>(G.output.i[0])*(1.0/4294967296.0)+
                  (0.5+0.5/4294967296.0);
    return G.output.d[0];
  }
  const double& double53bitSlow(MT_Standard& G) {
    unsigned int x,y;
    x=rand<unsigned int>(G)>>5;
    y=rand<unsigned int>(G)>>6;
    G.output.d[0]=(static_cast<double>(x)*67108864.0+static_cast<double>(y))*
                  (1.0/9007199254740992.0);
    return G.output.d[0];
  }
  const long double& longdouble63bitSlow(MT_Standard& G) {
    unsigned int x,y;
    x=rand<unsigned int>(G);
    y=rand<unsigned int>(G);
    G.output.ld=(x|(static_cast<unsigned long long int>(y)<<32))*
                (1.0/18446744073709551616.0L);
    return G.output.ld;
  }

}

#endif
