
#ifndef _Functional_LJ1012_H_
#define _Functional_LJ1012_H_

#include "parameter-name-lj1012.h"

namespace std {

  void FuncLJ1012(const double dsq, const UniqueParameter* prm,
                  double& func) {
    double ivr2=prm[LJ1012EqRadiusSQ].d/dsq;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr2*ivr4;
    double tmd=ivr6-ivr4;
    func=prm[LJ1012EqEnergyDepth].d*ivr6*(5*tmd-ivr4);
  }

  void DiffLJ1012(const double dsq, const UniqueParameter* prm,
                  double& diff) {
    double ivd2=1./dsq;
    double ivr2=prm[LJ1012EqRadiusSQ].d*ivd2;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr4*ivr2;
    diff=prm[LJ1012SixtyEqEnergyDepth].d*ivr6*(ivr4-ivr6)*ivd2;
  }

  void BothLJ1012(const double dsq, const UniqueParameter* prm,
                  double& func, double& diff) {
    double ivd2=1./dsq;
    double ivr2=prm[LJ1012EqRadiusSQ].d*ivd2;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr4*ivr2;
    double tmd=ivr6-ivr4;
    func=prm[LJ1012EqEnergyDepth].d*ivr6*(5*tmd-ivr4);
    diff=-prm[LJ1012SixtyEqEnergyDepth].d*ivr6*tmd*ivd2;
  }

}

#endif

