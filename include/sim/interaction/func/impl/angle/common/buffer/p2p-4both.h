
#ifndef _Interaction_Func_Implement_Angle_Common_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Angle_Common_Buffer_P2P4Both_H_

#include "interaction/func/impl/angle/common/buffer/p2p-4diff.h"

namespace mysimulator {

  template <typename T>
  void AngleCommonPre2Post4Both(const T* pre,const Unique64Bit* P,T* post,
                                bool& flag) {
    AngleCommonPre2Post4Diff(pre,P,post,flag);
  }

}

#endif

