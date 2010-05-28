
#ifndef _Functional_FENE_H_
#define _Functional_FENE_H_

#include "parameter-name-fene.h"
#include <cmath>

namespace std {

  void FuncFENE(const double dsq, const UniqueParameter* prm, double& func) {
    double r2=dsq*prm[FENEIvBoundLengthSQ].d;
    func=-prm[FENEHalfStrengthLengthSQ].d*log(1-r2);
  }

  void DiffFENE(const double dsq, const UniqueParameter* prm, double& diff) {
    double r2=dsq*prm[FENEIvBoundLengthSQ].d;
    diff=prm[FENEStrength].d/(1-r2);
  }

  void BothFENE(const double dsq, const UniqueParameter* prm,
                double& func, double& diff) {
    double r2=dsq*prm[FENEIvBoundLengthSQ].d;
    func=-prm[FENEHalfStrengthLengthSQ].d*log(1-r2);
    diff=prm[FENEStrength].d/(1-r2);
  }

}

#endif
