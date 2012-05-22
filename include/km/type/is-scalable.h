
#ifndef _Type_IsScalable_H_
#define _Type_IsScalable_H_

#include "type/is-included.h"
#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsScalableFlag {  public: static const bool Flag; };

  template <typename T1, typename T2>
  const bool IsScalableFlag<T1,T2>::Flag=
    IsIncludedFlag<T1,T2>::Flag&&IsNumericFlag<T1>::Flag&&
    IsNumericFlag<T2>::Flag;

  template <typename T> class ArrayNumeric;
  template <typename T1, typename T2>
  class IsScalableFlag<ArrayNumeric<T1>,T2> {
    public: static const bool Flag;
  };
  template <typename T1, typename T2>
  const bool IsScalableFlag<ArrayNumeric<T1>,T2>::Flag=
    IsScalableFlag<T1,T2>::Flag;

  template <typename T1, typename T2>
  class IsScalableFlag<ArrayNumeric<T1>,ArrayNumeric<T2> > {
    public: static const bool Flag;
  };
  template <typename T1, typename T2>
  const bool IsScalableFlag<ArrayNumeric<T1>,ArrayNumeric<T2> >::Flag=
    IsScalableFlag<T1,T2>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsScalable {
    public:
      typedef typename Check<IsScalableFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

