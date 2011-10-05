
#ifndef _Random_MT_Standard_Specification_H_
#define _Random_MT_Standard_Specification_H_

#include "random/base/interface.h"
#include "random/mt/interface.h"
#include "array/1d/fill.h"

namespace mysimulator {

  template <>
  struct MersenneTwister<StandardMT> : public RandomBase {

    public:

      typedef MersenneTwister<StandardMT> Type;
      typedef RandomBase  ParentType;

      static const unsigned int N;
      static const unsigned int M;
      static const unsigned int dNM;
      static const unsigned int NmOne;
      static const unsigned int MmOne;
      static const unsigned int MatrixA;
      static const unsigned int Upp;
      static const unsigned int Low;
      static const unsigned int Mag[2];
      static const unsigned int Mask32Bit;

      Array1D<unsigned int> s;
      unsigned int sl;

      MersenneTwister() : s(), sl(0) {}
      ~MersenneTwister() { clearData(); }

      void clearData() { release(s); sl=0; }
      bool isvalid() const { return IsValid(s); }

      virtual void init(const unsigned int& seed) {
        mysimulator::fill(s,0U);
        s[0]=seed&Mask32Bit;
        unsigned int r=s[0];
        for(sl=1;sl<N;++sl) {
          r=1812433253UL*(r^(r>>30))+sl;
          r&=Mask32Bit;
          s[sl]=r;
        }
        sl=1;
      }

      void init(const unsigned int* key, const unsigned int& nkey,
                const unsigned int& off=uZero, const int& step=iOne) {
        assert(IsValid(key));
      }

    private:

      MersenneTwister(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  const unsigned int MersenneTwister<StandardMT>::N=624;
  const unsigned int MersenneTwister<StandardMT>::M=397;
  const unsigned int MersenneTwister<StandardMT>::dNM=
    MersenneTwister<StandardMT>::N-MersenneTwister<StandardMT>::M;
  const unsigned int MersenneTwister<StandardMT>::NmOne=
    MersenneTwister<StandardMT>::N-1;
  const unsigned int MersenneTwister<StandardMT>::MmOne=
    MersenneTwister<StandardMT>::M-1;
  const unsigned int MersenneTwister<StandardMT>::MatrixA=0x9908B0DFUL;
  const unsigned int MersenneTwister<StandardMT>::Upp=0x80000000UL;
  const unsigned int MersenneTwister<StandardMT>::Low=0x7FFFFFFFUL;
  const unsigned int MersenneTwister<StandardMT>::Mag[2]=
      {0x0UL,MersenneTwister<StandardMT>::MatrixA};
  const unsigned int MersenneTwister<StandardMT>::Mask32Bit=0xFFFFFFFFUL;

}

#endif

