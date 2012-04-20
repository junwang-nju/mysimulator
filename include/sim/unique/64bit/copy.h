
#ifndef _Unique_64Bit_Copy_H_
#define _Unique_64Bit_Copy_H_

#include "unique/64bit/interface.h"

namespace mysimulator {

  void Copy(Unique64Bit& U,const Unique64Bit& iU) { U.ll=iU.ll; }

}

#endif

