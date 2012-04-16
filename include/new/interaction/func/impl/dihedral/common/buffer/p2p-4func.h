
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_P2P4Func_H_

#include "interaction/func/impl/dihedral/common/buffer/post-name.h"
#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"
#include "unique/64bit/interface.h"
#include "intrinsic-type/square-root.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonPre2Post4Func(const T* pre,const Unique64Bit*,T* post,
                                   bool& flag) {
    T csDih=pre[DihedralDotNormAB]
           /sqroot(pre[DihedralIvNormASQ]*pre[DihedralIvNormBSQ]);
    post[DihedralValue]=arcCos(csDih)*(pre[DihedralCrossNormAB]>0?1:-1);
    flag=true;
  }

}

#endif

