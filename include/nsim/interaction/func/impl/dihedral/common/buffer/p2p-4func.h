
#ifndef _Interaction_Func_Impl_Dihedral_Common_Buffer_Pre2Post4Func_H_
#define _Interaction_Func_Impl_Dihedral_Common_Buffer_Pre2Post4Func_H_

#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"
#include "interaction/func/impl/dihedral/common/buffer/post-name.h"
#include "unique/64bit/interface.h"
#include "intrinsic-type/square-root.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonPre2Post4Func(
      const Array1D<T>& pre,const Array1D<Unique64Bit>&,Array1D<T>& post,
      bool& flag) {
    T csDih=pre[DihedralDotNormAB]/
            sqroot(pre[DihedralIvNormASQ]*pre[DihedralIvNormBSQ]);
    post[DihedralValue]=arcCos(csDih)*(pre[DihedralCrossNormAB]>0?1:-1);
    flag=true;
  }

}

#endif

