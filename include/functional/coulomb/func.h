
#ifndef _Functional_Coulomb_Func_H_
#define _Functional_Coulomb_Func_H_

#include "functional/coulomb/parameter/name.h"
#include "unique-parameter/64bit/interface.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  void FuncCoulomb(const T& dsq,const UniqueParameter64Bit* prm,T& func) {
    func=prm[CoulombStrength].value<T>()/sqroot(dsq);
  }

}

#endif

