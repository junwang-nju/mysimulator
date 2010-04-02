
#ifndef _Parameter_Generate_LJ1012Cut_H_
#define _Parameter_Generate_LJ1012Cut_H_

#include "vector-base.h"
#include "parameter-name-lj1012cut.h"

namespace std {

  void ParameterGenerateLJ1012Cut(VectorBase<double>& Param) {
    double r0rc=Param[LJ1012Cut_EqRadius]/Param[LJ1012Cut_CutR];
    double rc2,r02;
    rc2=Param[LJ1012Cut_CutR]*Param[LJ1012Cut_CutR];
    r02=Param[LJ1012Cut_EqRadius]*Param[LJ1012Cut_EqRadius];
    double r0rc2,r0rc4,r0rc6;
    r0rc2=r0rc*r0rc;
    r0rc4=r0rc2*r0rc2;
    r0rc6=r0rc2*r0rc4;
    Param[LJ1012Cut_RadiusSQ]=r02*(1-r0rc6*r0rc4*r0rc)/(1-r0rc6*r0rc6*r0rc);
    double sgrc2,sgrc4,sgrc6;
    sgrc2=Param[LJ1012Cut_RadiusSQ]/rc2;
    sgrc4=sgrc2*sgrc2;
    sgrc6=sgrc4*sgrc2;
    Param[LJ1012Cut_Vc]=sgrc6*sgrc4*(sgrc2*5.-6.);
    Param[LJ1012Cut_Kc]=-60*sgrc6*sgrc4*(sgrc2-1.)/Param[LJ1012Cut_CutR];
    double sgr02,sgr04,sgr06;
    sgr02=Param[LJ1012Cut_RadiusSQ]/r02;
    sgr04=sgr02*sgr02;
    sgr06=sgr04*sgr02;
    double e;
    e=sgr06*sgr04*(sgr02*5.-6.);
    e-=Param[LJ1012Cut_Vc];
    e-=Param[LJ1012Cut_Kc]*(Param[LJ1012Cut_EqRadius]-Param[LJ1012Cut_CutR]);
    e=-1./e;
    Param[LJ1012Cut_Strength]=e;
    Param[LJ1012Cut_Vc]*=e;
    Param[LJ1012Cut_Kc]*=e;
    Param[LJ1012Cut_SixtyStrength]=60*e;
  }

}

#endif

