
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Buffer_Update4Func_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Buffer_Update4Func_H_

#include "interaction/func/impl/dihedral/periodic/buffer/name.h"
#include "interaction/func/impl/dihedral/common/buffer/update4func.h"

namespace mysimulator {

  template <typename T>
  void DihedralPeriodicUpdate4Func(const T* dt,const Unique64Bit* P,T* buffer) {
    DihedralCommonUpdate4Func(dt,P,buffer);
  }

}

#endif

