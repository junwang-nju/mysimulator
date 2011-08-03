
#ifndef _Map_Hash_Allocate_H_
#define _Map_Hash_Allocate_H_

#include "map/hash/interface.h"

namespace mysimulator {

  template <unsigned int NH>
  void allocate(HashTable<NH>& hash) { release(hash); }

  template <unsigned int NH>
  void imprint(HashTable<NH>& h1, const HashTable<NH>& h2) { allocate(h1); }

}

#endif

