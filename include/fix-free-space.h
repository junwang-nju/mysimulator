
#ifndef _Fixed_Free_Space_H_
#define _Fixed_Free_Space_H_

#include "free-space-base.h"

namespace std {

  template <unsigned int Dim>
  class fixFreeSpace : public FreeSpaceBase {

    public:

      typedef fixFreeSpace<Dim>   Type;

      typedef FreeSpaceBase       ParentType;

      fixFreeSpace() : ParentType() {}

      fixFreeSpace(const Type&) {
        myError("Cannot create from fixed Free space");
      }

      ~fixFreeSpace() {}

      Type& operator=(const Type& fFS) { return *this; }

      Type& operator=(const FreeSpaceBase& FS) { return *this; }

  };

}

#endif

