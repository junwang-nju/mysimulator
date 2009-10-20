
#ifndef _Propagator_Operation_H_
#define _Propagator_Operation_H_

#include "var-vector.h"

namespace std {

  template <typename T>
  void PropagatorParamAllocate(varVector<T>& Prm, const uint& NPrm) {
    if(NPrm>0)  Prm.allocate(NPrm);
  }

}

#endif

