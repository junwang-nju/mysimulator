
#ifndef _Subsystem_Propagator_ConstantE_VelocityVerlet_Move_H_
#define _Subsystem_Propagator_ConstantE_VelocityVerlet_Move_H_

#include "data/basic/unique-parameter.h"
#include "data/name/monomer-propagator-conste-vverlet.h"

namespace std {

  template <typename T>
  void EVMove_BeforeG(subsysPropagator<T>& SP) {
    typedef
    void (*mMoveFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    for(unsigned int i=0;i<SP.merPg.size;++i)
      reinterpret_cast<mMoveFunc>(SP.merPg[i][EV_MoveBeforeG].ptr)(
          SP.merPg[i],static_cast<const Vector<UniqueParameter>&>(SP));
  }

  template <typename T>
  void EVMove_AfterG(subsysPropagator<T>& SP) {
    typedef
    void (*mMoveFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    for(unsigned int i=0;i<SP.merPg.size;++i) {
      scale(*reinterpret_cast<Vector<T>*>(SP.merPg[i][GVector].ptr),
            *reinterpret_cast<Vector<T>*>(SP.merPg[i][MskVector].ptr));
      reinterpret_cast<mMoveFunc>(SP.merPg[i][EV_MoveAfterG].ptr)(
          SP.merPg[i],static_cast<const Vector<UniqueParameter>&>(SP));
    }
  }

}

#endif

