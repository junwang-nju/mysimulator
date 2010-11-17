
#ifndef _Build_Parameter_LJ1012Cut_H_
#define _Build_Parameter_LJ1012Cut_H_

#include "data/name/parameter-lj1012cut.h"
#include "data/basic/unique-parameter.h"

namespace std {

  void BuildParameterLJ1012Cut(UniqueParameter* prm) {
    double r0rc2,r0rcTEN,r0rcTLF,r02,rc2;
    rc2=prm[LJ1012CutCutR].d;
    rc2*=rc2;
    copy(prm[LJ1012CutCutRSQ],rc2);
    r02=prm[LJ1012CutEqRadius].d
    r02*=r02;
    r0rc2=r02/rc2;
    r0rcTEN=r0rc2*r0rc2;
    r0rcTEN*=r0rcTEN;
    r0rcTEN*=r0rc2;
    r0rcTLF=r0rcTEN*r0rc2;
    copy(prm[LJ1012CutRealRadiusSQ],r02*(r0rcTEN*r0rc-1.)/(r0rcTLF*r0rc-1.));
    double sgrc2,sgrcTEN,sgrcTLF;
    sgrc2=prm[LJ1012CutRealRadiusSQ].d/rc2;
    sgrcTEN=sgrc2*sgrc2;
    sgrcTEN*=sgrcTEN;
    sgrcTEN*=sgrc2;
    sgrcTLF=sgrcTEN*sgrc2;
    copy(prm[LJ1012CutVc],5*(sgrcTLF-sgrcTEN)-sgrcTEN);
    copy(prm[LJ1012CutKc],-60*(sgrcTLF-sgrcTEN)/prm[LJ1012CutCutR].d);
    double sgr0TEN,sgr0TLF,e0,tmd;
    sgr0TEN=sgrcTEN/r0rcTEN;
    sgr0TLF=sgrcTLF/r0rcTLF;
    e0=5*(sgr0TLF-sgr0TEN)-sgr0TEN;
    e0-=prm[LJ1012CutVc].d;
    e0-=prm[LJ1012CutKc].d*(prm[LJ1012CutEqRadius].d-prm[LJ1012CutCutR].d);
    tmd=-prm[LJ1012CutEqEnergyDepth].d/e0;
    copy(prm[LJ1012CutRealEnergyDepth],tmd);
    prm[LJ1012CutVc].d*=tmd;
    prm[LJ1012CutKc].d*=tmd;
    prm[LJ1012CutSixtyRealEnergyDepth].d=60*tmd;
  }

}

#include "data/basic/vector.h"

namespace std {

  void BuildParameterLJ1012Cut(Vector<UniqueParameter>& prm) {
    assert(prm.size>=LJ1012CutNumberParameter);
    BuildParameterLJ1012Cut(prm.data);
  }

}

#endif

