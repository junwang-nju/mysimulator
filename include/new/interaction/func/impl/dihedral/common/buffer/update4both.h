
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_Update4Both_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_Update4Both_H_

#include "interaction/func/impl/dihedral/common/buffer/update4diff.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonUpdate4Both(const T* dt,const Unique64Bit* P,T* buffer) {
    DihedralCommonUpdate4Diff(dt,P,buffer);
  }

}

#endif

