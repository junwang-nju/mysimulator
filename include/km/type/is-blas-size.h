
#ifndef _Type_IsBlasSize_H_
#define _Type_IsBlasSize_H_

namespace mysimulator {

  template <typename T>
  class IsBlasSizeFlag { static const bool Flag; };

  template <typename T>
  const bool IsBlasSizeFlag<T>::Flag=
    (sizeof(double)==sizeof(T))||(sizeof(float)==sizeof(T));

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsBlasSize {
    public:
      typedef typename Check<IsBlasSizeFlag<T>::Flag>::Type   Type;
  };

}

#endif

