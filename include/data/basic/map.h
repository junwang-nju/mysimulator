
#ifndef _Map_H_
#define _Map_H_

#include "data/basic/btree.h"
#include "data/basic/chain.h"

namespace std {

  template <typename KeyType, typename ValueType>
  struct Mapper : public Vector<BTree<KeyType,ValueType> > {
  };

}

#endif

