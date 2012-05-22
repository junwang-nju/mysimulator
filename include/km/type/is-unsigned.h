
#ifndef _Type_IsUnsigned_H_
#define _Type_IsUnsigned_H_

namespace mysimulator {

  template <typename T>
  class IsUnsignedFlag {  public: static const bool Flag; };

  template <typename T> const bool IsUnsignedFlag<T>::Flag=false;

}

#ifndef _UnsignDEF_
#define _UnsignDEF_(T)  template <> const bool IsUnsignedFlag<T>::Flag=true;
#else
#error "Duplicate _UnsignDEF_"
#endif

namespace mysimulator {

  _UnsignDEF_(unsigned long long)
  _UnsignDEF_(unsigned int)
  _UnsignDEF_(unsigned long)
  _UnsignDEF_(unsigned short)
  _UnsignDEF_(unsigned char)

}

#ifdef _UnsignDEF_
#undef _UnsignDEF_
#endif

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsUnsigned {
    public:
      typedef typename Check<IsUnsignedFlag<T>::Flag>::Type   Type;
  };

}

#endif
