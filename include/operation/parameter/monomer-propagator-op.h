
#ifndef _Monomer_Propagator_Operation_H_
#define _Monomer_Propagator_Operation_H_

#include "data/name/monomer-propagator-type.h"
#include "data/name/propagator-type.h"
#include "data/name/monomer-type.h"
#include "operation/propagate/monomer-move.h"
#include "operation/parameter/build-param-monomer-propagator.h"

namespace std {

  template <typename T>
  void assignMoveMode(monomerPropagator<T>& P, const unsigned int& mpgtype) {
    switch(mpgtype) {
      case ParticleConstEVVerlet:
        P[MoveMode].u=ConstantE_VelocityVerlet;
        break;
      case ParticleLangevinVVerlet:
        P[MoveMode].u=Langevin_VelocityVerlet;
        break;
      case ParticleBerendsenVVerlet:
        P[MoveMode].u=Berendsen_VelocityVerlet;
        break;
      default:
        myError("unknown monomer propagator type");
    }
  }

  template <typename T>
  void assignMonomerMode(monomerPropagator<T>& P, const unsigned int& mpgtype){
    switch(mpgtype) {
      case ParticleConstEVVerlet:
      case ParticleLangevinVVerlet:
      case ParticleBerendsenVVerlet:
        P[MonomerMode].u=ParticleType;
        break;
      default:
        myError("unknown monomer propagator type");
    }
  }

  template <typename T>
  void assignBuild(monomerPropagator<T>& P, const unsigned int& mpgtype) {
    typedef (*BuildFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    switch(mpgtype) {
      case ParticleConstEVVerlet:
        MP[Build].ptr=
          reinterpret_cast<void*>(
            static_cast<BuildFunc>(BuildParameterMonomerPropagatorPEV));
        break;
      case ParticleBerendsenVVerlet:
        MP[Build].ptr=
          reinterpret_cast<void*>(
            static_cast<BuildFunc>(BuildParameterMonomerPropagatorPBV));
        break;
      case ParticleLangevinVVerlet:
        MP[Build].ptr=
          reinterpret_cast<void*>(
            static_cast<BuildFunc>(BuildParameterMonomerPropagatorPLV));
        break;
      default:
        myError("unknown monomer propagator type");
    }
  }

  template <typename T>
  void assignMove(monomerPropagator<T>& P, const unsigned int& mpgtype) {
    typedef (*MoveFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    switch(mpgtype) {
      case ParticleConstEVVerlet:
        P[EV_MoveBeforeG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(PEVMove_BeforeG));
        P[EV_MoveAfterG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(PEVMove_AfterG));
        break;
      case ParticleLangevinVVerlet:
        P[LV_MoveBeforeG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(PLVMove_BeforeG));
        P[LV_MoveAfterG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(PLVMove_AfterG));
        break;
      case ParticleBerendsenVVerlet:
        P[BV_MovePreProcess].ptr=
          reinterpret_cast<void*>(static_cast<>(PBVMove_PreProcess));
        P[BV_MoveBeforeG].ptr=
          reinterpret_cast<void*>(static_cast<>(PBVMove_BeforeG));
        P[BV_MoveAfterG].ptr=
          reinterpret_cast<void*>(static_cast<>(PBVMove_AfterG));
        P[BV_MovePostProcess].ptr=
          reinterpret_cast<void*>(static_cast<>(PBVMove_PostProcess));
        break;
      default:
        myError("unknown monomer propagator type");
    }
  }

  template <typename T>
  void allocate(monomerPropagator<T>& P, const unsigned int& mpgtype) {
    assert(mpgtype<monomerPropagatorNumberType);
    allocate(static_cast<Vector<UniqueParameter>&>(P),
             monomerPropagatorParameterSize[mpgtype]);
    assignMonomerMode(P,mpgtype);
    assignMoveMode(P,mpgtype);
    assignBuild(P,mpgtype);
    assignMove(P,mpgtype);
  }

}

#endif
