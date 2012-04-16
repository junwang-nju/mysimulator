
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Buffer_P2P4Both_H_

#include "interaction/func/impl/dihedral/periodic/buffer/post-name.h"
#include "interaction/func/impl/dihedral/common/buffer/p2p-4both.h"

namespace mysimulator {

  template <typename T>
  void DihedralPeriodicPre2Post4Both(const T* pre,const Unique64Bit* P,T* post,
                                     bool& flag) {
    DihedralCommonPre2Post4Both(pre,P,post,flag);
  }

}

#endif
