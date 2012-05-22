
#ifndef _Type_IsInteger_H_
#define _Type_IsInteger_H_

namespace mysimulator {

  template <typename T>
  class IsIntegerFlag { public: static const bool Flag; };

  template <typename T> const bool IsIntegerFlag<T>::Flag=false;

}

#ifndef _IntDEF_
#define _IntDEF_(T) template <> const bool IsIntegerFlag<T>::Flag=true;
#else
#error "Duplicate _IntDEF_"
#endif

namespace mysimulator {

  _IntDEF_(long long)
  _IntDEF_(unsigned long long)
  _IntDEF_(int)
  _IntDEF_(unsigned int)
  _IntDEF_(long)
  _IntDEF_(unsigned long)
  _IntDEF_(short)
  _IntDEF_(unsigned short)
  _IntDEF_(char)
  _IntDEF_(unsigned char)

}

#ifdef _IntDEF_
#undef _IntDEF_
#endif

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsInteger {
    public:
      typedef typename Check<IsIntegerFlag<T>::Flag>::Type  Type;
  };

}

#endif

