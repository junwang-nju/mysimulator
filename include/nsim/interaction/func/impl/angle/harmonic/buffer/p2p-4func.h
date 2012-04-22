
#ifndef _Interaction_Func_Implement_Angle_Harmonic_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Angle_Harmonic_Buffer_P2P4Func_H_

#include "interaction/func/impl/angle/common/buffer/p2p-4func.h"
#include "interaction/func/impl/angle/harmonic/buffer/post-name.h"
#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename T>
  void AngleHarmonicPre2Post4Func(
      const Array1D<T>& pre,const Array1D<Unique64Bit>& P,Array1D<T>& post,
      bool& flag) {
    AngleCommonPre2Post4Func(pre,P,post,flag);
    post[AngleValue]=arcCos(post[AngleCosine]);
  }

}

#endif

