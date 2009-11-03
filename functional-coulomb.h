
#ifndef _Functional_Coulomb_H_
#define _Functional_Coulomb_H_

#include "var-vector.h"
#include "parameter-id.h"
#include <cmath>

namespace std {

  void FuncFactor_coulomb(const double& dsq, const varVector<double>& parm,
                          double& funcfac) {
    funcfac=parm[coulomb_Strength]/sqrt(dsq);
  }

  void DiffFactor_coulomb(const double& dsq, const varVector<double>& parm,
                          double& difffac) {
    double d=sqrt(dsq)*dsq;
    difffac=-parm[coulomb_Strength]/d;
  }

  void BothFactor_coulomb(const double& dsq, const varVector<double>& parm,
                          double& funcfac, double& difffac) {
    double d=sqrt(dsq);
    funcfac=parm[coulomb_Strength]/d;
    difffac=-funcfac/dsq;
  }

}

#endif

