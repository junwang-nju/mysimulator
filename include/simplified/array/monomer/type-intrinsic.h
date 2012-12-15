
#ifndef _Array_Monomer_Type_Intrinsic_H_
#define _Array_Monomer_Type_Intrinsic_H_

#include "array/monomer/type-def.h"

namespace mysimulator {

  template <typename T> class Intrinsic;

  template <typename T>
  class __array_monomer<Intrinsic<T>> { public: typedef T Type; };

}


#endif

