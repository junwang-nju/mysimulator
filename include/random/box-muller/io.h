
#ifndef _Random_Box_Muller_InputOutput_H_
#define _Random_Box_Muller_InputOutput_H_

#include "random/box-muller/interface.h"
#include "io/output/interface.h"
#include "io/input/interface.h"

namespace mysimulator {

  template <typename UniformRNG>
  OutputBase& operator<<(OutputBase& os, const BoxMuller<UniformRNG>& G) {
    assert(IsValid(G));
    os<<G.urng<<"\t";
    unsigned long long *p;
    p=reinterpret_cast<unsigned long long*>(const_cast<double*>(G.s));
    for(unsigned int i=0;i<3;++i) os<<p[i]<<"\t";
    os<<G.isSecond;
    return os;
  }

  template <typename UniformRNG>
  InputBase& operator>>(InputBase& is, BoxMuller<UniformRNG>& G) {
    assert(IsValid(G));
    is>>G.urng;
    unsigned long long *p;
    p=reinterpret_cast<unsigned long long*>(const_cast<double*>(G.s));
    for(unsigned int i=0;i<3;++i) is>>p[i];
    is>>G.isSecond;
    return is;
  }

}

#endif

