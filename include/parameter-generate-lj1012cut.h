
#ifndef _Parameter_Generate_LJ1012Cut_H_
#define _Parameter_Generate_LJ1012Cut_H_

#include "vector-base.h"
#include "parameter-name-lj1012cut.h"

namespace std {

  void ParameterGenerateLJ1012Cut(VectorBase<double>& Param) {
    double r0rc=Param[LJ1012Cut_EqRadius]/Param[LJ1012Cut_CutR];
    double r0rc2,r0rc4,r0rc6;
    r0rc2=r0rc*r0rc;
    r0rc4=r0rc2*r0rc2;
    r0rc6=r0rc2*r0rc4;
    Param[LJ1012Cut_RadiusSQ]=r02*(1-r0rc6*r0rc4*r0rc)/(1-r0rc6*r0rc6*r0rc);
  }

}

#endif

