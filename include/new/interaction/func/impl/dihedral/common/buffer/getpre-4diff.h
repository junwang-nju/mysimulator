
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Diff_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Diff_H_

#include "interaction/func/impl/dihedral/common/buffer/getpre-4func.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonGetPre4Diff(InteractionBuffer<T>* Buf) {
    assert(IsValid(Buf->inf));
    DihedralCommonGetPre4Func(Buf);
    InteractionBuffer<T>* rBuf;
    rBuf=Buf->inf[DihedralAxisInf];
    assert(rBuf!=NULL);
    Buf->pre[DihedralAxisSQ]=rBuf->pre[PairwiseDistanceSQ];
    rBuf=Buf->inf[DihedralDotABInf];
    assert(rBuf!=NULL);
    Buf->pre[DihedralDotBondAB]=-(rBuf->pre[AngleDotAB]);
    rBuf=Buf->inf[DihedralDotBCInf];
    assert(rBuf!=NULL);
    Buf->pre[DihedralDotBondBC]=-(rBuf->pre[AngleDotAB]);
  }

}

#endif

