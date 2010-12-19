
#ifndef _Subsystem_Propagator_Langevin_VerlocityVerlet_Move_H_
#define _Subsystem_Propagator_Langevin_VerlocityVerlet_Move_H_

#include "data/basic/unique-parameter.h"
#include "data/name/monomer-propagator-langevin-vverlet.h"

namespace std {

  template <typename T>
  void LVMove_BeforeG(subsysPropagator<T>& SP) {
    typedef
    void (*mMoveFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    for(unsigned int i=0;i<SP.merPg.size;++i)
      reinterpret_cast<mMoveFunc>(SP.merPg[i][LV_MoveBeforeG].ptr)(
          SP.merPg[i],static_cast<Vector<UniqueParameter>&>(SP));
  }

  template <typename T>
  void LVMove_AfterG(subsysPropagator<T>& SP) {
    typedef
    void (*mMoveFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    for(unsigned int i=0;i<SP.merPg.size;++i) {
      scale(*reinterpret_cast<Vector<T>*>(SP.merPg[i][GVector].ptr),
            *reinterpret_cast<Vector<T>*>(SP.merPg[i][MskVector].ptr));
      reinterpret_cast<mMoveFunc>(SP.merPg[i][LV_MoveBeforeG].ptr)(
          SP.merPg[i],static_cast<Vector<UniqueParameter>&>(SP));
    }
  }

}

#endif

