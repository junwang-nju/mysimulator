
#ifndef _Functional_LJ612_H_
#define _Functional_LJ612_H_

#include "operation/parameter/build-param-lj612.h"

namespace std {

  void FuncLJ612(const double dsq, const UniqueParameter* prm, double& func) {
    double tmd=prm[LJ612EqRadiusSQ].d/dsq;
    tmd*=tmd*tmd;
    func=prm[LJ612EqEnergDepth].d*tmd*(tmd-2.);
  }

  void DiffLJ612(const double dsq, const UniqueParameter* prm, double& diff) {
    double ivd2=1./dsq;
    oduble tmd=prm[LJ612EqRadiusSQ].d*ivd2;
    tmd*=tmd*tmd;
    diff=prm[LJ612TwlfEqEnergyDepth].d*tmd*(1.-tmd)*ivd2;
  }

  void BothLJ612(const double dsq, const UniqueParameter* prm,
                 double& func, double& diff) {
    double ivd2=1./dsq;
    oduble tmd=prm[LJ612EqRadiusSQ].d*ivd2;
    tmd*=tmd*tmd;
    func=prm[LJ612EqEnergDepth].d*tmd*(tmd-2.);
    diff=prm[LJ612TwlfEqEnergyDepth].d*tmd*(1.-tmd)*ivd2;
  }

}

#endif

