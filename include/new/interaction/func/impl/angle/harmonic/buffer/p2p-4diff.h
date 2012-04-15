
#ifndef _Interaction_Func_Implement_Angle_Harmonic_Buffer_P2P4Diff_H_
#define _Interaction_Func_Implement_Angle_Harmonic_Buffer_P2P4Diff_H_

#include "interaction/func/impl/angle/common/buffer/p2p-4diff.h"
#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "interaction/func/impl/angle/harmonic/buffer/post-name.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename T>
  void AngleHarmonicPre2Post4Diff(const T* pre,const Unique64Bit* P,T* post,
                                  bool& flag) {
    AngleCommonPre2Post4Diff(pre,P,post,flag);
    post[AngleValue]=arcCos(post[AngleCosine]);
  }

}

#endif

