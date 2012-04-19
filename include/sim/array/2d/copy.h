
#ifndef _Array_2D_Copy_H_
#define _Array_2D_Copy_H_

#include "array/1d/copy.h"
#include "array/2d/compare.h"
#include <cassert>

namespace mysimulator {

  template <typename T1, typename T2>
  void Copy(T1** p, T2** const q) {
    assert(IsSameStructure(p,q));
    Copy(*p,*q,size(*p));
  }

  template <typename T>
  void BLASCopy(T** p, T** const q) {
    assert(IsSameStructure(p,q));
    BLASCopy(*p,*q,size(*p));
  }

  template <typename T>
  void MemCopy(T** p, T** const q) {
    assert(IsSameStructure(p,q));
    MemCopy(*p,*q,size(*p));
  }

}

#endif

