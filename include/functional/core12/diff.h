
#ifndef _Functional_Core12_Diff_H_
#define _Functional_Core12_Diff_H_

#include "functional/core12/parameter/name.h"
#include "unique-parameter/64bit/interface.h"

namespace mysimulator {

  template <typename T>
  void DiffCore12(const T& dsq, const UniqueParameter64Bit* prm, T& diff) {
    T ivr2=1./dsq;
    T ivr6=ivr2*ivr2*ivr2;
    T ivr12=ivr6*ivr6;
    diff=-prm[Core12TwlfEqStrength].value<T>()*ivr12*ivr2;
  }

}

#endif

