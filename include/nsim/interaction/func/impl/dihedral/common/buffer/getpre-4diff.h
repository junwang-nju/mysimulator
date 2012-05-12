
#ifndef _Interaction_Func_Impl_Dihedral_Common_Buffer_GetPre4Diff_H_
#define _Interaction_Func_Impl_Dihedral_Common_Buffer_GetPre4Diff_H_

#include "interaction/func/impl/dihedral/common/buffer/getpre-4func.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonGetPre4Diff(InteractionBuffer<T>& Buf) {
    assert(Buf.inf.IsValid());
    DihedralCommonGetPre4Func(Buf);
    InteractionBuffer<T>* RBuf;
    RBuf=Buf.inf[DihedralAxisInf];
    assert(RBuf!=NULL);
    Buf.pre[DihedralAxisSQ]=RBuf->pre[PairwiseDistanceSQ];
    RBuf=Buf.inf[DihedralDotABInf];
    assert(RBuf!=NULL);
    Buf.pre[DihedralDotBondAB]=-(RBuf->pre[AngleDotAB]);
    RBuf=Buf.inf[DihedralDotBCInf];
    assert(RBuf!=NULL);
    Buf.pre[DihedralDotBondBC]=-(RBuf->pre[AngleDotAB]);
  }

}

#endif

