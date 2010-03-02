
#ifndef _Reference_Free_Space_H_
#define _Reference_Free_Space_H_

#include "free-space-base.h"

namespace std {

  class refFreeSpace : public FreeSpaceBase {

    typedef refFreeSpace  Type;

    typedef FreeSpaceBase ParentType;

    refFreeSpace() : ParentType() {}

    refFreeSpace(const Type&) {
      myError("Cannot create from reference Free Space");
    }

    ~refFreeSpace() {}

    Type& operator=(const Type& rFS) { return *this; }

    Type& operator=(const FreeSpaceBase& FS) { return *this; }

    void refer(const FreeSpaceBase& FS) {}

  };

}

#endif

