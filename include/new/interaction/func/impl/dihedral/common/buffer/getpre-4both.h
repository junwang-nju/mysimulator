
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Both_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Both_H_

#include "interaction/func/impl/dihedral/common/buffer/getpre-4diff.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonGetPre4Both(InteractionBuffer<T>* Buf) {
    DihedralCommonGetPre4Diff(Buf);
  }

}

#endif

