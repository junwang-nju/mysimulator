
#ifndef _Interaction_Func_Method_Angle_Both_H_
#define _Interaction_Func_Method_Angle_Both_H_

#include "distance/calc.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/func/impl/angle/common/buffer/vec-name.h"
#include "interaction/func/impl/angle/common/buffer/post-name.h"
#include "array/1d/scale-copy.h"

namespace mysimulator {

  template <typename GeomType,typename T>
  void BMethodAngle(
      T** const X,const unsigned int* id,const Unique64Bit* P,
      const GeomType& Geo,T& Energy,T** Grad,InteractionBuffer<T>& Buf,
      void (*bfunc)(const T*,const Unique64Bit*,T*,T*)) {
    uns
  }

}

#endif

