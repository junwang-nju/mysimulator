
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Buffer_P2P4Func_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Buffer_P2P4Func_H_

#include "interaction/func/impl/dihedral/periodic/buffer/post-name.h"
#include "interaction/func/impl/dihedral/common/buffer/p2p-4func.h"

namespace mysimulator {

  template <typename T>
  void DihedralPeriodicPre2Post4Func(const T* pre,const Unique64Bit* P,T* post,
                                     bool& flag) {
    DihedralCommonPre2Post4Func(pre,P,post,flag);
  }

}

#endif

