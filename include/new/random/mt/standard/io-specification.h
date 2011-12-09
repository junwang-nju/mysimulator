
#ifndef _Random_MT_Standard_InputOutput_Specification_H_
#define _Random_MT_Standard_InputOutput_Specification_H_

#include "random/mt/standard/specification.h"
#include "array/1d/io.h"

namespace mysimulator {

  OutputBase& operator<<(OutputBase& os, const MersenneTwister<StandardMT>& R) {
    assert(IsValid(R));
    os<<R.s<<"\t"<<R.sl;
    return os;
  }

  InputBase& operator>>(InputBase& is, MersenneTwister<StandardMT>& R) {
    is>>R.s>>R.sl;
    return is;
  }

}

#endif

