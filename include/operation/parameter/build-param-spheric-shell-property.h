
#ifndef _Build_Parameter_Spheric_Shell_Property_H_
#define _Build_Parameter_Spheric_Shell_Property_H_

#include "data/basic/unique-parameter.h"
#include "data/name/spheric-shell-property.h"

namespace std {

  template <typename T>
  void BuildParameterSphericShellProperty(UniqueParameter* prm) {
    prm[SphericShellDirection].value<T>()=
        (prm[SphericShellDirection].value<T>()>=0?1:-1);
    prm[SphericShellRadiusSQ].value<T>()=
        prm[SphericShellRadius].value<T>()*prm[SphericShellRadius].value<T>();
  }

  template <typename T>
  void BuildParameterSphericShellProperty(Vector<UniqueParameter>& prm) {
    assert(prm.size>=SphericShellPropertyNumberParameter);
    BuildParameterSphericShellProperty<T>(prm.data);
  }

}

#endif
