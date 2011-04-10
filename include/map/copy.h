
#ifndef _Map_Copy_H_
#define _Map_Copy_H_

#include "map/interface.h"
#include "chain/copy.h"

namespace mysimulator {

  template <typename ktype, typename vtype>
  void copy(Map<ktype,vtype>& M, const Map<ktype,vtype>& cM) {
    assert(IsValid(cM));
    release(M);
    copy(M.data,cM.data);
    M.update();
  }

}

#endif

