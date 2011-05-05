
#ifndef _Functional_LJ612_Both_H_
#define _Functional_LJ612_Both_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/lj612/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BothLJ612(const T& dsq, const UniqueParameter64Bit* prm, T& fc, T& df) {
    T ivd2=1./dsq;
    T tmd=prm[LJ612EqRadiusSq].value<T>()*ivd2;
    tmd*=tmd*tmd;
    fc=prm[LJ612EqEnergyDepth].value<T>()*tmd*(tmd-2.);
    df=prm[LJ612TwlfEnergyDepth].value<T>()*tmd*(1.-tmd)*ivd2;
  }

}

#endif

