
#ifndef _Free_Space_H_
#define _Free_Space_H_

#include "data/name/geometry.h"
#include "operation/basic/error-op.h"

namespace std {

  struct FreeSpace {
    typedef FreeSpace   Type;
    static const unsigned int Name;
    
    FreeSpace() {}
    FreeSpace(const Type& G) { Error("Cannot create Free Space"); }
    Type& operator=(const Type& G) {
      Error("Cannot copy Free Space");
      return *this;
    }
  };

  const unsigned int FreeSpace::Name=FreeSpaceGeometry;

  bool IsAvailable(const FreeSpace& G) { return true; }
  bool IsGeometry(const FreeSpace& G) { return true; }
  void copy(FreeSpace& G, const FreeSpace& cG) {}
  void release(FreeSpace& G) {}
  void allocate(FreeSpace& G, const unsigned int dim) {}
  void refer(FreeSpace& G, const FreeSpace& rG) {}

}

#endif
