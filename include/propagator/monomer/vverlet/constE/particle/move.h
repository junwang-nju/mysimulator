
#ifndef _Propagator_Monomer_Move_VelocityVerlet_ConstantE_Particle_H_
#define _Propagator_Monomer_Move_VelocityVerlet_ConstantE_Particle_H_

#include "propagator/monomer/vverlet/constE/particle/param-name.h"
#include "unique-parameter/64bit/interface.h"
#include "vector/shift.h"

namespace mysimulator {

  template <typename T>
  void PEVMove_BeforeG(Vector<UniqueParameter64Bit>& MP,
                       const Vector<UniqueParameter64Bit>& SP) {
    Vector<T> *X=MP[XData].pointer<Vector<T> >();
    Vector<T> *V=MP[VData].pointer<Vector<T> >();
    Vector<T> *G=MP[GData].pointer<Vector<T> >();
    shift(*V,-MP[PEVHalfTimeStepIvM].value<T>(),*G);
    shift(*X,SP[TimeStep].value<T>(),*V);
  }

  template <typename T>
  void PEVMove_AfterG(Vector<UniqueParameter64Bit>& MP,
                      const Vector<UniqueParameter64Bit>& SP) {
    Vector<T> *V=MP[VData].pointer<Vector<T> >();
    Vector<T> *G=MP[GData].pointer<Vector<T> >();
    shift(*V,-MP[PEVHalfTimeStepIvM].value<T>(),*G);
  }

}

#endif

