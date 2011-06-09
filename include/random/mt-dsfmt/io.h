
#ifndef _Random_MT_DSFMT_InputOutput_H_
#define _Random_MT_DSFMT_InputOutput_H_

#include "random/mt-dsfmt/interface.h"
#include "io/output/interface.h"
#include "io/input/interface.h"

namespace mysimulator {

  template <unsigned int LFac>
  OutputBase& operator<<(OutputBase& os, const MT_dSFMT<LFac>& G) {
    assert(IsValid(G));
    os<<LFac;
    for(unsigned int i=0;i<G.NStatus;++i) os<<"\t"<<G.s[i];
    os<<"\t"<<G.idx;
    return os;
  }

  template <unsigned int LFac>
  InputBase& operator>>(InputBase& is, MT_dSFMT<LFac>& G) {
    assert(IsValid(G));
    unsigned int rFac;
    is>>rFac;
    if(rFac!=LFac)  Error("Incompatible Factor for MT_dSFMT!");
    for(unsigned int i=0;i<G.NStatus;++i) is>>G.s[i];
    is>>G.idx;
    return is;
  }

}

#endif

