
#ifndef _Interaction_Func_Implement_LJ1012Cut_Paramete_Build_H_
#define _Interaction_Func_Implement_LJ1012Cut_Paramete_Build_H_

#include "interaction/func/impl/lj1012cut/parameter/name.h"
#include "unique/64bit/copy.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012Cut(Unique64Bit* prm) {
    T r0rc,r0rc2,r0rc10,r0rc12,r02,rc2;
    rc2=prm[LJ1012CutCutR].value<T>();
    r02=prm[LJ1012CutEqRadius].value<T>();
    r0rc=r02/rc2;
    rc2*=rc2;
    copy(prm[LJ1012CutCutRSQ],rc2);
    r02*=r02;
    r0rc2=r0rc*r0rc;
    r0rc10=r0rc2*r0rc2;
    r0rc10*=r0rc10;
    r0rc10*=r0rc2;
    r0rc12=r0rc10*r0rc2;
    copy(prm[LJ1012CutRealRadiusSQ],r02*(r0rc10*r0rc-1.)/(r0rc12*r0rc-1.));
    T sgrc2,sgrc10,sgrc12;
    sgrc2=prm[LJ1012CutRealRadiusSQ].value<T>()/rc2;
    sgrc10=sgrc2*sgrc2;
    sgrc10*=sgrc10;
    sgrc10*=sgrc2;
    sgrc12=sgrc10*sgrc2;
    copy(prm[LJ1012CutVc],5*(sgrc12-sgrc10)-sgrc10);
    copy(prm[LJ1012CutKc],-60*(sgrc12-sgrc10)/prm[LJ1012CutCutR].value<T>());
    T sgr010,sgr012;
    sgr010=sgrc10/r0rc10;
    sgr012=sgrc12/r0rc12;
    T e0,tmd;
    e0=5*(sgr012-sgr010)-sgr010;
    e0-=prm[LJ1012CutVc].value<T>();
    e0-=prm[LJ1012CutKc].value<T>()*(prm[LJ1012CutEqRadius].value<T>()-
                                     prm[LJ1012CutCutR].value<T>());
    tmd=-prm[LJ1012CutEqEnergyDepth].value<T>()/e0;
    copy(prm[LJ1012CutRealEnergyDepth],tmd);
    prm[LJ1012CutVc].value<T>()*=tmd;
    prm[LJ1012CutKc].value<T>()*=tmd;
    copy(prm[LJ1012CutSixtyRealEnergyDepth],60*tmd);
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012Cut(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>LJ1012CutNumberParameter);
    BuildParameterLJ1012Cut<T>(prm.start);
  }

}

#endif

