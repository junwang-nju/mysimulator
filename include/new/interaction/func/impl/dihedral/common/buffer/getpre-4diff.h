
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Diff_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Diff_H_

#include "interaction/func/impl/dihedral/common/buffer/getpre-4func.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonGetPre4Diff(
      InteractionBuffer<T>* Buf,const int* inf,T* pre) {
    DihedralCommonGetPre4Func(Buf,inf,pre);
    InteractionBuffer<T>* rBuf;
    assert(inf[DihedralAxisInf]<0);
    rBuf=Buf+inf[DihedralAxisInf];
    pre[DihedralAxisSQ]=rBuf->pre[PairwiseDistanceSQ];
    assert(inf[DihedralDotABInf]<0);
    rBuf=Buf+inf[DihedralDotABInf];
    pre[DihedralDotBondAB]=-(rBuf->pre[AngleDotAB]);
    assert(inf[DihedralDotBCInf]<0);
    rBuf=Buf+inf[DihedralDotBCInf];
    pre[DihedralDotBondBC]=-(rBuf->pre[AngleDotAB]);
  }

}

#endif

