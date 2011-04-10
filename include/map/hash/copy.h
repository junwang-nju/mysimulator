
#ifndef _Map_Element_Hash_Copy_H_
#define _Map_Element_Hash_Copy_H_

#include "map/hash/interface.h"

namespace mysimulator {

  template <unsigned int nhash>
  void copy(MapHash<nhash>& H, const MapHash<nhash>& cH) {
    unsigned int *p=H.value;
    unsigned int *cp=const_cast<unsigned int*>(cH.value);
    unsigned int *pend=p+nhash;
    for(;p!=pend;)  *(p++)=*(cp++);
  }

}

#endif

