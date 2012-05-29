
#ifndef _Propagator_Minimizer_Line_Condition_Name_H_
#define _Propagator_Minimizer_Line_Condition_Name_H_

namespace mysimulator {

  enum LineMinimizerConditionName {
    Armijo,
    Wolfe,
    StrongWolfe,
    UnknownCondition
  };

}

#endif

