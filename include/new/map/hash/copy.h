
#ifndef _Map_Hash_Copy_H_
#define _Map_Hash_Copy_H_

#include "map/hash/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <unsigned int NH>
  void copy(HashTable<NH>& h1, const HashTable<NH>& h2) {
    for(unsigned int i=0;i<NH;++i)  copy(h1[i],h2[i]);
  }

}

#endif

