
#ifndef _System_Mask_Mode_H_
#define _System_Mask_Mode_H_

namespace mysimulator {

  enum SystemMaskModeName {
    SystemNoMask=0,
    SystemFixed,
    SystemFree,
    SystemMaskModeNumber
  };

}

#include "system/masked/method/name.h"

namespace mysimulator {

  static const SystemMaskMethodName SystemMaskModeMethod[SystemMaskModeNumber]={
    SystemNoOperation,SystemDoMask,SystemDoMask
  };

}

#endif

