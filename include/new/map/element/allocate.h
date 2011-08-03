
#ifndef _Map_Element_Allocate_H_
#define _Map_Element_Allocate_H_

#include "map/element/interface.h"
#include "map/hash/allocate.h"
#include "object/allocate.h"

namespace mysimulator {

  template <typename KT, typename VT>
  void imprint(MapElement<KT,VT>& E, const MapElement<KT,VT>& cE) {
    assert(IsValid(cE));
    release(E);
    allocate(E.hash);
    imprint(E.key,cE.key);
    imprint(E.value,cE.value);
  }

}

#endif

