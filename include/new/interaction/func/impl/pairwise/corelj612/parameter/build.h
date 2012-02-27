
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Build_H_

#include "interaction/func/impl/pairwise/corelj612/parameter/name.h"
#include "interaction/func/impl/pairwise/lj612/parameter/build.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCoreLJ612(Unique64Bit* prm) {
    BuildParameterLJ612<T>(prm);
  }

  template <typename T>
  void BuildParameterCoreLJ612(Array1DContent<Unique64Bit>& prm) {
    BuildParameterLJ612<T>(prm);
  }

}

#endif

