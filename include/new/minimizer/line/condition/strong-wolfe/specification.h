
#ifndef _Minimizer_Line_Condition_StrongWolfe_Specification_H_
#define _Minimizer_Line_Condition_StrongWolfe_Specification_H_

#include "minimizer/line/condition/wolfe/specification.h"

namespace mysimulator {

  template <typename T>
  struct Condition<T,StrongWolfe> {
    static const bool
    Check(const T& ry,const T& rp,const T& my,const T& dp,const T& cp,
          const T& step) {
      return Condition<T,Wolfe>::Check(ry,rp,my,dp,cp,step)&&(rp<=-cp);
    }
  };

}

#endif

