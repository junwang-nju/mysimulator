
#ifndef _Functional_LJ612Cut_Parameter_Build_H_
#define _Functional_LJ612Cut_Parameter_Build_H_

#include "unique-parameter/64bit/copy.h"
#include "functional/lj612cut/parameter/name.h"
#include "intrinsic-type/square.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612Cut(UniqueParameter64Bit* prm) {
    T r0rc,r0rc6,r06,rc6;
    r06=prm[LJ612CutEqRadius].value<T>();
    rc6=prm[LJ612CutCutR].value<T>();
    r0rc=r06/rc6;
    r06*=square(r06);
    r06*=r06;
    rc6*=rc6;
    copy(prm[LJ612CutCutRSq],rc6);
    rc6*=square(rc6);
    r0rc6=r06/rc6;
    copy(prm[LJ612CutRealSigma6],r06*(1-r0rc6*r0rc)/(1-square(r0rc6)*r0rc));
    double sgrc6=prm[LJ612CutRealSigma6].value<T>()/rc6;
    copy(prm[LJ612CutVc],sgrc6*(sgrc6-2.));
    copy(prm[LJ612CutKc],12*sgrc6*(1.-sgrc6)/prm[LJ612CutCutR].value<T>());
    T sgr06=sgrc6/r0rc6;
    T e;
    e=sgr06*(sgr06-2.);
    e-=prm[LJ612CutVc].value<T>();
    e-=prm[LJ612CutKc].value<T>()*
       (prm[LJ612CutEqRadius].value<T>()-prm[LJ612CutCutR].value<T>());
    e=-prm[LJ612CutEqEnergyDepth].value<T>()/e;
    copy(prm[LJ612CutRealStrength],e);
    prm[LJ612CutVc].value<T>()*=e;
    prm[LJ612CutKc].value<T>()*=e;
    copy(prm[LJ612CutTwlfRealStrength],12*e);
  }

}

#include "vector/interface.h"

namespace mysimulator {

  template<typename T>
  void BuildParameterLJ612Cut(Vector<UniqueParameter64Bit>& prm) {
    assert(prm.size>=LJ612CutNumberParameter);
    BuildParameterLJ612Cut<T>(prm.pdata);
  }

}

#endif

