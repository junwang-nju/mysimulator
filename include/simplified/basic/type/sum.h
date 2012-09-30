
#ifndef _Basic_Type_Sum_H_
#define _Basic_Type_Sum_H_

#include "basic/type/intrinsic.h"
#include "basic/type/float-point.h"
#include "basic/type/unsigned.h"

namespace mysimulator {

  template <typename T1,typename T2>
  class __sum_flag { public: static const unsigned int FG; };

  template <typename T1,typename T2>
  const unsigned int __sum_flag<T1,T2>::FG=
    __intrinsic_flag<T1>::FG&&__intrinsic_flag<T2>::FG?
    ((__float_point_flag<T1>::FG)&&((sizeof(T1)>=sizeof(T2))||
                                    (!__float_point_flag<T2>::FG)))||
     ((!__float_point_flag<T1>::FG)&&(!__float_point_flag<T2>::FG)&&
      (sizeof(T1)>sizeof(T2))&&
      ((!__unsigned_flag<T1>::FG)||
       (__unsigned_flag<T1>::FG==__unsigned_flag<T2>::FG)))?1:
    ((__float_point_flag<T2>::FG)&&((sizeof(T2)>=sizeof(T1))||
                                    (!__float_point_flag<T1>::FG)))||
     ((!__float_point_flag<T2>::FG)&&(!__float_point_flag<T1>::FG)&&
      (sizeof(T2)>sizeof(T1))&&
      ((!__unsigned_flag<T2>::FG)||
       (__unsigned_flag<T2>::FG==__unsigned_flag<T1>::FG)))?2:0:0;

}

#endif

