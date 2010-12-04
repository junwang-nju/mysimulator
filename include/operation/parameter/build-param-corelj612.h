
#ifndef _Build_Parameter_CoreLJ612_H_
#define _Build_Parameter_CoreLJ612_H_

#include "data/name/corelj612.h"
#include "operation/parameter/build-param-lj612.h"

namespace std {

  template <typename T>
  void BuildParameterCoreLJ612(UniqueParameter* prm) {
    BuildParameterLJ612<T>(prm);
  }

  template <typename T>
  void BuildParameterCoreLJ612(Vector<UniqueParameter>& prm) {
    BuildParameterLJ612<T>(prm);
  }

}

#endif

