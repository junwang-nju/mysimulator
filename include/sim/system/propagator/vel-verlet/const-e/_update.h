
#ifndef _System_Propagator_VelVerlet_ConstE_Update_Func_H_
#define _System_Propagator_VelVerlet_ConstE_Update_Func_H_

#include "unique/64bit/interface.h"
#include "array/1d/copy.h"
#include "array/1d/inverse.h"
#include "array/1d/scale.h"

#define _VAL(Q)   (*reinterpret_cast<T*>(Q.ptr[0]))
#define _CVAL(Q)  (*reinterpret_cast<const T*>(Q.ptr[0]))

namespace mysimulator {

  template <typename T>
  void _UpdateFuncVelVerletCEHTIM_GMass(
      const T& dt, const Unique64Bit& PMass, Unique64Bit& PNegHTIM) {
    _VAL(PNegHTIM)=-0.5*dt/_CVAL(PMass);
  }

  template <typename T>
  void _UpdateFuncVelVerletCEHTIM_AMass(
      const T& dt, const Unique64Bit& PMass, Unique64Bit& PNegHTIM,
      const Unique64Bit* ID, unsigned int n) {
    T nhdt=-0.5*dt;
    unsigned int u,v;
    for(unsigned int i=0;i<n;++i) {
      u=ID[i].uv[0];
      v=ID[i].uv[1];
      BLASCo
    }
  }

}

#endif

