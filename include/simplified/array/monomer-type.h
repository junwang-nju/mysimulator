
#ifndef _Array_Monomer_Type_H_
#define _Array_Monomer_Type_H_

namespace mysimulator {

  template <typename T>
  class __array_monomer { public: typedef T Type; };

}

#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename T>
  class __array_monomer<Intrinsic<T>> { public: typedef T Type; };

}

#endif

