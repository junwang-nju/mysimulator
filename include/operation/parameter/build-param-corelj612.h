
#ifndef _Build_Parameter_CoreLJ612_H_
#define _Build_Parameter_CoreLJ612_H_

#include "data/name/parameter-corelj612.h"
#include "operation/parameter/build-param-lj612.h"

namespace std {

  void BuildParameterCoreLJ612(UniqueParameter* prm) {
    BuildParameterLJ612(prm);
  }

  void BuildParameterCoreLJ612(Vector<UniqueParameter>& prm) {
    BuildParameterLJ612(prm);
  }

}

#endif

