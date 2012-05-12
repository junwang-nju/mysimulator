
#ifndef _Minimizer_Line_Condition_Interface_H_
#define _Minimizer_Line_Condition_Interface_H_

#include "minimizer/line/condition/method-name.h"

namespace mysimulator {

  template <typename T, LineMinimizerConditionMethodName LCM>
  struct Condition {

    static bool Check(T,T,T,T,T,T) {
      fprintf(stderr,"Unknown Condition Method!\n"); return false;
    }

  };

#include "minimizer/line/condition/armijo/interface.h"

}

#endif

