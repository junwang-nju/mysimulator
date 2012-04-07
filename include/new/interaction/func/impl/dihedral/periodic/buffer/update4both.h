
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Buffer_Update4Both_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Buffer_Update4Both_H_

#include "interaction/func/impl/dihedral/periodic/buffer/name.h"
#include "interaction/func/impl/dihedral/common/buffer/update4both.h"

namespace mysimulator {

  template <typename T>
  void DihedralPeriodicUpdate4Both(const T* dt,const Unique64Bit* P,T* buffer) {
    DihedralCommonUpdate4Both(dt,P,buffer);
  }

}

#endif

