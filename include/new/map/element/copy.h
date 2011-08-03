
#ifndef _Map_Element_Copy_H_
#define _Map_Element_Copy_H_

#include "map/element/interface.h"
#include "object/copy.h"
#include "map/hash/copy.h"

namespace mysimulator {

  template <typename KT, typename VT>
  void copy(MapElement<KT,VT>& E, const MapElement<KT,VT>& cE) {
    assert(IsValid(E)&&IsValid(cE));
    copy(E.key,cE.key);
    copy(E.value,cE.value);
    copy(E.hash,cE.hash);
  }

}

#endif

