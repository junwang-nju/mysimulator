
#ifndef _List_Shift_H_
#define _List_Shift_H_

#include "list/interface.h"
#include "vector/shift.h"

namespace mysimulator {

  template <typename T, typename fT, typename sT>
  void shift(List<T>& L, const fT& d, const List<sT>& sL) {
    assert(IsValid(L)&&IsValid(sL));
    unsigned int n=(L.ListSize()<sL.ListSize()?L.ListSize():sL.ListSize());
    for(unsigned int i=0;i<n;++i)   shift(L[i],d,sL[i]);
  }

}

#endif

