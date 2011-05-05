
#ifndef _Functional_LJ612_Diff_H_
#define _Functional_LJ612_Diff_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/lj612/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void DiffLJ612(const T& dsq, const UniqueParameter64Bit* prm, T& diff) {
    T=ivd2=1./dsq;
    T tmd=prm[LJ612EqRadiusSq].value<T>()*ivd2;
    tmd*=tmd*tmd;
    diff=prm[LJ612TwlfEnergyDepth].value<T>()*tmd*(1.-tmd)*ivd2;
  }

}

#endif

