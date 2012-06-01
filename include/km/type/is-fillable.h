
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

  template <typename T> class ArrayData;
  template <typename T1, typename T2>
  class IsFillableFlag<ArrayData<T1>,T2> {  public: static const bool Flag; };
  template <typename T1, typename T2>
  const bool IsFillableFlag<ArrayData<T1>,T2>::Flag=
    IsFillableFlag<T1,T2>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsFillable {
    public: typedef typename Check<IsFillableFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

