
#ifndef _Parameter_Name_Core12_H_
#define _Parameter_Name_Core12_H_

namespace std {

  enum Core12ParameterName {
    Core12EqStrength=0,
    Core12TwlfEqStrength,
    Core12NumberParameter
  };

}

#include "unique-parameter.h"
#include "vector.h"
#include <cassert>

namespace std {

  void GenerateParameterCore12(UniqueParameter* prm) {
    prm[Core12TwlfEqStrength]=prm[Core12EqStrength].d*12;
  }

  void GenerateParameterCore12(Vector<UniqueParameter>& prm) {
    assert(prm.size>=Core12NumberParameter);
    GenerateParameterCore12(prm());
  }

}

#endif

