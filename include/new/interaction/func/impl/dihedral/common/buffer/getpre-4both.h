
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Both_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_GetPre4Both_H_

#include "interaction/func/impl/dihedral/common/buffer/getpre-4diff.h"

namespace mysimultor {

  template <typename T>
  void DihedralCommonGetPre4Both(
      InteractionBuffer<T>* Buf,const int* inf,T* pre) {
    DihedralCommonGetPre4Diff(Buf,inf,pre);
  }

}

#endif

