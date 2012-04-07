
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_Update4Diff_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_Update4Diff_H_

#include "interaction/func/impl/dihedral/common/buffer/name.h"
#include "unique/64bit/interface.h"
#include "intrinsic-type/square-root.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonUpdate4Diff(const T* dt,const Unique64Bit* P,T* buffer) {
    T tmda=1./dt[0];
    T tmdb=1./dt[1];
    T csDih=dt[2]*sqroot(tmda*tmdb);
    buffer[DihedralValue]=arcCos(csDih)*(dt[3]>0?1:-1);
    T tmd=sqroot(dt[4]);
    T tmd1=tmd/dt[4];
    buffer[DihedralFactorI]=-tmd*tmda;
    buffer[DihedralFactorJ]=-dt[5]*tmda*tmd1;
    buffer[DihedralFactorK]=dt[6]*tmdb*tmd1;
    buffer[DihedralFactorL]=tmd*tmdb;
  }

}

#endif

