
#ifndef _Interaction_Func_Implement_Dihedral_Common_Buffer_P2P4Diff_H_
#define _Interaction_Func_Implement_Dihedral_Common_Buffer_P2P4Diff_H_

#include "interaction/func/impl/dihedral/common/buffer/post-name.h"
#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"
#include "unique/64bit/interface.h"
#include "intrinsic-type/square-root.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename T>
  void DihedralCommonPre2Post4Diff(const T* pre,const Unique64Bit* P,T* post,
                                   bool& flag) {
    T tmda=1./pre[DihedralIvNormASQ];
    T tmdb=1./pre[DihedralIvNormBSQ];
    T csDih=pre[DihedralDotNormAB]*sqroot(tmda*tmdb);
    post[DihedralValue]=arcCos(csDih)*(pre[DihedralCrossNormAB]>0?1:-1);
    T tmd=sqroot(pre[DihedralAxisSQ]);
    T tmd1=tmd/pre[DihedralAxisSQ];
    post[DihedralFactorI]=-tmd*tmda;
    post[DihedralFactorJ]=-pre[DihedralDotBondAB]*tmda*tmd1;
    post[DihedralFactorK]=pre[DihedralDotBondBC]*tmdb*tmd1;
    post[DihedralFactorL]=tmd*tmdb;
    flag=false;
  }

}

#endif

