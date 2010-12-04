
#ifndef _Build_Parameter_Propagator_Monomer_Particle_ConstantE_VelVerlet_H_
#define _Build_Parameter_Propagator_Monomer_Particle_ConstantE_VelVerlet_H_

#include "data/name/propagator-type.h"
#include "data/name/monomer-type.h"
#include "operation/propagate/monomer-PEV-move.h"
#include "operation/parameter/build-param-propagator-monomer-base.h"

namespace std {

  template <typename T>
  void BuildParameterPropagatorMonomerPEV(
      UniqueParameter* P, const UniqueParameter* GP) {
    BuildParameterPropagatorMonomerBase<T>(P);
    copy(P[PEV_HalfDeltaTIvM],
         GP[HalfDeltaTime].value<T>()*P[IvMassData].value<T>());
  }

  template <typename T>
  void BuildParameterPropagatorMonomerPEV(
      Vector<UniqueParameter>& P, const Vector<UniqueParameter>& GP) {
    assert(P.size>=PropagatorMonomerPEVNumberParameter);
    BuildParameterPropagatorMonomerPEV<T>(P.data,GP.data);
  }

  template <typename T>
  void allocatePropagatorMonomerPEVParameter(Vector<UniqueParameter>& P) {
    allocate(P,PropagatorMonomerPEVNumberParameter);
    P[MoveMode].u=ConstantE_VelocityVerlet;
    P[MonomerMode].u=ParticleType;
    typedef
    void (*BuildFunc)(UniqueParameter*,const UniqueParameter*);
    P[pBuild].ptr=
      reinterpret_cast<void*>(
      static_cast<BuildFunc>(BuildParameterPropagatorMonomerPEV<T>));
    typedef
    void (*MoveFunc)(Vector<T>&,Vector<T>&,const Vector<T>&,const Vector<T>&,
                     const Vector<UniqueParameter>&,
                     const Vector<UniqueParameter>&);
    P[EV_MoveBeforeG].ptr=
      reinterpret_cast<void*>(static_cast<MoveFunc>(PEVMove_BeforeG<T>));
    P[EV_MoveAfterG].ptr=
      reinterpret_cast<void*>(static_cast<MoveFunc>(PEVMove_AfterG<T>));
  }

}

#endif
