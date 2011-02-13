
#ifndef _Random_Generator_MT_SFMT_Input_Output_H_
#define _Random_Generator_MT_SFMT_Input_Output_H_

#include "data/random/random-generator-mt-sfmt.h"
#include "data/basic/input-base.h"
#include "data/basic/output-base.h"

namespace std {

  template <unsigned int LoopFac>
  OutputBase& operator<<(OutputBase& os, const SFMT<LoopFac>& G) {
    assert(IsAvailable(G));
    os<<LoopFac<<"\t";
    for(unsigned int i=0;i<SFMT<LoopFac>::NStatus;++i)
    for(unsigned int k=0;k<4;++k)
      os<<G[i].u[k]<<"\t";
    os<<*(G.idx);
    //os<<static_cast<const Vector<UniqueParameter128b>&>(G)<<"\t"<<*(G.idx);
    return os;
  }

  template <unsigned int LoopFac>
  InputBase& operator>>(InputBase& is, SFMT<LoopFac>& G) {
    assert(IsAvailable(G));
    unsigned int expLoopFac;
    is>>expLoopFac;
    if(expLoopFac!=LoopFac) Error("Imcompatible SFMT data");
    for(unsigned int i=0;i<SFMT<LoopFac>::NStatus;++i)
    for(unsigned int k=0;k<4;++k)
      is>>G[i].u[k];
    is>>*(G.idx);
    //is>>static_cast<Vector<UniqueParameter128b>&>(G)>>*(G.idx);
    return is;
  }

}

#endif


