
#ifndef _Functional_LJ1012_Func_H_
#define _Functional_LJ1012_Func_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/lj1012/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void FuncLJ1012(const T& dsq, const UniqueParameter64Bit* prm, T& func) {
    T ivr2=prm[LJ1012EqRadiusSq].value<T>()/dsq;
    T ivr4=ivr2*ivr2;
    T ivr6=ivr4*ivr2;
    T tmd=ivr6-ivr4;
    func=prm[LJ1012EqEnergyDepth].value<T>()*ivr6*(5*tmd-ivr4);
  }

}

#endif

