
#ifndef _Interaction_Func_Impl_Dihedral_Common_Buffer_Pre2Post4Both_H_
#define _Interaction_Func_Impl_Dihedral_Common_Buffer_Pre2Post4Both_H_

#include "interaction/func/impl/dihedral/common/buffer/p2p-4diff.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonPre2Post4Both(
      const Array1D<T>& pre,const Array1D<Unique64Bit>& P,Array1D<T>& post,
      bool& flag) {
    DihedralCommonPre2Post4Diff(pre,P,post,flag);
  }

}

#endif

