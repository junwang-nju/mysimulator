
#ifndef _Interaction_Func_Implement_CoreLJ612_Func_H_
#define _Interaction_Func_Implement_CoreLJ612_Func_H_

#include "interaction/func/impl/corelj612/parameter/name.h"
#include "interaction/func/impl/lj612/func.h"

namespace mysimulator {

  template <typename T>
  void FuncCoreLJ612(const T& dsq, const Unique64Bit* P, T& func) {
    if(dsq>P[CoreLJ612RadiusSQ].value<T>()) func=0.;
    else {
      FuncLJ612(dsq,P,func);
      func+=P[CoreLJ612EnergyDepth].value<T>();
    }
  }

}

#endif

