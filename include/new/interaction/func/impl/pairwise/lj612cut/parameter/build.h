
#ifndef _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_LJ612Cut_Parameter_Build_H_

#include "interaction/func/impl/pairwise/lj612cut/parameter/name.h"
#include "unique/64bit/copy.h"
#include "intrinsic-type/square.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612Cut(Unique64Bit* prm) {
    T r0rc,r0rc6,r06,rc6;
    r06=prm[LJ612CutEqRadius].value<T>();
    rc6=prm[LJ612CutCutR].value<T>();
    r0rc=r06/rc6;
    r06*=square(r06);   r06*=r06;
    rc6*=rc6;
    copy(prm[LJ612CutCutRSQ],rc6);
    rc6*=square(rc6);
    r0rc6=r06/rc6;
    T r0rc7=r0rc6*r0rc;
    copy(prm[LJ612CutRealSigma6],r06*(1-r0rc7)/(1-r0rc6*r0rc7));
    T sgrc6=prm[LJ612CutRealSigma6].value<T>()/rc6;
    T sgrc12=sgrc6*sgrc6;
    copy(prm[LJ612CutVc],sgrc12-sgrc6-sgrc6);
    T tmd;
    tmd=(sgrc6-sgrc12)/prm[LJ612CutCutR].value<T>();
    tmd+=tmd+tmd;
    tmd+=tmd;
    copy(prm[LJ612CutKc],tmd+tmd);
    T sgr06=sgrc6/r0rc6;
    T e;
    e=sgr06*(sgr06-2.);
    e-=prm[LJ612CutVc].value<T>();
    e-=prm[LJ612CutKc].value<T>()*(prm[LJ612CutEqRadius].value<T>()-
       prm[LJ612CutCutR].value<T>());
    e=-prm[LJ612CutEqEnergyDepth].value<T>()/e;
    copy(prm[LJ612CutRealStrength],e);
    prm[LJ612CutVc].value<T>()*=e;
    prm[LJ612CutKc].value<T>()*=e;
    tmd=e+e+e;
    tmd+=tmd;
    copy(prm[LJ612CutTwlfRealStrength],tmd+tmd);
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612Cut(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>=LJ612CutNumberParameters);
    BuildParameterLJ612Cut<T>(prm.start);
  }

}

#endif

