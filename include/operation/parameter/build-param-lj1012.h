
#ifndef _Build_Parameter_LJ1012_H_
#define _Build_Parameter_LJ1012_H_

#include "data/name/parameter-lj612.h"
#include "data/basic/unique-parameter.h"

namespace std {

  void BuildParameterLJ1012(UniqueParameter* prm) {
    copy(prm[LJ1012EqRadiusSQ],prm[LJ1012EqRadius].d*prm[LJ1012EqRadius].d);
    copy(prm[LJ1012SixtyEqEnergyDepth],prm[LJ1012EqEnergyDepth].d*60);
  }

}

#include "data/basic/vector.h"

namespace std {

  void BuildParameterLJ1012(Vector<UniqueParameter>& prm) {
    assert(prm.size>=LJ1012NumberParameter);
    BuildParameterLJ1012(prm.data);
  }

}

#endif

