
#ifndef _Build_Parameter_Monomer_Propagator_Base_H_
#define _Build_Parameter_Monomer_Propagator_Base_H_

#include "data/name/monomer-propagator-base.h"
#include "data/propagator/monomer-propagator.h"

namespace std {

  template <typename T>
  void BuildParameterPropagatorMonomerBase(monomerPropagator<T>& MP) {
    assert(MP[MassData].value<T>()>1e-8);
    copy(MP[IvMassData],1./MP[MassData].value<T>());
  }

}

#endif

