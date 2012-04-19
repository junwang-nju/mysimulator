
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Func_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Func_H_

#include "interaction/buffer/interface.h"
#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"
#include "interaction/func/impl/dihedral/common/buffer/vec-name.h"
#include "interaction/func/impl/dihedral/common/buffer/inf-name.h"
#include "interaction/func/impl/angle/common/buffer/post-name.h"
#include "intrinsic-type/square.h"
#include "array/1d/content/norm.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonGetPre4Func(
      InteractionBuffer<T>* Buf,const int* inf,T* pre) {
    InteractionBuffer<T>* rBuf;
    assert(inf[DihedralNormAInf]<0);
    rBuf=Buf+inf[DihedralNormAInf];
    pre[DihedralIvNormASQ]=
      (rBuf->postUpdate?1./normSQ(Buf->tmvec[DihedralNormVecA]):
                        square(rBuf->post[AngleIvRabSin]));
    assert(inf[DihedralNormBInf]<0);
    rBuf=Buf+inf[DihedralNormBInf];
    pre[DihedralIvNormBSQ]=
      (rBuf->postUpdate?1./normSQ(Buf->tmvec[DihedralNormVecB]):
                        square(rBuf->post[AngleIvRabSin]));
  }

}

#endif

