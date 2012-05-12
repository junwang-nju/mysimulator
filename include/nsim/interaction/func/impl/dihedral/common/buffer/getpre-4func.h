
#ifndef _Interaction_Func_Impl_Dihedral_Common_Buffer_GetPre4Func_H_
#define _Interaction_Func_Impl_Dihedral_Common_Buffer_GetPre4Func_H_

#include "interaction/buffer/interface.h"
#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"
#include "interaction/func/impl/dihedral/common/buffer/vec-name.h"
#include "interaction/func/impl/dihedral/common/buffer/inf-name.h"
#include "interaction/func/impl/angle/comon/buffer/post-name.h"
#include "intrinsic-type/square.h"
#include "array/1d/norm.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonGetPre4Func(InteractionBuffer<T>& Buf) {
    assert(Buf.Inf.IsValid());
    InteractionBuffer<T>* RBuf=Buf.inf[DihedralNormAInf];
    assert(RBuf!=NULL);
    Buf.pre[DihedralIvNormASQ]=
      (RBuf->postUpdate?1./NormSQ(Buf.tmvec[DihedralNormVecA]):
                        Square(RBuf->post[AngleIvRabSin]));
    RBuf=Buf.inf[DihedralNormBInf];
    assert(RBuf!=NULL);
    Buf.pre[DihedralIvNormBSQ]=
      (RBuf->postUpdate?1./NormSQ(Buf.tmvec[DihedralNormVecB]):
                        Square(RBuf->post[AngleIvRabSin]));
  }

}

#endif

