
#ifndef _Interaction_Func_Implement_Angle_Harmonic_Buffer_Update4Diff_H_
#define _Interaction_Func_Implement_Angle_Harmonic_Buffer_Update4Diff_H_

#include "interaction/func/impl/angle/harmonic/buffer/update4func.h"

namespace mysimulator {

  template <typename T>
  void AngleHarmonicUpdate4Diff(const T* dsq,const Unique64Bit* P,T* buffer) {
    AngleHarmonicUpdate4Func(dsq,P,buffer);
  }

}

#endif

