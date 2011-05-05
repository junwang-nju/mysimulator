
#ifndef _Functional_LJ612_Func_H_
#define _Functional_LJ612_Func_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/lj612/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ612(const T& dsq, const UniqueParameter64Bit* prm, T& func) {
    T tmd=prm[LJ612EqRadiusSq].value<T>()/dsq;
    tmd*=tmd*tmd;
    func=prm[LJ612EqEnergyDepth].value<T>()*tmd*(tmd-2.);
  }

}

#endif

