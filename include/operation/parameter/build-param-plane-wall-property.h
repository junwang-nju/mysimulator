
#ifndef _Build_Parameter_Plane_Wall_Property_H_
#define _Build_Parameter_Plane_Wall_Property_H_

#include "data/basic/unique-parameter.h"

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

}

#endif
