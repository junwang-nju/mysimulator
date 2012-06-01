
#ifndef _Type_IsIntrinsic_H_
#define _Type_IsIntrinsic_H_

namespace mysimulator {

  template <typename T>
  class IsIntrinsicFlag { public: static const bool Flag; };

  template <typename T>
  const bool IsIntrinsicFlag<T>::Flag=false;

}

#ifndef _IntrDEF_
#define _IntrDEF_(T) template <> const bool IsIntrinsicFlag<T>::Flag=true;
#else
#error "Duplicate _IntrDEF_"
#endif

namespace mysimulator {

  _IntrDEF_(long double)
  _IntrDEF_(double)
  _IntrDEF_(float)
  _IntrDEF_(long long)
  _IntrDEF_(unsigned long long)
  _IntrDEF_(int)
  _IntrDEF_(unsigned int)
  _IntrDEF_(long)
  _IntrDEF_(unsigned long)
  _IntrDEF_(short)
  _IntrDEF_(unsigned short)
  _IntrDEF_(char)
  _IntrDEF_(unsigned char)
  _IntrDEF_(bool)

}

#ifdef _IntrDEF_
#undef _IntrDEF_
#endif

namespace mysimulator {

  template <typename T>
  class IsIntrinsicFlag<T*> { public: static const bool Flag; };

  template <typename T>
  const bool IsIntrinsicFlag<T*>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsIntrinsic {
    public:
      typedef typename Check<IsIntrinsicFlag<T>::Flag>::Type  Type;
  };

}

#endif

