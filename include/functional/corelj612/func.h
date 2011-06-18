
#ifndef _Functional_CoreLJ612_Func_H_
#define _Functional_CoreLJ612_Func_H_

#include "functional/lj612/func.h"
#include "functional/corelj612/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void FuncCoreLJ612(const T& dsq,const UniqueParameter64Bit* prm,T& func) {
    if(dsq>prm[CoreLJ612RadiusSq].value<T>())   func=0.;
    else {
      FuncLJ612(dsq,prm,func);
      func+=prm[CoreLJ612EnergyDepth].value<T>();
    }
  }

}

#endif

