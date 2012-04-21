
#ifndef _Intrinsic_Type_Inverse_H_
#define _Intrinsic_Type_Inverse_H_

#ifndef _INV
#define _INV(type) \
  void Inverse(type& d) { d=1./d; }
#else
#error "Duplicate Definition of Macro _INV"
#endif

namespace mysimulator {

  _INV(double)
  _INV(float)

}

#ifdef _INV
#undef _INV
#endif

#endif

