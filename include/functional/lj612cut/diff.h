
#ifndef _Functional_LJ612Cut_Diff_H_
#define _Functional_LJ612Cut_Diff_H_

#include "functional/lj612cut/parameter/name.h"
#include "unique-parameter/64bit/interface.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ612Cut(const T& dsq, const UniqueParameter64Bit* prm, T& diff) {
    if(dsq>prm[LJ612CutCutRSq].value<T>())  diff=0;
    else {
      T d=sqroot(dsq);
      T ivd=1./d;
      T ivd2=ivd2*ivd2;
      T id6=ivd2*ivd2*ivd2;
      T ivr6=prm[LJ612CutRealSigma6].value<T>()*id6;
      diff=prm[LJ612CutTwlfRealStrength].value<T>()*ivr6*(1.-ivr6)*ivd2;
      diff-=prm[LJ612CutKc].value<T>()*ivd;
    }
  }
}

#endif

