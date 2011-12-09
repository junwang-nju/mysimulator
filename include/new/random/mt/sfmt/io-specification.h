
#ifndef _Random_MT_SFMT_InputOutput_Specification_H_
#define _Random_MT_SFMT_InputOutput_Specification_H_

#include "random/mt/sfmt/specification.h"

namespace mysimulator {

  template <unsigned int Fac>
  OutputBase& operator<<(OutputBase& os, const MersenneTwister<SFMT,Fac>& R) {
    assert(IsValid(R));
    os<<Fac<<"\t"<<R.s<<"\t"<<R.idx;
    return os;
  }

  template <unsigned int Fac>
  InputBase& operator>>(InputBase& is, MersenneTwister<SFMT,Fac>& R) {
    assert(IsValid(R));
    unsigned int realFac;
    is>>realFac;
    if(realFac!=Fac)  Error("Incompatible Factor for SFMT MersenneTwister!");
    is>>R.s>>R.idx;
    return is;
  }

}

#endif

