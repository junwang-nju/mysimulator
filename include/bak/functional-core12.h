
#ifndef _Functional_Core12_H_
#define _Functional_Core12_H_

#include "vector-base.h"
#include "parameter-name-core12.h"

namespace std {

  void FuncCore12(const double dsq, const VectorBase<double>& Prm,
                  double& func) {
    double tmd=1./dsq;
    tmd*=tmd*tmd;
    tmd*=tmd;
    func=Prm[Core12_EqStrength]*tmd;
  }

  void DiffCore12(const double dsq, const VectorBase<double>& Prm,
                  double& diff) {
    double tmd=1./dsq;
    double tmd2=tmd*tmd;
    tmd2*=tmd2*tmd2;
    tmd*=tmd2;
    diff=-Prm[Core12_TwlfEqStrength]*tmd;
  }

  void BothCore12(const double dsq, const VectorBase<double>& Prm,
                  double& func, double& diff) {
    double tmd=1./dsq;
    double tmd2=tmd*tmd;
    tmd2*=tmd2*tmd2;
    tmd*=tmd2;
    func=Prm[Core12_EqStrength]*tmd2;
    diff=-Prm[Core12_TwlfEqStrength]*tmd;
  }

}

#endif

