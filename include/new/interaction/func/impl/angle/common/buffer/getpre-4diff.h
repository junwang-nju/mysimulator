
#ifndef _Interaction_Func_Implement_Angle_Common_Buffer_GetPre4Diff_H_
#define _Interaction_Func_Implement_Angle_Common_Buffer_GetPre4Diff_H_

#include "interaction/func/impl/angle/common/buffer/getpre-4func.h"

namespace mysimulator {

  template <typename T>
  void AngleCommonGetPre4Diff(InteractionBuffer<T>* Buf,const int* inf,T* pre) {
    AngleCommonGetPre4Func(Buf,inf,pre);
  }

}

#endif

