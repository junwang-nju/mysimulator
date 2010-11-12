
#ifndef _Random_Generator_MT_Standard_H_
#define _Random_Generator_MT_Standard_H_

#include "vector.h"

namespace std {

  struct MT_Standard : public Vector<unsigned int> {
    static const int N;
    static const int M;
    static const int dNM;
    static const int NmOne;
    static const int MmOne;
    static const unsigned int MatrixA;
    static const unsigned int UppMask;
    static const unsigned int LowMask;
    static const unsigned int Mag01[2];
    static const unsigned int Mask32b;

    typedef MT_Standard   Type;
    typedef Vector<unsigned int>  ParentType;

    unsigned int *mti;
    UniqueParameter128b output;

    MT_Standard() : ParentType(), mti(NULL), output() {}
    MT_Standard(const Type& G) { myError("Cannot create MT-Standard Generator"); }
    Type& operator=(const Type& G) {
      myError("Cannot copy MT-Standard Generator");
      return *this;
    }
    ~MT_Standard() { release(*this); }
  };

  const int MT_Standard::N=624;
  const int MT_Standard::M=397;
  const int MT_Standard::dNM=MT_Standard::N-MT_Standard::M;
  const int MT_Standard::NmOne=MT_Standard::N-1;
  const int MT_Standard::MmOne=MT_Standard::M-1;
  const unsigned int MT_Standard::MatrixA=0x9908B0DFUL;
  const unsigned int MT_Standard::UppMask=0x80000000UL;
  const unsigned int MT_Standard::LowMask=0x7FFFFFFFUL;
  const unsigned int MT_Standard::Mag01[2]={0x0UL,MT_Standard::MatrixA};
  const unsigned int MT_Standard::Mask32b=0xFFFFFFFFUL;

  bool IsAvailable(const MT_Standard& G) {
    return IsAvailable(static_cast<const Vector<unsigned int>&>(G));
  }
  bool IsRandomGenerator(const MT_Standard& G) { return true; }
  void copy(MT_Standard& G, const MT_Standard& cG) {
    assert(IsAvailable(G));
    assert(IsAvailable(cG));
    copy(static_cast<Vector<unsigned int>&>)(G),
         static_cast<const Vector<unsigned int>&>(cG));
    copy(*(G.mti),*(cG.mti));
    copy(G.output,cG.output);
  }
  void release(MT_Standard& G) {
    release(static_cast<Vector<unsigned int>&>(G));
    safe_delete(G.mti);
    copy(G.output,0);
  }
  void init(MT_Standard& G, const unsigned int seed) {
    assert(IsAvailable(G));
    unsigned int &idx=*(G.mti);
    unsigned int rmt;
    G[0]=seed&MT_Standard::Mask32b;
    rmt=G[0];
    for(ri=1;ri<MT_Standard::N;++ri) {
      rmt=1812433253UL*(rmt^(rmt>>30))+ri;
      rmt&=MT_Standard:Mask32b;
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
    i=1;  j=0;  g=0ff;
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
  void allocate(MT_Standard& G) {
    allocate(static_cast<Vector<unsigned int>&>(G),G.N);
    G.mti=new unsigned int;
    init(G,5489UL);
  }
  void refer(MT_Standard& G, const MT_Standard& rG) {
    refer(static_cast<Vector<unsigned int>&>(G),
          static_cast<const Vector<unsigned int>&>(rG));
    G.mti=rG.mti;
  }

}

#endif
