
#ifndef _Functiona_CoreLJ612_H_
#define _Functiona_CoreLJ612_H_

#include "operation/parameter/build-param-corelj612.h"
#include "operation/functional/lj612.h"

namespace std {

  void FuncCoreLJ612(const double dsq, const UniqueParameter* prm,
                     double& func) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  func=0.;
    else {
      FuncLJ612(dsq,prm,func);
      func+=prm[CoreLJ612EnergyDepth].d;
    }
  }

  void DiffCoreLJ612(const double dsq, const UniqueParameter* prm,
                     double& diff) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  diff=0.;
    else DiffLJ612(dsq,prm,diff);
  }

  void BothCoreLJ612(const double dsq, const UniqueParameter* prm,
                     double& func, double& diff) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  diff=0.;
    else {
      BothLJ612(dsq,prm,func,diff);
      func+=prm[CoreLJ612EnergyDepth].d;
    }
  }

}

#endif

