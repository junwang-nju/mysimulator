
#ifndef _Random_MT_DSFMT_InputOutput_Specification_H_
#define _Random_MT_DSFMT_InputOutput_Specification_H_

#include "random/mt/dsfmt/specification.h"
#include "array/1d/io.h"
#include "unique/128bit/io.h"

namespace mysimulator {

  template <unsigned int Fac>
  OutputBase& operator<<(OutputBase& os, const MersenneTwister<dSFMT,Fac>& R) {
    assert(IsValid(R));
    os<<Fac<<"\t"<<R.s<<"\t"<<R.idx;
    return os;
  }

  template <unsigned int Fac>
  InputBase& operator>>(InputBase& is, MersenneTwister<dSFMT,Fac>& R) {
    assert(IsValid(R));
    unsigned int realFac;
    is>>realFac;
    if(realFac!=Fac)  Error("Incompatible Factor for dSFMT MersenneTwister!");
    is>>R.s>>R.idx;
    return is;
  }

}

#endif

