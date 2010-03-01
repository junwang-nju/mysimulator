
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

  };

}

#endif

