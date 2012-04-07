
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Buffer_Update4Diff_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Buffer_Update4Diff_H_

#include "interaction/func/impl/dihedral/periodic/buffer/name.h"
#include "interaction/func/impl/dihedral/common/buffer/update4diff.h"

namespace mysimulator {

  template <typename T>
  void DuhedralPeriodicUpdate4Diff(const T* df,const Unique64Bit* P,T* buffer) {
    DihedralCommonUpdate4Diff(dt,P,buffer);
  }

}

#endif

