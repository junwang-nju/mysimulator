
#ifndef _Intrinsic_Type_Inverse_H_
#define _Intrinsic_Type_Inverse_H_

#include "intrinsic-type/constant.h"

#define _INV(type) \
  void inverse(type& d) { d=ValueOne<type>()/d; }

namespace mysimulator {

  _INV(double)
  _INV(float)

}

#undef _INV

#endif

