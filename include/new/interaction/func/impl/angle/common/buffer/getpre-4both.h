
#ifndef _Interaction_Func_Implement_Angle_Common_Buffer_GetPre4Both_H_
#define _Interaction_Func_Implement_Angle_Common_Buffer_GetPre4Both_H_

#include "interaction/func/impl/angle/common/buffer/getpre-4func.h"

namespace mysimulator {

  template <typename T>
  void AngleCommonGetPre4Both(InteractionBuffer<T>* Buf) {
    AngleCommonGetPre4Func(Buf);
  }

}

#endif

