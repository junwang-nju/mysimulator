
#ifndef _Functional_LJ612_H_
#define _Functional_LJ612_H_

#include "data/name/lj612.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void FuncLJ612(const T& dsq, const UniqueParameter* prm, T& func) {
    T tmd=prm[LJ612EqRadiusSQ].value<T>()/dsq;
    tmd*=tmd*tmd;
    func=prm[LJ612EqEnergyDepth].value<T>()*tmd*(tmd-2.);
  }

  template <typename T>
  void DiffLJ612(const T& dsq, const UniqueParameter* prm, T& diff) {
    T ivd2=1./dsq;
    T tmd=prm[LJ612EqRadiusSQ].value<T>()*ivd2;
    tmd*=tmd*tmd;
    diff=prm[LJ612TwlfEqEnergyDepth].value<T>()*tmd*(1.-tmd)*ivd2;
  }

  template <typename T>
  void BothLJ612(const T& dsq, const UniqueParameter* prm, T& func, T& diff) {
    T ivd2=1./dsq;
    T tmd=prm[LJ612EqRadiusSQ].value<T>()*ivd2;
    tmd*=tmd*tmd;
    func=prm[LJ612EqEnergyDepth].value<T>()*tmd*(tmd-2.);
    diff=prm[LJ612TwlfEqEnergyDepth].value<T>()*tmd*(1.-tmd)*ivd2;
  }

}

#endif

