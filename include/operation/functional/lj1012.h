
#ifndef _Functional_LJ1012_H_
#define _Functional_LJ1012_H_

#include "data/name/parameter-lj1012.h"

namespace std {

  template <typename T>
  void FuncLJ1012(const T& dsq, const UniqueParameter* prm, T& func) {
    T ivr2=prm[LJ1012EqRadiusSQ].d/dsq;
    T ivr4=ivr2*ivr2;
    T ivr6=ivr2*ivr4;
    T tmd=ivr6-ivr4;
    func=prm[LJ1012EqEnergyDepth].d*ivr6*(5*tmd-ivr4);
  }

  template <typename T>
  void DiffLJ1012(const T& dsq, const UniqueParameter* prm, T& diff) {
    T ivd2=1./dsq;
    T ivr2=prm[LJ1012EqRadiusSQ].d*ivd2;
    T ivr4=ivr2*ivr2;
    T ivr6=ivr2*ivr4;
    diff=prm[LJ1012SixtyEqEnergyDepth].d*ivr6*(ivr4-ivr6)*ivd2;
  }

  template <typename T>
  void BothLJ1012(const T& dsq, const UniqueParameter* prm, T& func, T& diff) {
    T ivd2=1./dsq;
    T ivr2=prm[LJ1012EqRadiusSQ].d*ivd2;
    T ivr4=ivr2*ivr2;
    T ivr6=ivr2*ivr4;
    T tmd=ivr6-ivr4;
    func=prm[LJ1012EqEnergyDepth].d*ivr6*(5*tmd-ivr4);
    diff=-prm[LJ1012SixtyEqEnergyDepth].d*ivr6*tmd*ivd2;
  }

}

#endif

