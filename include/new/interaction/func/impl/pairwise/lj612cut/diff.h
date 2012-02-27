
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Diff_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ612Cut(const T& dsq, const Unique64Bit* P, T& diff) {
    if(dsq>P[LJ612CutCutRSQ].value<T>())  diff=0.;
    else {
      T d=sqroot(dsq);
      T ivd=1./d;
      T ivd2=ivd*ivd;
      T ivd6=ivd2*ivd2*ivd2;
      T ivr6=P[LJ612CutRealSigma6].value<T>()*ivd6;
      diff=P[LJ612CutTwlfRealStrength].value<T>()*ivr6*(1.-ivr6)*ivd2;
      diff-=P[LJ612CutKc].value<T>()*ivd;
    }
  }

}

#endif

