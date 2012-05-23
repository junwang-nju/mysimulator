
#ifndef _Type_IsChar_H_
#define _Type_IsChar_H_

namespace mysimulator {

  template <typename T>
  class IsCharFlag { public: static const bool Flag; };

  template <typename T>
  const bool IsCharFlag<T>::Flag=false;

  template <> const bool IsCharFlag<char>::Flag=true;
  template <> const bool IsCharFlag<unsigned char>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsChar {
    public:
      typedef typename Check<IsCharFlag<T>::Flag>::Type   Type;
  };

}

#endif

