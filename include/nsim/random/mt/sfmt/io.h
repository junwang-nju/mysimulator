
#ifndef _Random_MT_SFMT_IO_H_
#define _Random_MT_SFMT_IO_H_

#include "random/mt/sfmt/interface.h"
#include "array/1d/io.h"
#include "unique/128bit/io.h"

namespace mysimulator {

  template <unsigned int Fac>
  void Write(const MersenneTwister<SFMT,Fac>& RNG) {
    assert(RNG.IsValid());
    Write(Fac,"\t",RNG.s<<"\t"<<R.idx);
  }

}

#endif

