
#ifndef _Propagator_Monomer_Allocate_H_
#define _Propagator_Monomer_Allocate_H_

#include "propagator/monomer/interface.h"
#include "vector/allocate.h"
#include "propagator/monomer/parameter/vverlet/conste/particle/update.h"
#include "propagator/move/vverlet/conste/particle/name.h"
#include "propagator/move/vverlet/conste/particle/monomer.h"

namespace mysimulator {

  template <typename T>
  void allocate(MonomerPropagator<T>& P, const PropagatorMoveName& Mv,
                const PropagatorEnsembleName& Es,
                const PropagatorMonomerName& Mn) {
    release(P);
    P.MoveMode=Mv;
    P.EnsembleMode=Es;
    P.MonomerMode=Mn;
    switch(Mv) {
      case VelocityVerlet:
        switch(Es) {
          case ConstantE:
            switch(Mn) {
              case ParticleType:
                allocate(
                    P.Data,
                    MonomerPropagatorNumberParameterParticleConstEVelVerlet);
                allocate(
                    P.Move,
                    PropagatorNumberMoveVelocityVerletConstantEParticle);
                P.Move[BeforeG]=PEVMove_BeforeG<T>;
                P.Move[AfterG]=PEVMove_AfterG<T>;
                P.Update=UpdateMonomerPropagatorParticleConstEVelVerlet<T>;
                break;
              default:
                Error("Unknown Monomer Type!");
            }
            break;
          case BerendsenThermo:
          case LangevinThermo:
          default:
            Error("Unknown Ensemble Type!");
        }
        break;
      default:
        Error("Unknown Move Type!");
    }
  }

  template <typename T>
  void imprint(MonomerPropagator<T>& P, const MonomerPropagator<T>& cP) {
    allocate(P,cP.MoveMode,cP.EnsembleMode,cP.MonomerMode);
  }

}

#endif

