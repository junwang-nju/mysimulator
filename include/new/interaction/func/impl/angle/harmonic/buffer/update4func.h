
#ifndef _Interaction_Func_Implement_Angle_Harmonic_Buffer_Update4Func_H_
#define _Interaction_Func_Implement_Angle_Harmonic_Buffer_Update4Func_H_

#include "interaction/func/impl/angle/common/buffer/update4func.h"
#include "interaction/func/impl/angle/harmonic/buffer/name.h"
#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename T>
  void AngleHarmonicUpdate4Func(const T* dsq,const Unique64Bit* P,T* buffer) {
    AngleCommonUpdate4Func(dsq,P,buffer);
    buffer[AngleValue]=arcCos(buffer[AngleCosine]);
  }

}

#endif

