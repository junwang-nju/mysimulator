
#ifndef _Interaction_Func_Implement_Angle_Common_Buffer_GetPre4Func_H_
#define _Interaction_Func_Implement_Angle_Common_Buffer_GetPre4Func_H_

#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/func/impl/angle/common/buffer/inf-name.h"
#include "interaction/buffer/interface.h"

namespace mysimulator {

  template <typename T>
  void AngleCommonGetPre4Func(InteractionBuffer<T>* Buf) {
    assert(IsValid(Buf->inf));
    assert(Buf->inf[AngleEdgeAInf]!=NULL);
    Buf->pre[AngleEdgeASQ]=Buf->inf[AngleEdgeASQ]->pre[PairwiseDistanceSQ];
    assert(Buf->inf[AngleEdgeBInf]!=NULL);
    Buf->pre[AngleEdgeBSQ]=Buf->inf[AngleEdgeBSQ]->pre[PairwiseDistanceSQ];
  }

}

#endif


