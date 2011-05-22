
#ifndef _Vector_State_Name_H_
#define _Vector_State_Name_H_

namespace mysimulator {

  enum VectorStateName {
    UnusedVector,
    AllocatedVector,
    SubVector
  };

}

#include "intrinsic-type/single-operation-type.h"

namespace mysimulator {

  template <>
  struct _SingleOp<VectorStateName> { typedef VectorStateName Type; };

}

#endif

