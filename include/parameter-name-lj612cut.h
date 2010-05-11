
#ifndef _Parameter_Name_LJ612Cut_H_
#define _Parameter_Name_LJ612Cut_H_

namespace std {

  enum LJ612CutParameterName {
    LJ612CutEqRadius=0,
    LJ612CutEqStrength,
    LJ612CutCutR,
    LJ612CutVc,
    LJ612CutKc,
    LJ612CutRealSigma6,
    LJ612CutRealStrength,
    LJ612CutTwlfRealStrength,
    LJ612CutNumberParameter
  };

}

#include "unique-parameter.h"
#include "vector.h"

namespace std {

  void GenerateParameterLJ612Cut(UniqueParameter* prm) {
    double r0rc,r0rc6,r06,rc6;
    r06=prm[LJ612CutEqRadius].d;
    rc6=prm[LJ612CutCutR].d;
    r0rc=r06/rc6;
    r06*=r06*r06;   r06*=r06;
    rc6*=rc6*rc6;   rc6*=rc6;
    r0rc6=r06/rc6;
    prm[LJ612CutRealSigma6]=r06*(1-r0rc6*r0rc)/(1-r0rc6*r0rc6*r0rc);
    double sgrc6=prm[LJ612CutRealSigma6].d/rc6;
    prm[LJ612CutVc]=sgrc6*(sgrc6-2.);
    prm[LJ612CutKc]=12*sgrc6*(1.-sgrc6)/prm[LJ612CutCutR].d;
    double sgr06=prm[LJ612CutRealSigma6].d/r06;
    double e,tmd;
    e=sgro6*(sgr06-2.);
    e-=prm[LJ612CutVc].d;
    e-=prm[LJ612CutKc].d*(prm[LJ612CutEqRadius].d-prm[LJ612CutCutR]);
    tmd=-1./e;
    prm[LJ612CutRealStrength]=tmd;
    prm[LJ612CutVc]*=tmd;
    prm[LJ612CutKc]*=tmd;
    prm[LJ612CutTwlfRealStrength]=12*tmd;
  }

  void GenerateParameterLJ612Cut(Vector<UniqueParameter>& prm) {
    assert(prm.size>=LJ612CutNumberParameter);
    GenerateParameterLJ612Cut(prm());
  }

}

#endif

