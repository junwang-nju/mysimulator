
#ifndef _Parameter_Name_FENE_H_
#define _Parameter_Name_FENE_H_

namespace std {

  enum FENEParameterName {
    FENEStrength=0,
    FENEBoundLength,
    FENEHalfStrength,
    FENEBoundLengthSQ,
    FENEIvBoundLengthSQ,
    FENEHalfStrengthLengthSQ,
    FENENumberParameter
  };

}

#include "unique-parameter.h"
#include "vector.h"

namespace std {

  void GenerateParameterFENE(UniqueParameter* prm) {
    prm[FENEHalfStrength]=0.5*prm[FENEStrength].d;
    prm[FENEBoundLengthSQ]=prm[FENEBoundLength].d*prm[FENEBoundLength].d;
    prm[FENEIvBoundLengthSQ]=1./prm[FENEBoundLengthSQ].d;
    prm[FENEHalfStrengthLengthSQ]=prm[FENEHalfStrength].d*
                                  prm[FENEBoundLengthSQ].d;
  }

  void GenerateParameterFENE(Vector<UniqueParameter>& prm) {
    assert(prm.size>=FENENumberParameter);
    GenerateParameterFENE(prm());
  }

}

#endif
