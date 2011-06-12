
#ifndef _Functional_LJ1012_Diff_H_
#define _Functional_LJ1012_Diff_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/lj1012/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ1012(const T& dsq, const UniqueParameter64Bit* prm, T& diff) {
    T ivd2=1./dsq;
    T ivr2=prm[LJ1012EqRadiusSq].value<T>()*ivd2;
    T ivr4=ivr2*ivr2;
    T ivr6=ivr4*ivr2;
    diff=prm[LJ1012SixtyEqEnergyDepth].value<T>()*ivr6*(ivr4-ivr6)*ivd2;
  }

}

#endif

