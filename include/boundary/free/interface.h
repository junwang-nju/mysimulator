
#ifndef _Boundary_Free_Interface_H_
#define _Boundary_Free_Interface_H_

#include "io/error.h"

namespace mysimulator {

  struct FreeSpace {

    typedef FreeSpace   Type;

    FreeSpace() {}
    FreeSpace(const Type&) { Error("Copier of FreeSpace Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for FreeSpace Disabled!");
      return *this;
    }
    ~FreeSpace() {}

    void clearData() {}

  };

  bool IsValid(const FreeSpace&) { return true; }

  void release(FreeSpace&) {}

}

#endif

