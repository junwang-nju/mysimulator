
#ifndef _Map_Element_Hash_Allocate_H_
#define _Map_Element_Hash_Allocate_H_

#include "map/element/hash/interface.h"

namespace mysimulator {

  template <unsigned int nhash>
  void allocate(MapHash<nhash>& H) { H.clearData(); }

  template <unsigned int nhash1>
  void imprint(MapHash<nhash>& H, MapHash<nhash>& cH) { allocate(H); }

}

#endif

