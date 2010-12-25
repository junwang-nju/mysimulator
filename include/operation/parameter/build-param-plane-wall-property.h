
#ifndef _Build_Parameter_Plane_Wall_Property_H_
#define _Build_Parameter_Plane_Wall_Property_H_

#include "data/basic/unique-parameter.h"
#include "data/name/plane-wall-property.h"

namespace std {

  template <typename T>
  void BuildParameterPlaneWallProperty(UniqueParameter* prm) {
    T tmvalue;
    Vector<T>& tmv=
      *reinterpret_cast<Vector<T>*>(prm[PlaneWallNormalDirectionPointer].ptr);
    tmvalue=norm(tmv);
    assert(tmvalue>1e-8);
    scale(tmv,1./tmvalue);
  }

  template <typename T>
  void BuildParameterPlaneWallProperty(Vector<UniqueParameter>& prm) {
    assert(prm.size>=PlaneWallPropertyNumberParameter);
    BuildParameterPlaneWallProperty<T>(prm.data);
  }
}

#endif
