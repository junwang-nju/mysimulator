
#ifndef _Type_IsCopyAble_H_
#define _Type_IsCopyAble_H_

#include "type/is-included.h"
#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsCopyableFlag {  public: static const bool Flag; };
  template <typename T1, typename T2> const bool IsCopyableFlag<T1,T2>::Flag=
    IsIncludedFlag<T1,T2>::Flag&&IsNumericFlag<T1>::Flag&&
    IsNumericFlag<T2>::Flag;

  template <typename T>
  class IsCopyableFlag<T*,T*> { public: static const bool Flag; };
  template <typename T> const bool IsCopyableFlag<T*,T*>::Flag=true;

  template <typename T>
  class IsCopyableFlag<void*,T*> {  public: static const bool Flag; };
  template <typename T> const bool IsCopyableFlag<void*,T*>::Flag=true;

  template <typename T>
  class IsCopyableFlag<T*,void*> {  public: static const bool Flag; };
  template <typename T> const bool IsCopyableFlag<T*,void*>::Flag=true;

}

#include "type/is-integer.h"

namespace mysimulator {

  template <typename T>
  class IsCopyableFlag<bool,T> {  public: static const bool Flag; };
  template <typename T> const bool IsCopyableFlag<bool,T>::Flag=
    IsIntegerFlag<T>::Flag;

}

#include "type/is-intrinsic.h"

namespace mysimulator {

  union Unique64Bit;

  template <typename T>
  class IsCopyableFlag<Unique64Bit,T> { public: static const bool Flag; };

  template <typename T> const bool IsCopyableFlag<Unique64Bit,T>::Flag=
    IsNumericFlag<T>::Flag&&IsIntrinsicFlag<T>::Flag&&
    (sizeof(T)<sizeof(long double));

  template <typename T>
  class IsCopyableFlag<T,Unique64Bit> { public: static const bool Flag; };

  template <typename T> const bool IsCopyableFlag<T,Unique64Bit>::Flag=
    IsNumericFlag<T>::Flag&&IsIntrinsicFlag<T>::Flag&&
    (sizeof(T)<sizeof(long double));

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsCopyable {
    public:
      typedef typename Check<IsCopyableFlag<T1,T2>::Flag>::Type  Type;
  };

}

#endif

