
#ifndef _Functional_Coulomb_H_
#define _Functional_Coulomb_H_

#include "vector-base.h"
#include "parameter-name-coulomb.h"
#include <cmath>

namespace std {

  void FuncCoulomb(const double dsq, const VectorBase<double>& Prm,
                   double& func) {
    func=Prm[Coulomb_Strength]/sqrt(dsq);
  }

  void DiffCoulomb(const double dsq, const VectorBase<double>& Prm,
                   double& diff) {
    double d=sqrt(dsq)*dsq;
    diff=-Prm[Coulomb_Strength]/d;
  }

  void BothCoulomb(const double dsq, const VectorBase<double>& Prm,
                   double& func, double& diff) {
    double d=sqrt(dsq);
    func=Prm[Coulomb_Strength]/d;
    diff=-func/dsq;
  }

}

#endif

