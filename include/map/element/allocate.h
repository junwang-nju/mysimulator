
#ifndef _Map_Element_Allocate_H_
#define _Map_Element_Allocate_H_

#include "map/element/interface.h"

namespace mysimulator {

  template <typename ktype, typename vtype>
  void allocate(MapElement<ktype,vtype>& E) {}

  template <typename ktype, typename vtype>
  void imprint(MapElement<ktype,vtype>& E, const MapElement<ktype,vtype>& cE) {
    assert(IsValid(cE));
    release(E);
    imprint(E.key,cE.key);
    imprint(E.value,cE.value);
    allocate(E.hash);
  }

}

#endif

