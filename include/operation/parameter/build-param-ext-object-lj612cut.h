
#ifndef _Build_Parameter_External_Object_LJ612Cut_H_
#define _Build_Parameter_External_Object_LJ612Cut_H_

#include "data/name/external-object-lj612cut.h"
#include "operation/parameter/build-param-lj612cut.h"

namespace std {

  template <typename T>
  void BuildParameterExtObjLJ612Cut(UniqueParameter* prm) {
    BuildParameterLJ612Cut<T>(prm+ExtObjectBaseNumberParameter);
  }

  template <typename T>
  void BuildParameterExtObjLJ612Cut(Vector<UniqueParameter>& prm) {
    assert(prm.size>=ExtObjLJ612CutNumberParameter);
    BuildParameterExtObjLJ612Cut<T>(prm.data);
  }

}

#endif
