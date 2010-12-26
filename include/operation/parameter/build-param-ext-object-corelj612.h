
#ifndef _Build_Parameter_External_Object_CoreLJ612_H_
#define _Build_Parameter_External_Object_CoreLJ612_H_

#include "data/name/external-object-corelj612.h"
#include "operation/parameter/build-param-corelj612.h"

namespace std {

  template <typename T>
  void BuildParameterExtObjCoreLJ612(UniqueParameter* prm) {
    BuildParameterCoreLJ612<T>(prm+ExtObjectBaseNumberParameter);
  }

  template <typename T>
  void BuildParameterExtObjCoreLJ612(Vector<UniqueParameter>& prm) {
    assert(prm.size>=ExtObjCoreLJ612NumberParameter);
    BuildParameterExtObjCoreLJ612<T>(prm.data);
  }

}

#endif
