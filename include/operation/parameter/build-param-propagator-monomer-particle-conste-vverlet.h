
#ifndef _Build_Parameter_Propagator_Monomer_Particle_ConstantE_VelVerlet_H_
#define _Build_Parameter_Propagator_Monomer_Particle_ConstantE_VelVerlet_H_

#include "data/name/parameter-propagator-monomer-particle-conste-vverlet.h"
#include "data/basic/UniqueParameter.h"
#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void allocatePropagatorMonomerPEVParameter(Vector<UniqueParameter>& P) {
    allocate(P,PropagatorMonomerPEVNumberParameter);
    P[pBuild].ptr=
      reinterpret_cast<void*>(BuildParameterPropagatorMonomerPEV<T>);
  }

  template <typename T>
  void BuildParameterPropagatorMonomerPEV(
      UniqueParameter* P, const UniqueParameter* GP) {
    copy(P[PEV_HalfDeltaTIvM],
         GP[HalfDeltaTime].value<T>()*P[IvMassData].value<T>());
  }

  template <typename T>
  void BuildParameterPropagatorMonomerPEV(
      Vector<UniqueParameter>& P, const Vector<UniqueParameter>& GP) {
    assert(P.size>=PropagatorMonomerPEVNumberParameter);
    BuildParameterPropagatorMonomerPEV<T>(P.data,GP.data);
  }

}

#endif
