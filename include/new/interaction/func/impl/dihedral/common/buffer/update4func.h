
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_Update4Func_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_Update4Func_H_

#include "interaction/func/impl/dihedral/common/buffer/name.h"
#include "unique/64bit/interface.h"
#include "intrinsic-type/square-root.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonUpdate4Func(const T* dt,const Unique64Bit*,T* buffer) {
    T csDih=dt[2]/sqroot(dt[0]*dt[1]);
    buffer[DihedralValue]=arcCos(csDih)*(dt[3]>0?1:-1);
  }

}

#endif

