
#ifndef _Functional_LJ612_H_
#define _Functional_LJ612_H_

#include "var-vector.h"

namespace std {

  void FuncFactor_lj612(const double& dsq, const varVector<double>& parm,
                        double& funcfac) {
    double tmd=parm[2]/dsq;
    tmd*=tmd*tmd;
    funcfac=parm[1]*tmd*(tmd-2.);
  }

  void DiffFactor_lj612(const double& dsq, const varVector<double>& parm,
                        double& difffac) {
    double ivd2=1./dsq, tmd=parm[2]*ivd2;
    tmd*=tmd*tmd;
    difffac=parm[2]*tmd*(1.-tmd)*ivd2;
  }

  void BothFactor_lj612(const double& dsq, const varVector<double>& parm,
                        double& funcfac, double& difffac) {
    double ivd2=1./dsq, tmd=parm[2]*ivd2;
    tmd*=tmd*tmd;
    funcfac=parm[1]*tmd*(tmd-2.);
    difffac=parm[3]*tmd*(1.-tmd)*ivd2;
  }

}

#endif
