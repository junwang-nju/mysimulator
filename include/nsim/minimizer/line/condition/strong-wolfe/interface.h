
#ifndef _Minimizer_Line_Condition_StrongWolfe_H_
#define _Minimizer_Line_Condition_StrongWolfe_H_

#include "minimizer/line/condition/wolfe/interface.h"

namespace mysimulator {

  template <typename T>
  struct Condition<T,StrongWolfe> {

    static const bool Check(T ry,T rp,T my,T dp, T cp, T step) {
      return Condition<T,Wolfe>::Check(ry,rp,my,dp,cp,step)&&(rp<=-cp);
    }

  };

}

#endif

