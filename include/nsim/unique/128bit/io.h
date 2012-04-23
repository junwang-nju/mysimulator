
#ifndef _Unique_128Bit_IO_H_
#define _Unique_128Bit_IO_H_

#include "unique/128bit/interface.h"
#include "intrinsic-type/io.h"

namespace mysimulator {

  void Write(const Unique128Bit& U) { Write(U.ullv[0],"\t",U.ullv[1]); }

}

#endif

