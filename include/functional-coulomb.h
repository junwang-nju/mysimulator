
#ifndef _Functional_Coulomb_H_
#define _Functional_Coulomb_H_

#include "parameter-name-coulomb.h"
#include <cmath>

namespace std {

  void FuncCoulomb(const double dsq, const UniqueParameter* prm,
                   double& func) {
    func=prm[CoulombStrength].d/sqrt(dsq);
  }

  void DiffCoulomb(const double dsq, const UniqueParameter* prm,
                   double& diff) {
    double d=sqrt(dsq)*dsq;
    diff=-prm[CoulombStrength].d/d;
  }

  void BothCoulomb(const double dsq, const UniqueParameter* prm,
                   double& func, double& diff) {
    double d=sqrt(dsq);
    func=prm[CoulombStrength].d/d;
    diff=-func/dsq;
  }

}

#endif

