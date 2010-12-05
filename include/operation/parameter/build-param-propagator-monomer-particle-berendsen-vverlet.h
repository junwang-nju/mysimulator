
#ifndef _Build_Parameter_Propagator_Monomer_Particle_Berendsen_VelVerlet_H_
#define _Build_Parameter_Propagator_Monomer_Particle_Berendsen_VelVerlet_H_

#include "data/name/propagator-type.h"
#include "data/name/monomer-type.h"
#include "operation/propagate/monomer-PBV-move.h"
#include "operation/parameter/build-param-propagator-monomer-base.h"

namespace std {

  template <typename T>
  void BuildParameterPropagatorMonomerPBV(
      UniqueParameter* P, const UniqueParameter* GP) {
    BuildParameterPropagatorMonomerBase<T>(P);
    copy(P[PBV_HalfDeltaTIvM],
         GP[HalfDeltaTime].value<T>()*P[IvMassData].value<T>());
  }

  template <typename T>
  void BuildParameterPropagatorMonomerPBV(
      Vector<UniqueParameter>& P, const Vector<UniqueParameter>& GP) {
    assert(P.size>=PropagatorMonomerPBVNumberParameter);
    BuildParameterPropagatorMonomerPBV<T>(P.data,GP.data);
  }

  template <typename T>
  void allocatePropagatorMonomerPBVParameter(Vector<UniqueParameter>& P) {
    allocate(P,PropagatorMonomerPBVNumberParameter);
    P[MoveMode].u=Berendsen_VelocityVerlet;
    P[MonomerMode].u=ParticleType;
    typedef
    void (*BuildFunc)(UniqueParameter*,const UniqueParameter*);
    P[pBuild].ptr=
      reinterpret_cast<void*>(
          static_cast<BuildFunc>(BuildParameterPropagatorMonomerPBV<T>));
    typedef
    void (*MoveFunc)(
        Vector<T>&,Vector<T>&,const Vector<T>&,const Vector<T>&,
        const Vector<UniqueParameter>&, const Vector<UniqueParameter>&);
    P[BV_MovePreProcess].ptr=
      reinterpret_cast<void*>(static_cast<MoveFunc>(PBVMove_PreProcess<T>));
    P[BV_MoveBeforeG].ptr=
      reinterpret_cast<void*>(static_cast<MoveFunc>(PBVMove_BeforeG<T>));
    P[BV_MoveAfterG].ptr=
      reinterpret_cast<void*>(static_cast<MoveFunc>(PBVMove_AfterG<T>));
    P[BV_MovePostProcess].ptr=
      reinterpret_cast<void*>(static_cast<MoveFunc>(PBVMove_PostProcess<T>));
  }

}

#endif

