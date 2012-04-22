
#ifndef _Array_2D_Scale_H_
#define _Array_2D_Scale_H_

#include "array/2d/interface.h"

namespace mysimulator {

  template <typename T1,typename T2>
  void Scale(Array2D<T1>& V, const T2& d) { Scale(V._ldata,d,V._ldata.Size()); }

  template <typename T>
  void BlasScale(Array2D<T>& V, const T& d) {
    BlasScale(V._ldata,d,V._ldata.Size());
  }

}

#include "array/2d/compare.h"

namespace mysimulator {

  template <typename T1,typename T2>
  void Scale(Array2D<T1>& V, const Array2D<T2>& V2) {
    assert(IsSameStructure(V,V2));
    Scale(V._ldata,V2._ldata,V._ldata.Size());
  }

  template <typename T>
  void BlasScale(Array2D<T>& V, const Array2D<T>& V2) {
    assert(IsSameStructure(V,V2));
    BlasScale(V._ldata,V2._ldata,V._ldata.Size());
  }

}

#endif

