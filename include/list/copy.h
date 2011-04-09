
#ifndef _List_Copy_H_
#define _List_Copy_H_

#include "list/interface.h"

namespace mysimulator {

  template <typename T, typename cT>
  void copy(List<T>& L, const List<cT>& cL) {
    assert(IsValid(L)&&IsValid(cL));
    unsigned int n=(L.ListSize()<cL.ListSize()?L.ListSize():cL.ListSize());
    for(unsigned int i=0;i<n;++i) copy<T,cT>(L.infra[i],cL.infra[i]);
  }

}

#include "list/compare.h"
#include "vector/copy.h"

namespace mysimulator {

  template <typename T>
  void ecopy(List<T>& L, const List<T>& cL) {
    assert(IsSameStructure(L,cL));
    copy(static_cast<Vector<T>&>(L),static_cast<const Vector<T>&>(cL));
  }

}

#endif

