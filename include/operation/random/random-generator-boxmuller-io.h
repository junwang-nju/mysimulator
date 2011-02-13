
#ifndef _Random_Generator_BoxMuller_Input_Output_H_
#define _Random_Generator_BoxMuller_Input_Output_H_

#include "data/random/random-generator-boxmuller.h"
#include "data/basic/input-base.h"
#include "data/basic/output-base.h"

namespace std {

  template <typename UniformRNG>
  OutputBase& operator<<(OutputBase& os, const BoxMuller<UniformRNG>& G) {
    os<<*(G.urng)<<"\t";
    unsigned long long int *p;
    p=reinterpret_cast<unsigned long long int*>(const_cast<double*>(G.data));
    for(unsigned int i=0;i<3;++i) os<<p[i]<<"\t";
    os<<*(G.isSecond);
    return os;
  }
  template <typename UniformRNG>
  InputBase& operator>>(InputBase& is, BoxMuller<UniformRNG>& G) {
    is>>*(G.urng);
    unsigned long long int *p;
    p=reinterpret_cast<unsigned long long int*>(G.data);
    for(unsigned int i=0;i<3;++i) is>>p[i];
    is>>*(G.isSecond);
    return is;
  }

}

#endif

