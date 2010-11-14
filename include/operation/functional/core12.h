
#ifndef _Functional_Core12_H_
#define _Functional_Core12_H_

#include "operation/parameter/build-param-core12.h"

namespace std {

  void FuncCore12(const double dsq, const UniqueParameter* prm, double& func) {
    double tmd=1./dsq;
    tmd*=tmd*tmd;
    tmd*=tmd;
    func=prm[Core12EqStrength].d*tmd;
  }

  void DiffCore12(const double dsq, const UniqueParameter* prm, double& diff) {
    double tmd=1./dsq;
    double tmd2=tmd*tmd;
    tmd2*=tmd2*tmd2;
    diff=-prm[Core12TwlfEqStrength].d*tmd*tmd2;
  }

  void BothCore12(const double dsq, const UniqueParameter* prm,
                  double& func, double& diff) {
    double tmd=1./dsq;
    double tmd2=tmd*tmd;
    tmd2*=tmd2*tmd2;
    func=prm[Core12EqStrength].d*tmd2;
    diff=-prm[Core12TwlfEqStrength].d*tmd*tmd2;
  }

}

#endif

