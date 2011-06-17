
#ifndef _Functional_Core12_Both_H_
#define _Functional_Core12_Both_H_

#include "unique-parameter/64bit/interface.h"
#include "functional/core12/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BothCore12(const T& dsq, const UniqueParameter64Bit* prm, T& fc,T& df) {
    T ivr2=1./dsq;
    T ivr6=ivr2*ivr2*ivr2;
    T ivr12=ivr6*ivr6;
    fc=prm[Core12EqStrength].value<T>()*ivr12;
    df=-prm[Core12TwlfEqStrength].value<T>()*ivr12*ivr2;
  }

}

#endif

