
#ifndef _Referable_Object_State_Name_H_
#define _Referable_Object_State_Name_H_

namespace mysimulator {

  enum ObjectStateName {
    Unused,
    Referred,
    Allocated
  };

}

#include "intrinsic-type/single-operation-type.h"

namespace mysimulator {

  template <>
  struct _SingleOp<ObjectStateName> { typedef ObjectStateName Type; };

}

#endif

