
#ifndef _Unique_64Bit_IO_H_
#define _Unique_64Bit_IO_H_

#include "unique/64bit/interface.h"
#include "intrinsic-type/io.h"

namespace mysimulator {

  void Write(const Unique64Bit& U) { Write(U.ull); }

}

#endif

