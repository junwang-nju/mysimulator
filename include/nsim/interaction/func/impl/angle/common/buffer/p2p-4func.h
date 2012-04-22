
#ifndef _Interaction_Func_Implement_Angle_Common_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Angle_Common_Buffer_P2P4Func_H_

#include "interaction/func/impl/angle/common/buffer/post-name.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "unique/64bit/interface.h"
#include "intrinsic-type/square-root.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void AngleCommonPre2Post4Func(
      const Array1D<T>& pre,const Array1D<Unique64Bit>&,Array1D<T>& post,
      bool& flag) {
    post[AngleCosine]=pre[AngleDotAB]
                     /sqroot(pre[AngleEdgeASQ]*pre[AngleEdgeBSQ]);
    flag=true;
  }

}

#endif

