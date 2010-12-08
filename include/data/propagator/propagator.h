
#ifndef _Propagator_H_
#define _Propagator_H_

#include "data/propagator/subsystem-propagator.h"

namespace std {

  template <typename T>
  struct Propagator : public Vector<UniqueParameter> {
    typedef Propagator<T> Type;
    typedef Vector<UniqueParameter>   ParentType;
    
    Vector<subsysPropagator<T> >  SysPg;
  };

}

#endif
