
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Diff_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Diff_H_

#include "interaction/buffer/interface.h"
#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonGetPre4Diff(
      InteractionBuffer<T>* Buf,const int* inf,T* pre) {
    InteractionBuffer<T>* rBuf;
    assert(inf[0]<0)
    rBuf=Buf+inf[0];
    pre[DihedralIvNormASQ]=
      (rBuf->postUpdate?1./normSQ(Buf->tmvec[3]):
                        square(rBuf->post[AngleIvRabSin]));
    assert(inf[1]<0)
    rBuf=Buf+inf[1];
    pre[DihedralIvNormBSQ]=
      (rBuf->postUpdate?1./normSQ(Buf->tmvec[4]):
                        square(rBuf->post[AngleIvRabSin]));
    assert(inf[2]<0);
    rBuf=Buf+inf[2];
    pre[DihedralAxisSQ]=rBuf->pre[PairwiseDistanceSQ];
    assert(inf[3]<0);
    rBuf=Buf+inf[3];
    pre[DihedralDotBondAB]=rBuf->pre[AngleDotAB];
    assert(inf[4]<0);
    rBuf=Buf+inf[4];
    pre[DihedralDotBondBC]=rBuf->pre[AngleDotAB];
  }

}

#endif

