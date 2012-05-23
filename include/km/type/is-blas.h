
#ifndef _Type_IsBlas_H_
#define _Type_IsBlas_H_

namespace mysimulator {

  template <typename T>
  class IsBlasableFlag { public: static const bool Flag; };

  template <typename T>
  const bool IsBlasableFlag<T>::Flag=false;

  template <> const bool IsBlasableFlag<double>::Flag=true;
  template <> const bool IsBlasableFlag<float>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsBlasable {
    public:
      typedef typename Check<IsBlasableFlag<T>::Flag>::Type   Type;
  };

}

#endif

