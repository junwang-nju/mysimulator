
#ifndef _Build_Parameter_External_Object_Harmonic_H_
#define _Build_Parameter_External_Object_Harmonic_H_

#include "data/name/external-object-harmonic.h"
#include "operation/parameter/build-param-harmonic.h"

namespace std {

  template <typename T>
  void BuildParameterExtObjHarmonic(UniqueParameter* prm) {
    BuildParameterHarmonic<T>(prm+ExtObjectBaseNumberParameter);
  }

  template <typename T>
  void BuildParameterExtObjHarmonic(Vector<UniqueParameter>& prm) {
    assert(prm.size>=ExtObjHarmonicNumberParameter);
    BuildParameterExtObjHarmonic<T>(prm.data);
  }

}

#endif

