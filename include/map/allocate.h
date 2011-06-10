
#ifndef _Map_Allocate_H_
#define _Map_Allocate_H_

#include "map/interface.h"
#include "chain/allocate.h"

namespace mysimulator {

  template <typename ktype, typename vtype>
  void allocate(Map<ktype,vtype>& M) {
    release(M);
    allocate(M.data);
  }

  template <typename ktype, typename vtype>
  void imprint(Map<ktype,vtype>& M, const Map<ktype,vtype>& cM) {
    allocate(M);
  }

}

#endif

