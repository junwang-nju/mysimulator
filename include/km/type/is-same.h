
#ifndef _Type_IsSame_H_
#define _Type_IsSame_H_

namespace mysimulator {

  template <typename T1, typename T2>
  class IsTypeSameFlag { public: static const bool Flag; };

  template <typename T1, typename T2>
  const bool IsTypeSameFlag<T1,T2>::Flag=false;

  template <typename T>
  class IsTypeSameFlag<T,T> { public: static const bool Flag; };
  template <typename T>
  const bool IsTypeSameFlag<T,T>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsTypeSame {
    public:
      typedef typename Check<IsTypeSameFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif
