
#ifndef _Type_IsNumeric_H_
#define _Type_IsNumeric_H_

namespace mysimulator {

  template <typename T>
  class IsNumericFlag { public: static const bool Flag; };

  template <typename T> const bool IsNumericFlag<T>::Flag=false;

}

#ifndef _NumDEF_
#define _NumDEF_(T) template <> const bool IsNumericFlag<T>::Flag=true;
#else
#error "Duplicate _NumDEF_"
#endif

namespace mysimulator {

  _NumDEF_(long double)
  _NumDEF_(double)
  _NumDEF_(float)
  _NumDEF_(long long)
  _NumDEF_(unsigned long long)
  _NumDEF_(int)
  _NumDEF_(unsigned int)
  _NumDEF_(long)
  _NumDEF_(unsigned long)
  _NumDEF_(short)
  _NumDEF_(unsigned short)
  _NumDEF_(char)
  _NumDEF_(unsigned char)

}

#ifdef _NumDEF_
#undef _NumDEF_
#endif

namespace mysimulator {

  template <typename T> class ArrayNumeric;

  template <typename T>
  class IsNumericFlag<ArrayNumeric<T> > { public: static const bool Flag; };

  template <typename T>
  const bool IsNumericFlag<ArrayNumeric<T> >::Flag=
    IsNumericFlag<T>::Flag;

  template <typename T> class ArrayNumericDoubleSize;

  template <typename T>
  class IsNumericFlag<ArrayNumericDoubleSize<T> > {
    public: static const bool Flag;
  };

  template <typename T>
  const bool IsNumericFlag<ArrayNumericDoubleSize<T> >::Flag=
    IsNumericFlag<T>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsNumeric {
    public:
      typedef typename Check<IsNumericFlag<T>::Flag>::Type   Type;
  };

}

#endif

