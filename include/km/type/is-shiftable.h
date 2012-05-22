
#ifndef _Type_Is_Shiftable_H_
#define _Type_Is_Shiftable_H_

#include "type/is-included.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsShiftableFlag { public: static const bool Flag; };

  template <typename T1, typename T2>
  const bool IsShiftableFlag<T1,T2>::Flag=
    IsIncludedFlag<T1,T2>::Flag;

  template <typename T> class ArrayNumeric;
  template <typename T1, typename T2>
  class IsShiftableFlag<ArrayNumeric<T1>,T2> {
    public: static const bool Flag;
  };
  template <typename T1, typename T2>
  const bool IsShiftableFlag<ArrayNumeric<T1>,T2>::Flag=
    IsShiftableFlag<T1,T2>::Flag;

  template <typename T1, typename T2>
  class IsShiftableFlag<ArrayNumeric<T1>,ArrayNumeric<T2> > {
    public: static const bool Flag;
  };
  template <typename T1, typename T2>
  const bool IsShiftableFlag<ArrayNumeric<T1>,ArrayNumeric<T2> >::Flag=
    IsShiftableFlag<T1,T2>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsShiftable {
    public:
      typedef typename Check<IsShiftableFlag<T1,T2>::Flag>::Type  Type;
  };

}

#endif

