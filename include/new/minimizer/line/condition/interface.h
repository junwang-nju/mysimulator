
#ifndef _Minimizer_Line_Condition_Interface_H_
#define _Minimizer_Line_Condition_Interface_H_

#include "minimizer/line/condition/method-name.h"
#include "io/error.h"

namespace mysimulator {

  template <typename T, LineMinimizerConditionMethodName LCM>
  struct Condition {
    static bool Check(const T&,const T&,const T&,const T&,const T&,const T&) {
      Error("Unknown Condition Method!");
      return false;
    }
  };

}

#include "minimizer/line/condition/armijo/specification.h"
#include "minimizer/line/condition/wolfe/specification.h"
#include "minimizer/line/condition/strong-wolfe/specification.h"

#endif

