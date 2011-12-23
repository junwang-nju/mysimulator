
#ifndef _System_Propagate_Method_Name_H_
#define _System_Propagate_Method_Name_H_

namespace mysimulator {

  enum SystemPropagateMethodName {
    SysToBeDetermined=0, //used as Bai-Da
    SysFixPosition,
    SysMinimizerLineRegular,
    SysConstEVelVerlet,
    NumberSystemPropagateMethods,
    SysPropagateUnassigned
  };

}

#endif

