
#ifndef _Map_Element_Copy_H_
#define _Map_Element_Copy_H_

#include "map/element/interface.h"
#include "referable-object/copy.h"
#include "map/hash/copy.h"

namespace mysimulator {

  template <typename ktype, typename vtype>
  void copy(MapElement<ktype,vtype>& E, const MapElement<ktype,vtype>& cE) {
    assert(IsValid(E)&&IsValid(cE));
    copy(E.key,cE.key);
    copy(E.value,cE.value);
    copy(E.hash,cE.hash);
  }

}

#endif

