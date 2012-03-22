
#ifndef _Interaction_Func_Impl_Pairwise_LJ612Cut_Both_DistSQ_H_
#define _Interaction_Func_Impl_Pairwise_LJ612Cut_Both_DistSQ_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void BothLJ612CutDistSQ(const T* dsq,const Unique64Bit* P,T* func,T* diff) {
    if((*dsq)>P[LJ612CutCutRSQ].value<T>())  (*func)=(*diff)=0.;
    else {
      T d=sqroot(*dsq);
      T ivd=1./d;
      T ivd2=ivd*ivd;
      T ivd6=ivd2*ivd2*ivd2;
      T ivr6=P[LJ612CutRealSigma6].value<T>()*ivd6;
      T ivr12=ivr6*ivr6;
      T fc,df;
      fc=P[LJ612CutRealStrength].value<T>()*(ivr12-ivr6-ivr6);
      fc-=P[LJ612CutVc].value<T>();
      fc-=P[LJ612CutKc].value<T>()*(d-P[LJ612CutCutR].value<T>());
      df=P[LJ612CutTwlfRealStrength].value<T>()*(ivr6-ivr12)*ivd2;
      df-=P[LJ612CutKc].value<T>()*ivd;
      *func=fc;
      *diff=df;
    }
  }

}

#endif

