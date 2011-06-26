
#ifndef _Propagator_Interaction_H_
#define _Propagator_Interaction_H_

#include "propagator/subsystem/interface.h"
#include "list/interface.h"

namespace mysimulator {

  template <typename T>
  struct Propagator {

    typedef Propagator<T>   Type;

    PropagatorMoveName  MoveMode;
    Vector<UniqueParameter64Bit>  Data;
    Vector<SubsysPropagator<T> >  Sys;
    List<T> X;
    List<T> V;
    List<T> G;
    List<T> Msk;

    Propagator() : MoveMode(UnknownMove), Data(), Sys(), X(), V(), G(), Msk(){}

  };

} 

#endif

