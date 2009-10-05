
#ifndef _Functional_LJ612Cut_H_
#define _Functional_LJ612Cut_H_

#include "var-vector.h"
#include "parameter-id.h"
#include <cmath>

namespace std {

  void FuncFactor_lj612cut(const double& dsq, const varVector<double>& parm,
                           double& funcfac) {
    double d=sqrt(dsq);
    double d6=dsq*dsq*dsq;
    double ivr6=parm[lj612cut_Sigma6]/d6;
    funcfac=parm[lj612cut_Strength]*ivr6*(ivr6-2.)
           -parm[lj612cut_Vc]-parm[lj612cut_Kc]*(d-parm[lj612cut_CutR]);
  }

  void DiffFactor_lj612cut(const double& dsq, const varVector<double>& parm,
                           double& difffac) {
    double ivd2=1./dsq;
    double ivd=sqrt(ivd2);
    double ivr6=parm[lj612cut_Sigma6]*ivd2*ivd2*ivd2;
    difffac=parm[lj612cut_TwlfStrength]*ivr6*(1.-ivr6)*ivd2
           -parm[lj612cut_Kc]*ivd;
  }

  void BothFactor_lj612cut(const double& dsq, const varVector<double>& parm,
                           double& funcfac, double& difffac) {
    double ivd2=1./dsq;
    double ivd=sqrt(ivd2);
    double d=1./ivd;
    double ivr6=parm[lj612cut_Sigma6]*ivd2*ivd2*ivd2;
    funcfac=parm[lj612cut_Strength]*ivr6*(ivr6-2.)
           -parm[lj612cut_Vc]-parm[lj612cut_Kc]*(d-parm[lj612cut_CutR]);
    difffac=parm[lj612cut_TwlfStrength]*ivr6*(1.-ivr6)*ivd2
           -parm[lj612cut_Kc]*ivd;
  }

}

#endif
