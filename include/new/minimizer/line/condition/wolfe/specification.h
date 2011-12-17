
#ifndef _Minimizer_Line_Condition_Wolfe_Specification_H_
#define _Minimizer_Line_Condition_Wolfe_Specification_H_

#include "minimizer/line/condition/armijo/specification.h"

namespace mysimulator {

  template <typename T>
  struct Condition<T,Wolfe> {
    static const bool
    Check(const T& ry,const T& rp,const T& my,const T& dp,const T& cp,
          const T& step) {
      return Condition<T,Armijo>::Check(ry,rp,my,dp,cp,step)&&(rp>=cp);
    }
  };

}

#endif

