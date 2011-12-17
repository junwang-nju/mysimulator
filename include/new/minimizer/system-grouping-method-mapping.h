
#ifndef _Minimizer_System_GroupingMethod_Mapping_H_
#define _Minimizer_System_GroupingMethod_Mapping_H_

#include "system/grouping/method-name.h"
#include "io/error.h"

namespace mysimulator {

  const SystemGroupingMethodName
  MinimizerSysGrpMethodMapping(const SystemGroupingMethodName& GM) {
    SystemGroupingMethodName oGM=SystemUnassigned;
    switch(GM) {
      case SystemFixPosition:
      case SystemMinimizerLineRegular:
        oGM=GM;
        break;
      default:
        Error("Unknown System Grouping Method to be mapped in Minimizer!");
    }
    return oGM;
  }

}

#endif

