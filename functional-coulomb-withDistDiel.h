
#ifndef _Functional_With_DistanceDielectric_H_
#define _Functional_With_DistanceDielectric_H_

#include "var-vector.h"
#include "parameter-id.h"

namespace std {

  void FuncFactor_coulomb_wde(const double& dsq, const varVector<double>& parm,
                              double& funcfac) {
    funcfac=parm[coulombwde_Strength]/dsq;
  }

  void DiffFactor_coulomb_wde(const double& dsq, const varVector<double>& parm,
                              double& difffac) {
    difffac=-param[coulombwde_DualStrength]/(dsq*dsq);
  }

  void BothFactor_coulomb_wde(const double& dsq, const varVector<double>& parm,
                              double& funcfac, double& difffac) {
    double ivd2=1./dsq;
    funcfac=parm[coulombwde_Strength]*ivd2;
    difffac=-(funcfac+funcfac)*ivd2;
  }

}

#endif

