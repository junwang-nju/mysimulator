
#ifndef _Build_Parameter_LJ1012Cut_H_
#define _Build_Parameter_LJ1012Cut_H_

#include "data/name/parameter-lj1012cut.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void BuildParameterLJ1012Cut(UniqueParameter* prm) {
    T r0rc2,r0rcTEN,r0rcTLF,r02,rc2;
    rc2=prm[LJ1012CutCutR].value<T>();
    rc2*=rc2;
    copy(prm[LJ1012CutCutRSQ],rc2);
    r02=prm[LJ1012CutEqRadius].value<T>();
    r02*=r02;
    r0rc2=r02/rc2;
    r0rcTEN=r0rc2*r0rc2;
    r0rcTEN*=r0rcTEN;
    r0rcTEN*=r0rc2;
    r0rcTLF=r0rcTEN*r0rc2;
    copy(prm[LJ1012CutRealRadiusSQ],r02*(r0rcTEN*r0rc-1.)/(r0rcTLF*r0rc-1.));
    T sgrc2,sgrcTEN,sgrcTLF;
    sgrc2=prm[LJ1012CutRealRadiusSQ].value<T>()/rc2;
    sgrcTEN=sgrc2*sgrc2;
    sgrcTEN*=sgrcTEN;
    sgrcTEN*=sgrc2;
    sgrcTLF=sgrcTEN*sgrc2;
    copy(prm[LJ1012CutVc],5*(sgrcTLF-sgrcTEN)-sgrcTEN);
    copy(prm[LJ1012CutKc],-60*(sgrcTLF-sgrcTEN)/prm[LJ1012CutCutR].value<T>());
    T sgr0TEN,sgr0TLF,e0,tmd;
    sgr0TEN=sgrcTEN/r0rcTEN;
    sgr0TLF=sgrcTLF/r0rcTLF;
    e0=5*(sgr0TLF-sgr0TEN)-sgr0TEN;
    e0-=prm[LJ1012CutVc].value<T>();
    e0-=prm[LJ1012CutKc].value<T>()
        *(prm[LJ1012CutEqRadius].value<T>()-prm[LJ1012CutCutR].value<T>());
    tmd=-prm[LJ1012CutEqEnergyDepth].value<T>()/e0;
    copy(prm[LJ1012CutRealEnergyDepth],tmd);
    prm[LJ1012CutVc].value<T>()*=tmd;
    prm[LJ1012CutKc].value<T>()*=tmd;
    copy(prm[LJ1012CutSixtyRealEnergyDepth],60*tmd);
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterLJ1012Cut(Vector<UniqueParameter>& prm) {
    assert(prm.size>=LJ1012CutNumberParameter);
    BuildParameterLJ1012Cut<T>(prm.data);
  }

}

#endif

