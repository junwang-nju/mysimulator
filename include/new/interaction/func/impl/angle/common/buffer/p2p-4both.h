
#ifndef _Interaction_Func_Implement_Angle_Common_Buffer_P2P4Both_H_
#define _Interaction_Func_Implement_Angle_Common_Buffer_P2P4Both_H_

#include "interaction/func/impl/angle/common/buffer/post-name.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "unique/64bit/interface.h"

namespace mysimulator {

  template <typename T>
  void AngleCommonPre2Post4Both(const T* pre,const Unique64Bit*,T* post,
                                bool& flag) {
    T tmda=1./pre[AngleEdgeA];
    T tmdb=1./pre[AngleEdgeB];
    T tmd=sqroot(tmda*tmdb);
    T tmd1=tmd*pre[AngleDotAB];
    T tmd2=1./sqroot(1-tmd1*tmd1);
    T tmd3=tmd1*tmd2;
    post[AngleCosine]=tmd1;
    post[AngleIvRabSin]=tmd*tmd2;
    post[AngleIvRaSQCtg]=tmd3*tmda;
    post[AngleIvRbSQCtg]=tmd3*tmdb;
    flag=false;
  }

}

#endif

