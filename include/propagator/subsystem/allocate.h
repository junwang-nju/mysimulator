
#ifndef _Propagator_Subsystem_Allocate_H_
#define _Propagator_Subsystem_Allocate_H_

#include "propagator/subsystem/interface.h"
#include "propagator/move/vverlet/conste/name.h"
#include "propagator/move/vverlet/conste/subsystem.h"
#include "propagator/subsystem/parameter/vverlet/conste/update.h"

namespace mysimulator {

  template <typename T>
  void allocate(SubsysPropagator<T>& SP, const PropagatorMoveName& Mv,
                const PropagatorEnsembleName& Es,
                const Vector<PropagatorMonomerName>& Mn) {
    release(SP);
    SP.MoveMode=Mv;
    SP.EnsembleMode=Es;
    switch(Mv) {
      case VelocityVerlet:
        switch(Es) {
          case ConstantE:
            allocate(SP.Data,SubsysPropagatorNumberParameterConstEVelVerlet);
            allocate(SP.Move,PropagatorNumberMoveVelocityVerletConstantE);
            SP.Move[BeforeG]=EVMove_BeforeG<T>;
            SP.Move[AfterG]=EVMove_AfterG<T>;
            SP.Update=UpdateSubsysPropagatorConstEVelVerlet<T>;
            allocate(SP.Mer,Mn.size);
            for(unsigned int i=0;i<Mn.size;++i)
              allocate(SP.Mer[i],Mv,Es,Mn[i]);
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

}

#endif

