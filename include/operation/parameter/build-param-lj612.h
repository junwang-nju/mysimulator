
#ifndef _Build_Parameter_LJ612_H_
#define _Build_Parameter_LJ612_H_

#include "data/name/parameter-lj612.h"
#include "data/basic/unique-parameter.h"

namespace std {

  void BuildParameterLJ612(UniqueParameter* prm) {
    copy(prm[LJ612EqRadiusSQ],prm[LJ612EqRadius].d*prm[LJ612EqRadius].d);
    copy(prm[LJ612TwlfEqEnergyDepth],12*prm[LJ612EqEnergDepth].d);
  }

}

#include "data/basic/vector.h"

namespace std {

  void BuildParameterLJ612(Vector<UniqueParameter>& prm) {
    assert(prm.size>=LJ612NumberParameter);
    BuildParameterLJ612(prm.data);
  }

}

#endif

