
#ifndef _Array_Format_Swap_H_
#define _Array_Format_Swap_H_

#include "array/format/interface.h"
#include "pointer/swap.h"

namespace mysimulator {

  template <typename T, template<typename> class ArrayContent>
  void Swap(ArrayFormat<T,ArrayContent>& A1, ArrayFormat<T,ArrayContent>& A2) {
    Swap(A1.data,A2.data);
    typedef typename ArrayFormat<T,ArrayContent>::ParentType  Type;
    Swap(static_cast<Type&>(A1),static_cast<Type&>(A2));
  }

}

#endif

