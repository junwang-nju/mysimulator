
#ifndef _Minimizer_System_PropagateMethod_Mapping_H_
#define _Minimizer_System_PropagateMethod_Mapping_H_

#include "system/propagate/method-name.h"
#include "io/error.h"

namespace mysimulator {

  const SystemPropagateMethodName
  MinimizerSysPropagateMethodMapping(const SystemPropagateMethodName& PM) {
    SystemPropagateMethodName oPM=SysPropagateUnassigned;
    switch(PM) {
      case SysFixPosition:
      case SysMinimizerLineRegular:
        oPM=PM;
        break;
      case SysToBeDetermined:
        oPM=SysMinimizerLineRegular;
      default:
        Error("Unknown System Propagate Method to be mapped in Minimizer!");
    }
    return oPM;
  }

}

#endif

