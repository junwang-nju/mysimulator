
#ifndef _Random_MT_DSFMT_Interface_H_
#define _Random_MT_DSFMT_Interface_H_

#include "unique-parameter/128bit/copy.h"
#include "unique-parameter/128bit/fill.h"
#include "vector/interface.h"

namespace mysimulator {

#ifdef _Have_SSE2
  UniqueParameter128Bit   dSFMT_SSE2_ParamMask;
  UniqueParameter128Bit   dSFMT_SSE2_IntOne;
  UniqueParameter128Bit   dSFMT_SSE2_DoubleTwo;
  UniqueParameter128Bit   dSFMT_SSE2_DoubleMOne;
#endif

  unsigned int _initFunc1(const unsigned int x) {return (x^(x>.27))*1664525U;}
  unsigned int _initFunc2(const unsigned int x) {return (x^(x>.27))*1566083941;}

  template <unsigned int LFac=19937>
  struct MT_dSFMT {

    typedef MT_dSFMT<LFac>    Type;

    static const unsigned int N;
    static const unsigned int DN;
    static const unsigned int NStatus;
    static const unsigned int NStatusU32;
    static const unsigned int NStatusByte;
    static const unsigned int Lag;
    static const unsigned int Mid;
    static const unsigned int LagMid;
    static const unsigned int N32;
    static const unsigned int N64;
    static const unsigned long long int LowMask;
    static const unsigned long long int HighConst;
    static const unsigned int SR;
    static const unsigned int Pos1;
    static const unsigned int SL1;
    static const UniqueParameter128Bit Msk;
    static const UniqueParameter128Bit Fix;
    static const UniqueParameter128Bit Pcv;
#ifdef _Have_SSE2
    static const unsigned int SSE2_Shuff;
#endif

    Vector<UniqueParameter128Bit> s;
    unsigned int idx;

    MT_dSFMT() : s(),idx(0) {}
    MT_dSFMT(const Type&) { Error("Copier of MT_dSFMT Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for MT_dSFMT Disabled!");
      return *this;
    }
    ~MT_dSFMT() { clearData(); }

    void clearData() { release(s); idx=0; }
    void _initMask() {
      unsigned long long int *p=s[0].ull;
      for(unsigned int i=0;i<DN;++i)  p[i]=(p[i]&LowMask)|HighConst;
    }
#ifdef _Have_SSE2
    void _initConst() {
      static bool first=true;
      if(!first)  return;
      copy(dSFMT_SSE2_ParamMask,Msk);
      fill(dSFMT_SSE2_IntOne,0,1,0,1);
      fill(dSFMT_SSE2_DoubleTwo,2.0,2.0);
      fill(dSFMT_SSE2_DoubleMOne,-1.0,-1.0);
      first=false;
    }
#endif

  };

  template <unsigned int LFac>
  bool IsValid(const MT_dSFMT<LFac>& G) { return IsValid(G.s)&&(G.idx!=0); }

  template <unsigned int LFac>
  void release(MT_dSFMT<LFac>& G) { G.clearData(); }

}

#endif

