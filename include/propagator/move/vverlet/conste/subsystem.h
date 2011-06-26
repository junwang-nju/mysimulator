
#ifndef _Propagator_Subsystem_Move_ConstantE_VelocityVerlet_H_
#define _Propagator_Subsystem_Move_ConstantE_VelocityVerlet_H_

#include "propagator/move/vverlet/conste/name.h"
#include "propagator/subsystem/interface.h"
#include "propagator/monomer/parameter/common/name.h"
#include "vector/scale.h"

namespace mysimulator {

  template <typename T>
  void EVMove_BeforeG(SubsysPropagator<T>& SP) {
    for(unsigned int i=0;i<SP.Mer.size;++i)
      SP.Mer[i].Move[BeforeG](SP.Mer[i].Data,SP.Data);
  }

  template <typename T>
  void EVMove_AfterG(SubsysPropagator<T>& SP) {
    for(unsigned int i=0;i<SP.Mer.size;++i) {
      //scale(*(SP.Mer[i].Data[GData].pointer<Vector<T> >()),
      //      *(SP.Mer[i].Data[MskData].pointer<Vector<T> >()));
      SP.Mer[i].Move[AfterG](SP.Mer[i].Data,SP.Data);
    }
  }

}

#endif

