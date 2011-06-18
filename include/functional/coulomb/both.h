
#ifndef _Functional_Coulomb_Both_H_
#define _Functional_Coulomb_Both_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/coulomb/parameter/name.h"
#include "intrinsic-type/sqroot.h"

namespace mysimulator {

  template <typename T>
  void BothCoulomb(const T& dsq,const UniqueParameter64Bit* prm,T& fc,T& df) {
    T ivd2=1./dsq;
    T ivd=sqroot(ivd2);
    fc=prm[CoulombStrength].value<T>()*ivd;
    df=-fc*ivd2;
  }

}

#endif

