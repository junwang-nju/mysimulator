
#ifndef _Build_Parameter_Shifted_FENE_H_
#define _Build_Parameter_Shifted_FENE_H_

#include "data/name/shifted-fene.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void BuildParameterShiftedFENE(UniqueParameter* prm) {
    copy(prm[SfFENEHalfStrength],0.5*prm[SfFENEStrength].value<T>());
    T d=prm[SfFENEDeltaRadiusMax].value<T>(),dd=d*d;
    copy(prm[SfFENEDeltaRadiusMaxSQ],dd);
    copy(prm[SfFENEIvDeltaRadiusMaxSQ],1./dd);
    copy(prm[SfFENEStrengthDRadiusSQ],prm[SfFENEStrength].value<T>()*dd);
    copy(prm[SfFENEHalfStrengthDRadiusSQ],
         prm[SfFENEHalfStrength].value<T>()*dd);
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterShiftedFENE(Vector<UniqueParameter>& prm) {
    assert(prm.size>=SfFENENumberParameter);
    BuildParameterShiftedFENE<T>(prm.data);
  }

}

#endif
