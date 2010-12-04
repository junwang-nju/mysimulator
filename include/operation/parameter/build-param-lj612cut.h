
#ifndef _Build_Parameter_LJ612Cut_H_
#define _Build_Parameter_LJ612Cut_H_

#include "data/name/lj612cut.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void BuildParameterLJ612Cut(UniqueParameter* prm) {
    T r0rc,r0rc6,r06,rc6;
    r06=prm[LJ612CutEqRadius].value<T>();
    rc6=prm[LJ612CutCutR].value<T>();
    r0rc=r06/rc6;
    r06*=r06*r06;   r06*=r06;
    rc6*=rc6;
    copy(prm[LJ612CutCutRSQ],rc6);
    rc6*=rc6*rc6;
    r0rc6=r06/rc6;
    copy(prm[LJ612CutRealSigma6],r06*(1-r0rc6*r0rc)/(1-r0rc6*r0rc6*r0rc));
    double sgrc6=prm[LJ612CutRealSigma6].value<T>()/rc6;
    copy(prm[LJ612CutVc],sgrc6*(sgrc6-2.));
    copy(prm[LJ612CutKc],12*sgrc6*(1.-sgrc6)/prm[LJ612CutCutR].value<T>());
    T sgr06=prm[LJ612CutRealSigma6].value<T>()/r06;
    T e,tmd;
    e=sgr06*(sgr06-2.);
    e-=prm[LJ612CutVc].value<T>();
    e-=prm[LJ612CutKc].value<T>()
       *(prm[LJ612CutEqRadius].value<T>()-prm[LJ612CutCutR].value<T>());
    tmd=-prm[LJ612CutEqEnergyDepth].value<T>()/e;
    copy(prm[LJ612CutRealStrength],tmd);
    prm[LJ612CutVc].value<T>()*=tmd;
    prm[LJ612CutKc].value<T>()*=tmd;
    copy(prm[LJ612CutTwlfRealStrength],12*tmd);
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterLJ612Cut(Vector<UniqueParameter>& prm) {
    assert(prm.size>=LJ612CutNumberParameter);
    BuildParameterLJ612Cut<T>(prm.data);
  }

}

#endif

