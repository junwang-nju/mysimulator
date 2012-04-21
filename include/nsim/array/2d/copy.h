
#ifndef _Array_2D_Copy_H_
#define _Array_2D_Copy_H_

#include "array/2d/compare.h"
#include "array/1d/copy.h"

namespace mysimulator {

  template <typename T1,typename T2>
  void Copy(Array2D<T1>& V,const Array2D<T2>& V2) {
    assert(IsSameStructure(V,V2));
    Copy(V._ldata,V2._ldata,V._ldata.Size());
  }

  template <typename T>
  void BlasCopy(Array2D<T>& V,const Array2D<T>& V2) {
    assert(IsSameStructure(V,V2));
    BlasCopy(V._ldata,V2._ldata,V._ldata.Size());
  }

  template <typename T>
  void MemCopy(Array2D<T>& V,const Array2D<T>& V2) {
    assert(IsSameStructure(V,V2));
    MemCopy(V._ldata,V2._ldata,V._ldata.Size());
  }

}

#endif

