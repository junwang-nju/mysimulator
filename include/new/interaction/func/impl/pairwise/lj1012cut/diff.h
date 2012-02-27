
#ifndef _Interaction_Func_Implement_Pairwise_LJ1012Cut_Diff_H_
#define _Interaction_Func_Implement_Pairwise_LJ1012Cut_Diff_H_

#include "interaction/func/impl/pairwise/lj1012cut/parameter/name.h"
#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ1012Cut(const T& dsq, const Unique64Bit* P, T& diff) {
    if(dsq>P[LJ1012CutCutRSQ].value<T>())  diff=0;
    else {
      T ivd2=1./dsq;
      T ivd=sqroot(ivd2);
      T sgr2=P[LJ1012CutRealRadiusSQ].value<T>()*ivd2;
      T sgr10;
      sgr10=sgr2*sgr2;
      sgr10*=sgr10;
      sgr10*=sgr2;
      diff=P[LJ1012CutSixtyRealEnergyDepth].value<T>()*sgr10*(1.-sgr2)*ivd2;
      diff-=P[LJ1012CutKc].value<T>()*ivd;
    }
  }

}

#endif

