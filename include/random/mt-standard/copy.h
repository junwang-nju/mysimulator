
#ifndef _Random_MT_Standard_Copy_H_
#define _Random_MT_Standard_Copy_H_

#include "random/mt-standard/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  void copy(MT_Standard& G, const MT_Standard& cG) {
    assert(IsValid(G)&&IsValid(cG));
    unsigned int *p=G.s;
    unsigned int *cp=const_cast<unsigned int*>(cG.s);
    unsigned int *pend=p+MT_Standard::N;
    for(;p!=pend;)  copy(*(p++),*(cp++));
    copy(G.sl,cG.sl);
  }

}

#endif

