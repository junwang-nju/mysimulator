
#ifndef _Array_Base_Swap_H_
#define _Array_Base_Swap_H_

#include "array/base/interface.h"
#include "array/data/swap.h"

namespace mysimulator {

  template <typename T>
  void _Swap(ArrayBase<T>& A, ArrayBase<T>& B) {
    typedef ArrayData<T>  DType;
    _Swap(static_cast<DType&>(A),static_cast<DType&>(B));
    _SwapContent(A._status,B._status);
    _SwapContent(A._isPart,B._isPart);
  }

}

#endif

