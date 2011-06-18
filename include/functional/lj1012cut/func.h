
#ifndef _Functional_LJ1012Cut_Func_H_
#define _Functional_LJ1012Cut_Func_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/lj1012cut/parameter/name.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ1012Cut(const T& dsq,const UniqueParameter64Bit* prm,T& func) {
    if(dsq>prm[LJ1012CutCutRSq].value<T>()) func=0.;
    else {
      T d=sqroot(dsq);
      T sgr2=prm[LJ1012CutRealRadiusSq].value<T>()/dsq;
      T sgr10;
      sgr10=sgr2*sgr2;
      sgr10*=sgr10;
      sgr10*=sgr2;
      func=prm[LJ1012CutEqEnergyDepth].value<T>()*sgr10*(5*sgr2-6.);
      func-=prm[LJ1012CutVc].value<T>();
      func-=prm[LJ1012CutKc].value<T>()*(d-prm[LJ1012CutCutR].value<T>());
    }
  }

}

#endif

