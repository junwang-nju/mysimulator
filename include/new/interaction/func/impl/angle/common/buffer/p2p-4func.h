
#ifndef _Interaction_Func_Implement_Angle_Common_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Angle_Common_Buffer_P2P4Func_H_

#include "interaction/func/impl/angle/common/buffer/post-name.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "unique/64bit/interface.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void AngleCommonPre2Post4Func(const T* pre, const Unique64Bit*,T* post,
                                bool& flag) {
    post[AngleCosine]=pre[AngleDotAB]
                     /sqroot(pre[AngleEdgeASQ]*pre[AngleEdgeBSQ]);
    flag=true;
  }

}

#endif

