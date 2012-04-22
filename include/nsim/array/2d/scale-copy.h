
#ifndef _Array_2D_Scale_Copy_H_
#define _Array_2D_Scale_Copy_H_

#include "array/2d/compare.h"
#include "array/1d/scale-copy.h"

namespace mysimulator {

  template <typename T1,typename T2,typename T3>
  void ScaleCopy(Array2D<T1>& V,const Array2D<T2>& V2,const T3& d) {
    assert(IsSameStructure(V,V2));
    ScaleCopy(V._ldata,V2._ldata,d,V._ldata.Size());
  }

  template <typename T1,typename T2,typename T3>
  void ScaleCopy(Array2D<T1>& V,const T2& d, const Array2D<T3>& V2) {
    ScaleCopy(V,V2,d);
  }

  template <typename T1,typename T2,typename T3>
  void ScaleCopy(Array2D<T1>& V,const Array2D<T2>& V2,const Array2D<T3>& V3) {
    assert(IsSameStructure(V,V2)&&IsSameStructure(V,V3));
    ScaleCopy(V._ldata,V2._ldata,V3._ldata,V._ldata.Size());
  }

  template <typename T>
  void BlasScaleCopy(Array2D<T>& V,const Array2D<T>& V2,const T& d) {
    assert(IsSameStructure(V,V2));
    BlasScaleCopy(V._ldata,V2._ldata,d,V._ldata.Size());
  }

  template <typename T>
  void BlasScaleCopy(Array2D<T>& V,const T& d,const Array2D<T>& V2) {
    BlasScaleCopy(V,V2,d);
  }

  template <typename T>
  void BlasScaleCopy(Array2D<T>& V,const Array2D<T>& V2,const Array2D<T>& V3) {
    assert(IsSameStructure(V,V2)&&IsSameStructure(V,V3));
    BlasScaleCopy(V._ldata,V2._ldata,V3._ldata,V._ldata.Size());
  }

  template <typename T>
  void MemScaleCopy(Array2D<T>& V,const Array2D<T>& V2,const T& d) {
    assert(IsSameStructure(V,V2));
    MemScaleCopy(V._ldata,V2._ldata,d,V._ldata.Size());
  }

  template <typename T>
  void MemScaleCopy(Array2D<T>& V,const T& d,const Array2D<T>& V2) {
    MemScaleCopy(V,V2,d);
  }

  template <typename T>
  void MemScaleCopy(Array2D<T>& V,const Array2D<T>& V2,const Array2D<T>& V3) {
    assert(IsSameStructure(V,V2)&&IsSameStructure(V,V3));
    MemScaleCopy(V._ldata,V2._ldata,V3._ldata,V._ldata.Size());
  }

}

#endif

