
#ifndef _Random_MT_DSFMT_Interface_H_
#define _Random_MT_DSFMT_Interface_H_

#include "random/mt/interface.h"
#include "random/base/interface.h"
#include "random/mt/dsfmt/module/convert.h"

namespace mysimulator {

  template <unsigned int Fac>
  struct MersenneTwister<dSFMT,Fac> : public RandomBase {

    public:

      typedef MersenneTwister<dSFMT,Fac>    Type;
      typedef RandomBase  ParentType;

      static const unsigned int N;
      static const unsigned int DualN;
      static const unsigned int NStatus;
      static const unsigned int NStatusU32;
      static const unsigned int NStatusU32m1;
      static const unsigned int NStatusByte;
      static const unsigned int Lag;
      static const unsigned int Mid;
      static const unsigned int LagMid;
      static const unsigned int N64;
      static const unsigned long long Low;
      static const unsigned long long Upp;
      static const unsigned int SR;
      static const unsigned int Pos;
      static const unsigned int SL;
      static const Unique128Bit Msk;
      static const Unique128Bit Fix;
      static const Unique128Bit Pcv;
#ifdef _HAVE_SSE2
      static const unsigned int SSE2Shuffle;
#endif

      Array1D<Unique128Bit> s;
      unsigned int idx;

    private:

      MersenneTwister(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

