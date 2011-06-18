
#ifndef _Functional_Coulomb_Diff_H_
#define _Functional_Coulomb_Diff_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/coulomb/parameter/name.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  void DiffCoulomb(const T& dsq,const UniqueParameter64Bit* prm,T& diff) {
    T d3=dsq*sqroot(dsq);
    diff=-prm[CoulombStrength].value<T>()/d3;
  }

}

#endif

