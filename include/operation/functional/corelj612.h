
#ifndef _Functiona_CoreLJ612_H_
#define _Functiona_CoreLJ612_H_

#include "operation/parameter/build-param-corelj612.h"
#include "operation/functional/lj612.h"

namespace std {

  template <typename T>
  void FuncCoreLJ612(const T& dsq, const UniqueParameter* prm, T& func) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  func=0.;
    else {
      FuncLJ612(dsq,prm,func);
      func+=prm[CoreLJ612EnergyDepth].d;
    }
  }

  template <typename T>
  void DiffCoreLJ612(const T& dsq, const UniqueParameter* prm, T& diff) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  diff=0.;
    else DiffLJ612(dsq,prm,diff);
  }

  template <typename T>
  void BothCoreLJ612(const T& dsq, const UniqueParameter* prm,
                     T& func, T& diff) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  diff=0.;
    else {
      BothLJ612(dsq,prm,func,diff);
      func+=prm[CoreLJ612EnergyDepth].d;
    }
  }

}

#endif

