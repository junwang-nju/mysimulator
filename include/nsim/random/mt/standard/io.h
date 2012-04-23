
#ifndef _Random_MT_Standard_IO_H_
#define _Random_MT_Standard_IO_H_

#include "random/mt/standard/interface.h"
#include "array/1d/io.h"

namespace mysimulator {

  void Write(const MersenneTwister<StandardMT>& Rnd) {
    Write(Rnd.s,"\t",Rnd.sloc);
  }

}

#endif

