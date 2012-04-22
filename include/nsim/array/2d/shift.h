
#ifndef _Array_2D_Shift_H_
#define _Array_2D_Shift_H_

#include "array/2d/interface.h"
#include "array/1d/shift.h"

namespace mysimulator {

  template <typename T1,typename T2>
  void Shift(Array2D<T1>& V, const T2& d) {
    Shift(V._ldata,d,V._ldata.Size());
  }

  template <typename T>
  void BlasShift(Array2D<T>& V, const T& d) {
    BlasShift(V._ldata,d,V._ldata.Size());
  }

}

#include "array/2d/compare.h"

namespace mysimulator {

  template <typename T1,typename T2>
  void Shift(Array2D<T1>& V, const Array2D<T2>& V2) {
    assert(IsSameStructure(V,V2));
    Shift(V._ldata,V2._ldata,V._ldata.Size());
  }

  template <typename T>
  void BlasShift(Array2D<T>& V, const Array2D<T>& V2) {
    assert(IsSameStructure(V,V2));
    BlasShift(V._ldata,V2._ldata,V._ldata.Size());
  }

  template <typename T1,typename T2,typename T3>
  void Shift(Array2D<T1>& V,const T2& d,const Array2D<T3>& V2) {
    assert(IsSameStructure(V,V2));
    Shift(V._ldata,d,V2._ldata,V._ldata.Size());
  }

  template <typename T>
  void BlasShift(Array2D<T>& V, const T& d, const Array2D<T>& V2) {
    assert(IsSameStructure(V,V2));
    BlasShift(V._ldata,d,V2._ldata,V._ldata.Size());
  }

  template <typename T1,typename T2,typename T3>
  void Shift(Array2D<T1>& V,const Array2D<T2>& V2,const T3& d) {
    Shift(V,d,V2);
  }

  template <typename T>
  void BlasShift(Array2D<T>& V,const Array2D<T>& V2,const T& d) {
    BlasShift(V,d,V2);
  }

  template <typename T1,typename T2,typename T3>
  void Shift(Array2D<T1>& V,const Array2D<T2>& V2,const Array2D<T3>& V3) {
    assert(IsSameStructure(V,V2)&&IsSameStructure(V,V3));
    Shift(V._ldata,V2._ldata,V3._ldata,V._ldata.Size());
  }

  template <typename T>
  void BlasShift(Array2D<T>& V,const Array2D<T>& V2,const Array2D<T>& V3) {
    assert(IsSameStructure(V,V2)&&IsSameStructure(V,V3));
    BlasShift(V._ldata,V2._ldata,V3._ldata,V._ldata.Size());
  }

  template <typename T1,typename T2,typename T3,typename T4>
  void Shift(Array2D<T1>& V,const T2& d, const Array2D<T3>& V3,
             const Array2D<T4>& V4) {
    assert(IsSameStructure(V,V3)&&IsSameStructure(V,V4));
    Shift(V._ldata,d,V3._ldata,V4._ldata,V._ldata.Size());
  }

  template <typename T>
  void BlasShift(Array2D<T>& V,const T& d,const Array2D<T>& V3,
                 const Array2D<T>& V4) {
    assert(IsSameStructure(V,V3)&&IsSameStructure(V,V4));
    BlasShift(V._ldata,d,V3._ldata,V4._ldata,V._ldata.Size());
  }

}

#endif

