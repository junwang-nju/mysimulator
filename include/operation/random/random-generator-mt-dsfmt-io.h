
#ifndef _Random_Generator_MT_DSFMT_Input_Output_H_
#define _Random_Generator_MT_DSFMT_Input_Output_H_

#include "data/random/random-generator-mt-dsfmt.h"
#include "data/basic/input-base.h"
#include "data/basic/output-base.h"

namespace std {

  template <unsigned int LoopFac>
  OutputBase& operator<<(OutputBase& os, const dSFMT<LoopFac>& G) {
    assert(IsAvailable(G));
    os<<LoopFac<<"\t";
    for(unsigned int i=0;i<G.size;++i)
    for(unsigned int k=0;k<4;++k)
      os<<G[i].u[k]<<"\t";
    os<<*(G.idx);
    return os;
  }

  template <unsigned int LoopFac>
  InputBase& operator>>(InputBase& is, dSFMT<LoopFac>& G) {
    assert(IsAvailable(G));
    unsigned int expLoopFac;
    is>>expLoopFac;
    if(expLoopFac!=LoopFac) Error("Imcompatiable LoopFac for dSFMT");
    for(unsigned int i=0;i<G.size;++i)
    for(unsigned int k=0;k<4;++k)
      is>>G[i].u[k];
    is>>*(G.idx);
    return is;
  }

}

#endif


