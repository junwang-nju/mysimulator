
#ifndef _Functional_CoreLJ612_Diff_H_
#define _Functional_CoreLJ612_Diff_H_

#include "functional/corelj612/parameter/name.h"
#include "functional/lj612/diff.h"

namespace mysimulator {

  template <typename T>
  void DiffCoreLJ612(const T& dsq,const UniqueParameter64Bit* prm,T& diff) {
    if(dsq>prm[CoreLJ612RadiusSq].value<T>())   diff=0.;
    else  DiffLJ612(dsq,prm,diff);
  }

}

#endif

