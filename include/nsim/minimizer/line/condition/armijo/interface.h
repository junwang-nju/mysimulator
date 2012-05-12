
#ifndef _Minimizer_Line_Condition_Armijo_Interface_H_
#define _Minimizer_Line_Condition_Armijo_Interface_H_

#include "minimizer/line/condition/interface.h"

namespace mysimulator {

  template <typename T>
  struct Condition<T,Armijo> {

    static const bool Check(T ry, T,T my,T dp,T,T step) {
      return ry<=my+step*dp;
    }

  };

}

#endif

