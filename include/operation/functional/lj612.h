
#ifndef _Functional_LJ612_H_
#define _Functional_LJ612_H_

#include "data/name/parameter-lj612.h"

namespace std {

  template <typename T>
  void FuncLJ612(const T& dsq, const UniqueParameter* prm, T& func) {
    T tmd=prm[LJ612EqRadiusSQ].d/dsq;
    tmd*=tmd*tmd;
    func=prm[LJ612EqEnergDepth]<T>()*tmd*(tmd-2.);
  }

  template <typename T>
  void DiffLJ612(const T& dsq, const UniqueParameter* prm, T& diff) {
    T ivd2=1./dsq;
    T tmd=prm[LJ612EqRadiusSQ].d*ivd2;
    tmd*=tmd*tmd;
    diff=prm[LJ612TwlfEqEnergyDepth]<T>()*tmd*(1.-tmd)*ivd2;
  }

  template <typename T>
  void BothLJ612(const T& dsq, const UniqueParameter* prm, T& func, T& diff) {
    T ivd2=1./dsq;
    T tmd=prm[LJ612EqRadiusSQ].d*ivd2;
    tmd*=tmd*tmd;
    func=prm[LJ612EqEnergDepth].d*tmd*(tmd-2.);
    diff=prm[LJ612TwlfEqEnergyDepth].d*tmd*(1.-tmd)*ivd2;
  }

}

#endif

