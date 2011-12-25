
#ifndef _Accelerator_NeighborList_Allocate_H_
#define _Accelerator_NeighborList_Allocate_H_

#include "accelerator/neighbor-list/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(NeighborList<T>& L, const unsigned int& n) {
    release(L);
    allocate(L.tmpVec,n);
  }

  template <typename T1, typename T2>
  void imprint(NeighborList<T1>& L, const NeighborList<T2>& cL) {
    assert(IsValid(cL));
    release(L);
    _imprint_structure(L.tmpVec,cL.tmpVec);
  }

}

#endif

