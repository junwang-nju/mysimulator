
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_P2P4Both_H_

#include "interaction/func/impl/dihedral/common/buffer/p2p-4diff.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonPre2Post4Both(const T* pre,const Unique64Bit* P,T* post,
                                   bool& flag) {
    DihedralCommonPre2Post4Diff(pre,P,post,flag);
  }

}

#endif

