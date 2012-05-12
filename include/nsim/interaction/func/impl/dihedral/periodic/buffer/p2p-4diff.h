
#ifndef _Interaction_Func_Impl_Dihedral_Periodic_Buffer_Pre2Post4Diff_H_
#define _Interaction_Func_Impl_Dihedral_Periodic_Buffer_Pre2Post4Diff_H_

#include "interaction/func/impl/dihedral/periodic/buffer/post-name.h"
#include "interaction/func/impl/dihedral/common/buffer/p2p-4diff.h"

namespace mysimulator {

  template <typename T>
  void DihedralPeriodicPre2Post4Diff(
      const Array1D<T>& pre,const Array1D<Unique64Bit>& P,Array1D<T>& post,
      bool& flag) {
    DihedralCommonPre2Post4Diff(pre,P,post,flag);
  }

}

#endif

