
#ifndef _Monomer_Propagator_Operation_H_
#define _Monomer_Propagator_Operation_H_

#include "data/name/monomer-propagator-type.h"
#include "data/name/propagator-type.h"
#include "data/name/monomer-type.h"
#include "data/name/ensemble-type.h"
#include "operation/propagate/monomer-move.h"
#include "operation/parameter/build-param-monomer-propagator.h"

namespace std {

  template <typename T>
  void assignMoveMode(monomerPropagator<T>& P, const unsigned int& mpgtype) {
    switch(mpgtype) {
      case ParticleConstEVVerlet:
      case ParticleLangevinVVerlet:
      case ParticleBerendsenVVerlet:
        P[MonomerMoveMode].u=VelocityVerlet;
        break;
      default:
        Error("unknown monomer propagator type");
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
        Error("unknown monomer propagator type");
    }
  }

  template <typename T>
  void assignEnsembleMode(monomerPropagator<T>& P,const unsigned int& mpgtype){
    switch(mpgtype) {
      case ParticleConstEVVerlet:
        P[MonomerEnsembleMode].u=ConstantE;
        break;
      case ParticleLangevinVVerlet:
        P[MonomerEnsembleMode].u=Langevin;
        break;
      case ParticleBerendsenVVerlet:
        P[MonomerEnsembleMode].u=Berendsen;
        break;
      default:
        Error("unknown monomer propagator type");
    }
  }

  template <typename T>
  void assignBuild(monomerPropagator<T>& MP, const unsigned int& mpgtype) {
    typedef
    void (*BuildFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    switch(mpgtype) {
      case ParticleConstEVVerlet:
        MP[monomerPgBuild].ptr=
          reinterpret_cast<void*>(
            static_cast<BuildFunc>(BuildParameterMonomerPropagatorPEV));
        break;
      case ParticleBerendsenVVerlet:
        MP[monomerPgBuild].ptr=
          reinterpret_cast<void*>(
            static_cast<BuildFunc>(BuildParameterMonomerPropagatorPBV));
        break;
      case ParticleLangevinVVerlet:
        MP[monomerPgBuild].ptr=
          reinterpret_cast<void*>(
            static_cast<BuildFunc>(BuildParameterMonomerPropagatorPLV));
        break;
      default:
        Error("unknown monomer propagator type");
    }
  }

  template <typename T>
  void assignMove(monomerPropagator<T>& P, const unsigned int& mpgtype) {
    typedef
    void (*MoveFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
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
          reinterpret_cast<void*>(static_cast<MoveFunc>(PBVMove_PreProcess));
        P[BV_MoveBeforeG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(PBVMove_BeforeG));
        P[BV_MoveAfterG].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(PBVMove_AfterG));
        P[BV_MovePostProcess].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(PBVMove_PostProcess));
        break;
      default:
        Error("unknown monomer propagator type");
    }
  }

  template <typename T>
  void allocate(monomerPropagator<T>& P, const unsigned int& mpgtype) {
    assert(mpgtype<monomerPropagatorNumberType);
    allocate(static_cast<Vector<UniqueParameter>&>(P),
             monomerPropagatorParameterSize[mpgtype]);
    assignMonomerMode(P,mpgtype);
    assignMoveMode(P,mpgtype);
    assignEnsembleMode(P,mpgtype);
    assignBuild(P,mpgtype);
    assignMove(P,mpgtype);
  }

}

#endif
