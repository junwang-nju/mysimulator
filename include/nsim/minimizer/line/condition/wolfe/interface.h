
#ifndef _Minimizer_Line_Condition_Wolfe_Interface_H_
#define _Minimizer_Line_Condition_Wolfe_Interface_H_

#include "minimizer/line/condition/interface.h"

namespace mysimulator {

  template <typename T>
  struct Condition<T,Wolfe> {

    static const bool Check(T ry,T rp,T my,T dp,T cp, T step) {
      return Condition<T,Armijo>::Check(ry,rp,my,dp,cp,step)&&(rp>=cp);
    }

  };

}

#endif

