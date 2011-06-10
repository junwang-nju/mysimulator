
#ifndef _Map_Element_Hash_Allocate_H_
#define _Map_Element_Hash_Allocate_H_

#include "map/hash/interface.h"

namespace mysimulator {

  template <unsigned int nhash>
  void allocate(MapHash<nhash>& H) { H.clearData(); }

  template <unsigned int nhash>
  void imprint(MapHash<nhash>& H, const MapHash<nhash>&) { allocate(H); }

}

#endif

