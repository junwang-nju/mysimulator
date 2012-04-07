
#ifndef _Interaction_Func_Implement_Angle_Common_Buffer_Update4Func_H_
#define _Interaction_Func_Implement_Angle_Common_Buffer_Update4Func_H_

#include "interaction/func/impl/angle/common/buffer/name.h"
#include "unique/64bit/interface.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void AngleCommonUpdate4Func(const T* dsq, const Unique64Bit*,T* buffer) {
    buffer[AngleCosine]=dsq[2]/sqroot(dsq[0]*dsq[1]);
  }

}

#endif

