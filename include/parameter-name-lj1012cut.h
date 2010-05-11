
#ifndef _Parameter_Name_LJ1012Cut_H_
#define _Parameter_Name_LJ1012Cut_H_

namespace std {

  enum LJ1012CutParameterName {
    LJ1012CutEqRadius=0,
    LJ1012CutEqEnergyDepth,
    LJ1012CutCutR,
    LJ1012CutCutRSQ,
    LJ1012CutRealEnergyDepth,
    LJ1012CutRealRadiusSQ,
    LJ1012CutSixtyRealEnergyDepth,
    LJ1012CutVc,
    LJ1012CutKc,
    LJ1012CutNumberParameter
  };

}

#include "unique-parameter.h"
#include "vector.h"

namespace std {

  void GenerateParameterLJ1012Cut(UniqueParameter* prm) {
    double r0rc=prm[LJ1012CutEqRadius].d/prm[LJ1012CutCutR].d;
    double rc2,r02;
    rc2=prm[LJ1012CutCutR].d*prm[LJ1012CutCutR].d;
    prm[LJ1012CutCutRSQ]=rc2;
    r02=prm[LJ1012CutEqRadius].d*prm[LJ1012CutEqRadius].d;
    double r0rc2,r0rc4,r0rc6,r0rc7;
    r0rc2=r0rc*r0rc;
    r0rc4=r0rc2*r0rc2;
    r0rc6=r0rc2*r0rc4;
    r0rc7=r0rc6*r0rc;
    prm[LJ1012CutRealRadiusSQ]=r02*(1.-r0rc7*r0rc4)/(1.-r0rc7*r0rc6);
    double sgrc2,sgrc4,sgrc6,sgrc10;
    sgrc2=prm[LJ1012CutRealRadiusSQ].d/rc2;
    sgrc4=sgrc2*sgrc2;
    sgrc6=sgrc2*sgrc4;
    sgrc10=sgrc6*sgrc4;
    prm[LJ1012CutVc]=sgrc10*(sgrc2*5-6.);
    prm[LJ1012CutKc]=60*sgrc10*(1.-sgrc2)/prm[LJ1012CutCutR].d;
    double sgr02,sgr04,sgr06;
    sgr02=prm[LJ1012CutRealRadiusSQ].d/r02;
    sgr04=sgr02*sgr02;
    sgr06=sgr02*sgr04;
    double e;
    e=sgr06*sgr04*(5.*sgr02-6.);
    e-=prm[LJ1012CutVc].d;
    e-=prm[LJ1012CutKc].d*(prm[LJ1012CutEqRadius].d-prm[LJ1012CutCutR].d);
    e=-1./e;
    prm[LJ1012CutRealEnergyDepth]=e;
    prm[LJ1012CutVc].d*=e;
    prm[LJ1012CutKc].d*=e;
    prm[LJ1012CutSixtyRealEnergyDepth]=60*e;
  }

  void GenerateParameterLJ1012Cut(Vector<UniqueParameter>& prm) {
    assert(prm.size>=LJ1012CutNumberParameter);
    GenerateParameterLJ1012Cut(prm());
  }

}

#endif

