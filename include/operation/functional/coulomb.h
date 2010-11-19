
#ifndef _Functional_Coulomb_H_
#define _Functional_Coulomb_H_

#include "data/name/parameter-coulomb.h"
#include <cmath>

namespace std {

  template <typename T>
  void FuncCoulomb(const T& dsq, const UniqueParameter* prm, T& func) {
    func=prm[CoulombStrength]<T>()/sqrt(dsq));
  }

  template <typename T>
  void DiffCoulomb(const T& dsq, const UniqueParameter* prm, T& diff) {
    T d=sqrt(dsq)*dsq;
    diff=-prm[CoulombStrength]<T>()/d;
  }

  template <typename T>
  void BothCoulomb(const T& dsq, const UniqueParameter* prm, T& diff) {
    T ivd2=1./dsq;
    T ivd=sqrt(ivd2);
    func=prm[CoulombStrength]<T>()*ivd;
    diff=-func*ivd2;
  }

}

#endif
