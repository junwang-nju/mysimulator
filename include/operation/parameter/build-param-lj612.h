
#ifndef _Build_Parameter_LJ612_H_
#define _Build_Parameter_LJ612_H_

#include "data/name/lj612.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void BuildParameterLJ612(UniqueParameter* prm) {
    copy(prm[LJ612EqRadiusSQ],
         prm[LJ612EqRadius].value<T>()*prm[LJ612EqRadius].value<T>());
    copy(prm[LJ612TwlfEqEnergyDepth],12*prm[LJ612EqEnergyDepth].value<T>());
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterLJ612(Vector<UniqueParameter>& prm) {
    assert(prm.size>=LJ612NumberParameter);
    BuildParameterLJ612<T>(prm.data);
  }

}

#endif

