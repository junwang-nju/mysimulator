
#ifndef _System_Content_Data_Null_Accumulate_H_
#define _System_Content_Data_Null_Accumulate_H_

#include "system/content/data/null/interface.h"
#include "io/error.h"

namespace mysimulator {

  void accumulateEnergy(SysContentDataNull&, const SysContentDataNull&) {
    Error("Not available for this data!");
  }

  void accumulateGradient(SysContentDataNull&, const SysContentDataNull&) {
    Error("Not available for this data!");
  }

  void accumulateBoth(SysContentDataNull&, const SysContentDataNull&) {
    Error("Not available for this data!");
  }

  void accumulate(SysContentDataNull&, const SysContentDataNull&) {
    Error("Not available for this data!");
  }

}

#endif

