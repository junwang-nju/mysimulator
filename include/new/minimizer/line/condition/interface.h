
#ifndef _Minimizer_Line_Condition_Interface_H_
#define _Minimizer_Line_Condition_Interface_H_

#include "minimizer/line/condition/name.h"
#include "io/error.h"

namespace mysimulator {

  template <typename T, LineMinimizerConditionName LMCName>
  struct Condition {
    bool Check(const T&,const T&,const T&,const T&,const T&,const T&) {
      Error("Unknown Condition!");
      return false;
    }
  };

  template <typename T>
  struct Condition<T,Armijo> {
    bool Check(const T& ry, const T&,const T& my,const T& dp,const T&,
               const T& step) { return ry<=my+step*dp; }
  };

  template <typename T>
  struct Condition<T,Wolfe> {
    bool Check(const T& ry, const T& rp, const T& my, const T& dp, const T& cp,
               const T& step) {
      return Condition<T,Armijo>::Check(ry,rp,my,dp,cp,step)&&(rp>=cp);
    }
  };

  template <typename T>
  struct Condition<T,StrongWolfe> {
    bool Check(const T& ry, const T& rp, const T& my, const T& dp, const T& cp,
               const T& step) {
      return Condition<T,Wolfe>::Check(ry,rp,my,dp,cp,step)&&(rp<=-cp);
    }
  };

}

#endif

