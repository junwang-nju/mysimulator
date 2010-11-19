
#ifndef _Interaction_H_
#define _Interaction_H_

#include "data/basic/vector.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <>
  struct Interaction : public Vector<UniqueParameter> {
  };

}

#endif

