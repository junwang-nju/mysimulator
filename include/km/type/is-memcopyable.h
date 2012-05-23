
#ifndef _Type_IsMemCopyable_H_
#define _Type_IsMemCopyable_H_

namespace mysimulator {

  template <typename T>
  class IsMemCopyableFlag { public: static const bool Flag; };

  template <typename T>
  const bool IsMemCopyableFlag<T>::Flag=true;

  template <typename T>
  class IsMemCopyableFlag<T*> { public: static const bool Flag; };

  template <typename T>
  const bool IsMemCopyableFlag<T*>::Flag=false;

  template <typename T> class ArrayData;
  template <typename T>
  class IsMemCopyableFlag<ArrayData<T> > { public: static const bool Flag; };

  template <typename T>
  const bool IsMemCopyableFlag<ArrayData<T> >::Flag=false;

  template <typename T> class Array;
  template <typename T>
  class IsMemCopyableFlag<Array<T> > { public: static const bool Flag; };

  template <typename T>
  const bool IsMemCopyableFlag<Array<T> >::Flag=false;

  template <typename T> class ArrayNumeric;
  template <typename T>
  class IsMemCopyableFlag<ArrayNumeric<T> > { public: static const bool Flag; };

  template <typename T>
  const bool IsMemCopyableFlag<ArrayNumeric<T> >::Flag=false;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsMemCopyable {
    public:
      typedef typename Check<IsMemCopyableFlag<T>::Flag>::Type  Type;
  };

}

#endif

