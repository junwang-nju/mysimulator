
#ifndef _Functional_Coulomb_H_
#define _Functional_Coulomb_H_

#include "data/name/coulomb.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void FuncCoulomb(const T& dsq, const UniqueParameter* prm, T& func) {
    func=prm[CoulombStrength].value<T>()/sqroot(dsq);
  }

  template <typename T>
  void DiffCoulomb(const T& dsq, const UniqueParameter* prm, T& diff) {
    T d=sqroot(dsq)*dsq;
    diff=-prm[CoulombStrength].value<T>()/d;
  }

  template <typename T>
  void BothCoulomb(const T& dsq, const UniqueParameter* prm, T& func, T& diff) {
    T ivd2=1./dsq;
    T ivd=sqroot(ivd2);
    func=prm[CoulombStrength].value<T>()*ivd;
    diff=-func*ivd2;
  }

}

#endif
