
#ifndef _Array_2D_Dot_H_
#define _Array_2D_Dot_H_

#include "array/2d/compare.h"
#include "array/1d/dot.h"

#ifndef _DotType
#define _DotType(T1,T2) typename _Dual<T1,T2>::CombineType
#else
#error "Duplicate Definition for Macro _DotType"
#endif

namespace mysimulator {

  template <typename T1,typename T2>
  _DotType(T1,T2) Dot(const Array2D<T1>& V1,const Array2D<T2>& V2) {
    assert(IsSameStructure(V1,V2));
    return Dot(V1._ldata,V2._ldata,V1._ldata.Size());
  }

}

#ifdef _DotType
#undef _DotType
#endif

namespace mysimulator {

  template <typename T>
  T BlasDot(const Array2D<T>& V1,const Array2D<T>& V2) {
    assert(IsSameStructure(V1,V2));
    return BlasDot(V1._ldata,V2._ldata,V1._ldata.Size());
  }

}

#endif

