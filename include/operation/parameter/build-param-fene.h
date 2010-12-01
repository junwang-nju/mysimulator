
#ifndef _Build_Parameter_FENE_H_
#define _Build_Parameter_FENE_H_

#include "data/name/parameter-fene.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void BuildParameterFENE(UniqueParameter* prm) {
    copy(prm[FENEHalfStrength],0.5*prm[FENEStrength].value<T>());
    T d=prm[FENEDeltaRadiusMax].value<T>(),dd=d*d;
    copy(prm[FENEDeltaRadiusMaxSQ],dd);
    copy(prm[FENEIvDeltaRadiusMaxSQ],1./dd);
    copy(prm[FENEStrengthDRadiusSQ],prm[FENEStrength].value<T>()*dd);
    copy(prm[FENEHalfStrengthDRadiusSQ],prm[FENEHalfStrength].value<T>()*dd);
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterFENE(Vector<UniqueParameter>& prm) {
    assert(prm.size>=FENENumberParameter);
    BuildParameterFENE<T>(prm.data);
  }

}

#endif
