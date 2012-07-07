
#ifndef _Type_IsFillAble_H_
#define _Type_IsFillAble_H_

#include "type/is-included.h"
#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsFillableFlag {  public: static const bool Flag; };
  template <typename T1, typename T2> const bool IsFillableFlag<T1,T2>::Flag=
    IsIncludedFlag<T1,T2>::Flag&&IsNumericFlag<T1>::Flag&&
    IsNumericFlag<T2>::Flag;

  template <> const bool IsFillableFlag<bool,bool>::Flag=true;

}

#include "type/is-intrinsic.h"

namespace mysimulator {

  union Unique64Bit;
  template <typename T>
  class IsFillableFlag<Unique64Bit,T> { public: static const bool Flag; };
  template <typename T>
  const bool IsFillableFlag<Unique64Bit,T>::Flag=
    IsNumericFlag<T>::Flag&&(sizeof(T)<sizeof(long double));

  union Unique128Bit;
  template <typename T>
  class IsFillableFlag<Unique128Bit,T> { public: static const bool Flag; };
  template <typename T>
  const bool IsFillableFlag<Unique128Bit,T>::Flag=IsNumericFlag<T>::Flag;
  template <>
  const bool IsFillableFlag<Unique128Bit,Unique64Bit>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsFillable {
    public: typedef typename Check<IsFillableFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

