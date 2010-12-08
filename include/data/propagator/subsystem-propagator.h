
#ifndef _SubSystem_Propagator_H_
#define _SubSystem_Propagator_H_

#include "data/propagator/monomer-propagator.h"

namespace std {

  template <typename T>
  struct subsysPropagator : public Vector<UniqueParameter> {
    typedef subsysPropagator<T> Type;
    typedef Vector<UniqueParameter> ParentType;
    
    Vector<monomerPropagator>   merPg;
  };

}

#endif
