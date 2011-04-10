
#ifndef _Random_MT_Standard_InputOutput_H_
#define _Random_MT_Standard_InputOutput_H_

#include "random/mt-standard/interface.h"
#include "io/output/interface.h"
#include "io/input/interface.h"

namespace mysimulator {

  OutputBase& operator<<(OutputBase& os, const MT_Standard& G) {
    assert(IsValid(G));
    for(unsigned int i=0;i<MT_Standard::N;++i)  os<<G.s[i]<<"\t";
    os<<G.sl;
    return os;
  }

  InputBase& operator>>(InputBase& is, MT_Standard& G) {
    for(unsigned int i=0;i<MT_Standard::N;++i)  is>>G.s[i];
    is>>G.sl;
    return is;
  }

}

#endif

