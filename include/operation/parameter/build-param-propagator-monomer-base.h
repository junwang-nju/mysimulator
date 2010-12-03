
#ifndef _Build_Parameter_Propagator_Monomer_Base_H_
#define _Build_Parameter_Propagator_Monomer_Base_H_

#include "data/name/parameter-propagator-monomer-base.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void BuildParameterPropagatorMonomerBase(UniqueParameter* P) {
    assert(P[MassData].value<T>()>1e-8);
    copy(P[IvMassData],1./P[MassData].value<T>());
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterPropagatorMonomerBase(Vector<UniqueParameter>& P) {
    assert(P.size>=PropagatorMonomerBaseNumberParameter);
    BuildParameterPropagatorMonomerBase<T>(P.data);
  }

}

#endif

