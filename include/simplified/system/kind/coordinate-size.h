
#ifndef _System_Kind_Coordinate_Size_H_
#define _System_Kind_Coordinate_Size_H_

#include "system/kind/name.h"
#include <cassert>

namespace mysimulator {

  unsigned int CoordinateSize(SystemKindName KN,unsigned int dim) {
    unsigned int ncoor=0;
    switch (KN) {
      case SystemKindName::Particle:  ncoor=dim;  break;
      case SystemKindName::Wall:      ncoor=dim+1;  break;
      default: assert(false);
    }
    return ncoor;
  }

}

#endif

