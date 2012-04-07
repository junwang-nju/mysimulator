
#ifndef _Interaction_Func_Implement_Angle_Common_Buffer_Update4Both_H_
#define _Interaction_Func_Implement_Angle_Common_Buffer_Update4Both_H_

#include "interaction/func/impl/angle/common/buffer/name.h"
#include "unique/64bit/interface.h"

namespace mysimulator {

  template <typename T>
  void AngleCommonUpdate4Both(const T* dsq,const Unique64Bit*,T* buffer) {
    T tmda=1./dsq[0];
    T tmdb=1./dsq[1];
    T tmd=sqroot(tmda*tmdb);
    T tmd1=tmd*dsq[2];
    T tmd2=1./sqroot(1-tmd1*tmd1);
    T tmd3=tmd1*tmd2;
    buffer[AngleCosine]=tmd1;
    buffer[AngleIvRabSin]=tmd*tmd2;
    buffer[AngleIvRaSQCtg]=tmd3*tmda;
    buffer[AngleIvRbSQCtg]=tmd3*tmdb;
  }

}

#endif

