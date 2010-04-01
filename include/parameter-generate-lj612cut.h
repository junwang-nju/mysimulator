
#ifndef _Parameter_Generate_LJ612Cut_H_
#define _Parameter_Generate_LJ612Cut_H_

#include "vector-base.h"
#include "parameter-name-lj612cut.h"

namespace std {

  void ParameterGenerateLJ612Cut(VectorBase<double>& Param) {
    double r0rc=Param[LJ612Cut_EqRadius]/Param[LJ612Cut_CutR];
    double r0rc6,r06,rc6;
    r06=Param[LJ612Cut_EqRadius];
    r06=r06*r06*r06;
    r06*=r06;
    rc6=Param[LJ612Cut_CutR];
    rc6=rc6*rc6*rc6;
    rc6*=rc6;
    r0rc6=r06/rc6;
    Param[LJ612Cut_Sigma6]=r06*(1-r0rc6*r0rc)/(1-r0rc6*r0rc6*r0rc);
    double sgrc6=Param[LJ612Cut_Sigma6]/rc6;
    Param[LJ612Cut_Vc]=sgrc6*(sgrc6-2.);
    Param[LJ612Cut_Kc]=-12*sgrc6*(sgrc6-1.)/Param[LJ612Cut_CutR];
    double sgr06=Param[LJ612Cut_Sigma6]/r06;
    double e;
    e=sgr06*(sgr06-2.);
    e-=Param[LJ612Cut_Vc];
    e-=Param[LJ612Cut_Kc]*(Param[LJ612Cut_EqRadius]-Param[LJ612Cut_CutR]);
    Param[LJ612Cut_Strength]=-1./e;
    Param[LJ612Cut_Vc]*=Param[LJ612Cut_Strength];
    Param[LJ612Cut_Kc]*=Param[LJ612Cut_Strength];
    Param[LJ612Cut_TwlfStrength]=Param[LJ612Cut_Strength]*12;
  }

}

#endif

