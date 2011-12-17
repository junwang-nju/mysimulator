
#ifndef _Minimizer_Line_Condition_Armijo_Specification_H_
#define _Minimizer_Line_Condition_Armijo_Specification_H_

#include "minimizer/line/condition/interface.h"

namespace mysimulator {

  template <typename T>
  struct Condition<T,Armijo> {
    static const bool
    Check(const T& ry,const T&,const T& my,const T& dp,const T&,const T& step) {
      return ry<=my+step*dp;
    }
  };

}

#endif

