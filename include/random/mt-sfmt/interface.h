
#ifndef _Random_MT_SFMT_Interface_H_
#define _Random_MT_SFMT_Interface_H_

#include "random/base/interface.h"
#include "unique-parameter/128bit/interface.h"

namespace mysimulator {

  template <unsigned int LFac=19937>
  struct MT_SFMT : public RandomBase {

    typedef MT_SFMT   Type;
    typedef RandomBase  ParentType;

    static const unsigned int N=LFac/128+1;
    static const unsigned int NStatus=N;
    static const unsigned int NStatusByte=N*16;
    static const unsigned int N32=N*4;
    static const unsigned int N64=N*2;
    static const unsigned int Lag=(N32>=623?11:(N32>=68?7:(N32>=39?5:3)));
    static const unsigned int Mid=(N-Lag)/2;
    static const unsigned int LagMid=Lag+Mid;
    static const unsigned int Pos1;
    static const unsigned int SL1;
    static const unsigned int SL2;
    static const unsigned int SR1;
    static const unsigned int SR2;
    static const UniqueParameter128Bit Msk;
    static const UniqueParameter128Bit Parity;

    Vector<UniqueParameter128Bit> s;
    unsigned int idx;

    MT_SFMT() : s(), idx(0) {}
    MT_SFMT(const Type&) { Error("Copier of MT_SFMT Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for MT_SFMT Disabled!");
      return *this;
    }
    ~MT_SFMT() {} { clearData(); }

    void clearData() { release(s); idx=0; }

  };

  template <unsigned int LFac>
  bool IsValid(const MT_SFMT& G) { return IsValid(G.s)&&(G.idx!=0); }

  template <unsigned int LFac>
  void release(MT_SFMT& G) { G.clearData(); }

}

#endif

