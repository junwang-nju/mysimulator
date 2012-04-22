
#ifndef _Array_2D_Fill_H_
#define _Array_2D_Fill_H_

#include "array/2d/interface.h"
#include "array/1d/fill.h"

namespace mysimulator {

  template <typename T1,typename T2>
  void Fill(Array2D<T1>& V1, const T2& d) {
    Fill(V1._ldata,d,V1._ldata.Size());
  }

  template <typename T>
  void BlasFill(Array2D<T>& V, const T& d) {
    BlasFill(V1._ldata,d,V1._ldata.Size());
  }

  template <typename T>
  void MemFill(Array2D<T>& V, const T& d) {
    MemFill(V1._ldata,d,V1._ldata.Size());
  }

}

#endif

