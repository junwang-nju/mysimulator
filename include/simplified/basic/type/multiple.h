
#ifndef _Basic_Type_Multiple_H_
#define _Basic_Type_Multiple_H_

#include "basic/type/intrinsic-check.h"

namespace mysimulator {

  template <typename T1,typename T2>
  class __mul {
    public:
      static_assert( __intrinsic<T1>::FLAG && __intrinsic<T2>::FLAG,
                     "Only Works for Intrinsic Type!\n" );
      static const unsigned int FLAG;
    private:
      static const bool _not_float;
      static const bool _same_unsigned;
      static const bool _first_float;
      static const bool _second_float;
      static const bool _first_not_float;
      static const bool _second_not_float;
  };

}

#include "basic/type/intrinsic-def.h"

namespace mysimulator {

  template <typename T1,typename T2>
  const bool __mul<T1,T2>::_not_float =
    ! Intrinsic<T1>::IsFloatingPoint && ! Intrinsic<T2>::IsFloatingPoint;

  template <typename T1,typename T2>
  const bool __mul<T1,T2>::_same_unsigned =
    Intrinsic<T1>::IsUnsigned == Intrinsic<T2>::IsUnsigned;

  template <typename T1,typename T2>
  const bool __mul<T1,T2>::_first_float =
    Intrinsic<T1>::IsFloatingPoint &&
    ( sizeof(T1)>=sizeof(T2) || ! Intrinsic<T2>::IsFloatingPoint );

  template <typename T1,typename T2>
  const bool __mul<T1,T2>::_second_float =
    Intrinsic<T2>::IsFloatingPoint &&
    ( sizeof(T2)>=sizeof(T1) || ! Intrinsic<T1>::IsFloatingPoint );

  template <typename T1,typename T2>
  const bool __mul<T1,T2>::_first_not_float =
    __mul<T1,T2>::_not_float && sizeof(T1)>=sizeof(T2) &&
    ( ! Intrinsic<T1>::IsUnsigned || __sum<T1,T2>::_same_unsigned );

  template <typename T1,typename T2>
  const bool __mul<T1,T2>::_second_not_float =
    __mul<T1,T2>::_not_float && sizeof(T2)>=sizeof(T1) &&
    ( ! Intrinsic<T2>::IsUnsigned || __sum<T1,T2>::_same_unsigned );

  template <typename T1,typename T2>
  const unsigned int __mul<T1,T2>::FLAG = 
    __mul<T1,T2>::_first_float ? 1 :
    __mul<T1,T2>::_second_float ? 2 :
    __mul<T1,T2>::_first_not_float ? 1 :
    __mul<T1,T2>::_second_not_float ? 2 : 0;

}

#endif

