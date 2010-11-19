
#ifndef _Build_Parameter_LJ1012_H_
#define _Build_Parameter_LJ1012_H_

#include "data/name/parameter-lj612.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void BuildParameterLJ1012(UniqueParameter* prm) {
    copy(prm[LJ1012EqRadiusSQ],
         prm[LJ1012EqRadius]<T>()*prm[LJ1012EqRadius]<T>());
    copy(prm[LJ1012SixtyEqEnergyDepth],prm[LJ1012EqEnergyDepth]<T>()*60);
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterLJ1012(Vector<UniqueParameter>& prm) {
    assert(prm.size>=LJ1012NumberParameter);
    BuildParameterLJ1012<T>(prm.data);
  }

}

#endif

