
#ifndef _Random_BoxMuller_InputOutput_H_
#define _Random_BoxMuller_InputOutput_H_

#include "random/box-muller/interface.h"

namespace mysimulator {

  template <typename UniformRNG>
  OutputBase& operator<<(OutputBase& os, const BoxMuller<UniformRNG>& R) {
    assert(IsValid(R));
    os<<R.urng<<"\t";
    unsigned long long *p;
    p=reinterpret_cast<unsigned long long*>(const_cast<double*>(R.s.start));
    os<<p[0]<<"\t"<<p[1]<<"\t"<<p[2]<<"\t"<<R.isSecond;
    return os;
  }

  template <typename UniformRNG>
  InputBase& operator>>(InputBase& is, BoxMuller<UniformRNG>& R) {
    assert(IsValid(R));
    is>>R.urng;
    unsigned long long *p;
    p=reinterpret_cast<unsigned long long*>(R.s.start);
    is>>p[0]>>p[1]>>p[2]>>R.isSecond;
    return is;
  }

}

#endif

