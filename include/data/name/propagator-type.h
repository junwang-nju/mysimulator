
#ifndef _Propagator_Type_H_
#define _Propagator_Type_H_

namespace std {

  enum PropagatorTypeName {
    VelocityVerlet=0,
    PropagatorNumberType
  };

}

#include "data/name/propagator-vverlet.h"

namespace std {

  static
  const unsigned int
  PropagatorParameterSize[PropagatorNumberType]={
    PropagatorVelocityVerletNumberParameter
  };

}

#endif

