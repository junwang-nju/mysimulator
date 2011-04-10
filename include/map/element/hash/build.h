
#ifndef _Map_Element_Hash_Build_H_
#define _Map_Element_Hash_Build_H_

#include "map/element/hash/interface.h"
#include "hash/func.h"

namespace mysimulator {

  template <typename T, unsigned int nhash>
  void key2hash(const T& key, MapHash<nhash>& hash) {
  }

}

#endif

