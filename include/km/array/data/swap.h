
#ifndef _Array_Data_Swap_H_
#define _Array_Data_Swap_H_

#include "array/data/interface.h"
#include "basic/swap.h"

namespace mysimulator {

  template <typename T>
  void _Swap(ArrayData<T>& A, ArrayData<T>& B) {
    _SwapContent(A._data,B._data);
    _SwapContent(A._size,B._size);
    _SwapContent(A._alloc,B._alloc);
  }

  template <typename T>
  void _SwapContent(ArrayData<T>& A, ArrayData<T>& B) {
    assert(A.IsValid());
    assert(B.IsValid());
    assert(A.Size()==B.Size());
    T *p=A.Head(), *pEnd=A.Head()+A.Size();
    T *q=B.Head();
    for(;p!=pEnd;)  _SwapContent(*(p++),*(q++));
  }

}

#endif

