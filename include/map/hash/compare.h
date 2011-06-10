
#ifndef _Map_Element_Hash_Compare_H_
#define _Map_Element_Hash_Compare_H_

#include "map/hash/interface.h"

namespace mysimulator {

  template <unsigned int nhash1, unsigned int nhash2>
  int compare(const MapHash<nhash1>& H1, const MapHash<nhash2>& H2) {
    if(nhash1>nhash2)       return 1;
    else if(nhash1<nhash2)  return -1;
    else
      for(unsigned int i=0;i<nhash1;++i)
        if(H1(i)!=H2(i)) return H1(i)>H2(i)?1:-1;
    return 0;
  }

}

#endif

