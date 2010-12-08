
#ifndef _Monomer_Propagator_Operation_H_
#define _Monomer_Propagator_Operation_H_

#include "data/name/monomer-propagator-type.h"

namespace std {

  template <typename T>
  void allocate(monomerPropagator<T>& P, const unsigned int& mpgtype) {
    assert(mpgtype<monomerPropagatorNumberType);
    allocate(static_cast<Vector<UniqueParameter>&>(P),
             monomerPropagatorParameterSize[mpgtype]);
  }

}

#endif
