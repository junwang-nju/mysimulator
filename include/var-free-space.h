
#ifndef _Variable_Free_Space_H_
#define _Variable_Free_Space_H_

#include "free-space-base.h"

namespace std {

  class varFreeSpace : public FreeSpaceBase {

    typedef varFreeSpace  Type;

    typedef FreeSpaceBase ParentType;

    varFreeSpace() : ParentType() {}

    varFreeSpace(const Type&) {
      myError("Cannot create from variable Free-Space");
    }

    ~varFreeSpace() {}

    Type& operator=(const Type& vFS) { return *this; }

    Type& operator=(const FreeSpaceBase& FS) { return *this; }

    void clear() {}

    void allocate(const unsigned int Dim) {}

  };

}

#endif

