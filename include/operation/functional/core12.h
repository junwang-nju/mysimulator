
#ifndef _Functional_Core12_H_
#define _Functional_Core12_H_

#include "data/name/parameter-core12.h"

namespace std {

  template <typename T>
  void FuncCore12(const T& dsq, const UniqueParameter* prm, T& func) {
    T tmd=1./dsq;
    tmd*=tmd*tmd;
    tmd*=tmd;
    func=prm[Core12EqStrength].d*tmd;
  }

  template <typename T>
  void DiffCore12(const T& dsq, const UniqueParameter* prm, T& diff) {
    T tmd=1./dsq;
    T tmd2=tmd*tmd;
    tmd2*=tmd2*tmd2;
    diff=-prm[Core12TwlfEqStrength].d*tmd*tmd2;
  }

  template <typename T>
  void BothCore12(const T& dsq, const UniqueParameter* prm, T& func, T& diff) {
    T tmd=1./dsq;
    T tmd2=tmd*tmd;
    tmd2*=tmd2*tmd2;
    func=prm[Core12EqStrength].d*tmd2;
    diff=-prm[Core12TwlfEqStrength].d*tmd*tmd2;
  }

}

#endif

