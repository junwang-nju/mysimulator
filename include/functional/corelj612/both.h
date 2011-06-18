
#ifndef _Functional_CoreLJ612_Both_H_
#define _Functional_CoreLJ612_Both_H_

#include "functional/corelj612/parameter/name.h"
#include "functional/lj612/both.h"

namespace mysimulator {

  template <typename T>
  void BothCoreLJ612(const T& dsq,const UniqueParameter64Bit* prm,T& fc,T& df){
    if(dsq>prm[CoreLJ612RadiusSq].value<T>()) fc=df=0.;
    else {
      BothLJ612(dsq,prm,fc,df);
      fc+=prm[CoreLJ612EnergyDepth].value<T>();
    }
  }

}

#endif

