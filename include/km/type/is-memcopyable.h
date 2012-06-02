
/**
 * @file type/is-memcopyable.h
 * @brief check if an object can be copied with another object
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsMemCopyable_H_
#define _Type_IsMemCopyable_H_

#include "type/is-intrinsic.h"

namespace mysimulator {

  template <typename T>
  class IsMemCopyableFlag { public: static const bool Flag; };

  template <typename T>
  const bool IsMemCopyableFlag<T>::Flag=
    IsIntrinsicFlag<T>::Flag;

  template <typename T>
  class IsMemCopyableFlag<T*> { public: static const bool Flag; };

  template <typename T>
  const bool IsMemCopyableFlag<T*>::Flag=false;

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

