
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

  template <typename T1, typename T2>
  class IsNegShiftableFlag { public: static const bool Flag; };

}

#include "type/is-unsigned.h"
#include "type/data.h"

namespace mysimulator {

  template <typename T1, typename T2>
  const bool IsNegShiftableFlag<T1,T2>::Flag=
    IsShiftableFlag<T1,T2>::Flag&&
    (!IsUnsignedFlag<typename DataType<T1>::Type>::Flag);

  template <typename T1,typename T2,typename T3>
  class IsShiftable3Flag { public: static const bool Flag; };

  template <typename T1,typename T2,typename T3>
  const bool IsShiftable3Flag<T1,T2,T3>::Flag=
    IsShiftableFlag<T1,T2>::Flag&&IsShiftableFlag<T1,T3>::Flag;

  template <typename T1,typename T2,typename T3,typename T4>
  class IsShiftable4Flag { public: static const bool Flag;  };

  template <typename T1,typename T2,typename T3,typename T4>
  const bool IsShiftable4Flag<T1,T2,T3,T4>::Flag=
    IsShiftableFlag<T1,T2>::Flag&&IsShiftableFlag<T1,T3>::Flag&&
    IsShiftableFlag<T1,T4>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsShiftable {
    public:
      typedef typename Check<IsShiftableFlag<T1,T2>::Flag>::Type  Type;
  };

  template <typename T1, typename T2>
  class IsNegShiftable {
    public:
      typedef typename Check<IsNegShiftableFlag<T1,T2>::Flag>::Type Type;
  };

  template <typename T1,typename T2,typename T3>
  class IsShiftable3 {
    public:
      typedef typename Check<IsShiftable3Flag<T1,T2,T3>::Flag>::Type  Type;
  };

  template <typename T1,typename T2,typename T3,typename T4>
  class IsShiftable4 {
    public:
      typedef typename Check<IsShiftable4Flag<T1,T2,T3,T4>::Flag>::Type  Type;
  };

}

#endif

