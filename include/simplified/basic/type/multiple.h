
#ifndef _Basic_Type_Multiple_H_
#define _Basic_Type_Multiple_H_

namespace mysimulator {

  template <typename T1,typename T2>
  class __mul_flag {
    public:
      static const unsigned int FG;
    private:
      static const bool _all_intrinsic;
      static const bool _first_float;
      static const bool _second_float;
      static const bool _all_not_float;
      static const bool _first_unsigned;
      static const bool _second_unsigned;
      static const bool _same_unsigned;
  };

}

#include "basic/type/intrinsic.h"
#include "basic/type/float-point.h"
#include "basic/type/unsigned.h"

namespace mysimulator {

  template <typename T1,typename T2>
  const bool __mul_flag<T1,T2>::_all_intrinsic =
      __intrinsic_flag<T1>::FG && __intrinsic_flag<T2>::FG;

  template <typename T1,typename T2>
  const bool __mul_flag<T1,T2>::_first_float =
      __float_point_flag<T1>::FG;

  template <typename T1,typename T2>
  const bool __mul_flag<T1,T2>::_second_float =
      __float_point_flag<T2>::FG;

  template <typename T1,typename T2>
  const bool __mul_flag<T1,T2>::_all_not_float =
      !__mul_flag<T1,T2>::_first_float && !__mul_flag<T1,T2>::_second_float;

  template <typename T1,typename T2>
  const bool __mul_flag<T1,T2>::_first_unsigned =
      __unsigned_flag<T1>::FG;

  template <typename T1,typename T2>
  const bool __mul_flag<T1,T2>::_second_unsigned =
      __unsigned_flag<T2>::FG;

  template <typename T1,typename T2>
  const bool __mul_flag<T1,T2>::_same_unsigned =
      __mul_flag<T1,T2>::_first_unsigned == __mul_flag<T1,T2>::_second_unsigned;

  template <typename T1,typename T2>
  const unsigned int __mul_flag<T1,T2>::FG =
    __mul_flag<T1,T2>::_all_intrinsic ?
    ( (sizeof(T1)>=sizeof(T2)) &&
      ( !__mul_flag<T1,T2>::_first_unsigned ||
        __mul_flag<T1,T2>::_same_unsigned ) ) ||
    ( __mul_flag<T1,T2>::_first_float && !__mul_flag<T1,T2>::_second_float )?1:
    ( (sizeof(T2)>=sizeof(T1)) &&
      ( !__mul_flag<T1,T2>::_second_unsigned ||
        __mul_flag<T1,T2>::_same_unsigned ) ) ||
    ( __mul_flag<T1,T2>::_second_float && !__mul_flag<T1,T2>::_first_float )?
    2 : 0 : 0;

}

#endif

