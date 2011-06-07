
#ifndef _Binary_Tree_Allocate_H_
#define _Binary_Tree_Allocate_H_

#include "btree/interface.h"

namespace mysimulator {

  template <typename kT, typename vT>
  void allocate(BTree<kT,vT>& B) { release(B); }

  template <typename kT, typename vT>
  void imprint(BTree<kT,vT>& B, const BTree<kT,vT>& cB) { allocate(B); }

}

#endif

