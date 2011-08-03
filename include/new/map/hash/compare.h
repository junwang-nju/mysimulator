
#ifndef _Map_Hash_Compare_H_
#define _Map_Hash_Compare_H_

#include "map/hash/interface.h"

namespace mysimulator {

  template <unsigned int NH1, unsigned int NH2>
  int compare(const HashTable<NH1>& h1, const HashTable<NH2>& h2) {
    if(NH1!=NH2)  return NH1>NH2?1:-1;
    else {
      for(unsigned int i=0;i<NH1;++i)
        if(h1[i]!=h2[i])  return h1[i]>h2[i]?1:-1;
    }
    return 0;
  }

}

#endif

