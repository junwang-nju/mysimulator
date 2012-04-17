
#ifndef _Interaction_Func_Implement_Angle_Common_Buffer_GetPre4Func_H_
#define _Interaction_Func_Implement_Angle_Common_Buffer_GetPre4Func_H_

#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/buffer/interface.h"

namespace mysimulator {

  template <typename T>
  void AngleCommonGetPre4Func(InteractionBuffer<T>* Buf,const int* inf,T* pre) {
    assert((inf[0]<0)&&(inf[1]<0));
    pre[AngleEdgeASQ]=(Buf+inf[0])->pre[PairwiseDistanceSQ];
    pre[AngleEdgeBSQ]=(Buf+inf[1])->pre[PairwiseDistanceSQ];
  }

}

#endif


