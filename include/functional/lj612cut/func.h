
#ifndef _Functional_LJ612Cut_Func_H_
#define _Functional_LJ612Cut_Func_H_

#include "functional/lj612cut/parameter/name.h"
#include "unique-parameter/64bit/interface.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ612Cut(const T& dsq, const UniqueParameter64Bit* prm, T& func) {
    if(dsq>prm[LJ612CutCutRSq].value<T>())  func=0;
    else {
      T d=sqroot(dsq);
      T d6=dsq*dsq*dsq;
      T ivr6=prm[LJ612CutRealSigma6].value<T>()/d6;
      func=prm[LJ612CutRealStrength].value<T>()*ivr6*(ivr6-2.);
      func-=prm[LJ612CutVc].value<T>();
      func-=prm[LJ612CutKc].value<T>()*(d-prm[LJ612CutCutR].value<T>());
    }
  }

}

#endif

