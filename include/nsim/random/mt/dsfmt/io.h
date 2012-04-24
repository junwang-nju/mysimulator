
#ifndef _Random_MT_dSFMT_IO_H_
#define _Random_MT_dSFMT_IO_H_

#include "random/mt/dsfmt/interface.h"
#include "array/1d/io.h"
#include "unique/128bit/io.h"

namespace mysimulator {

  template <unsigned int Fac>
  void Write(const MersenneTwister<dSFMT,Fac>& R) {
    assert(R.IsValid());
    Write(Fac,"\t",R.s,"\t",R.idx);
  }

}

#endif

