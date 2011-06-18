
#ifndef _Functional_CoreLJ612_Parameter_Build_H_
#define _Functional_CoreLJ612_Parameter_Build_H_

#include "functional/lj612/parameter/build.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCoreLJ612(UniqueParameter64Bit* prm) {
    BuildParameterLJ612<T>(prm);
  }

  template <typename T>
  void BuildParameterCoreLJ612(Vector<UniqueParameter64Bit>& prm) {
    BuildParameterLJ612<T>(prm);
  }

}

#endif

