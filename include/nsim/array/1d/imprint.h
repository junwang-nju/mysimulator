
#ifndef _Array_1D_Imprint_H_
#define _Array_1D_Imprint_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T,typename T1>
  void ImprintStructure(Array1D<T>& V,const Array1D<T1>& V1) {
    V.Allocate(V1.Size());
  }

}

#include "intrinsic-type/imprint.h"

namespace mysimulator {

  template <typename T>
  void Imprint(Array1D<T>& V, const Array1D<T>& V1) {
    ImprintStructure(V,V1);
    for(unsigned int i=0;i<V.Size();++i)  Imprint(V[i],V1[i]);
  }

}

#endif

