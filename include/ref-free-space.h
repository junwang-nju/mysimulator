
#ifndef _Reference_Free_Space_H_
#define _Reference_Free_Space_H_

#include "free-space-base.h"
#include "ref-vector.h"

namespace std {

  class refFreeSpace : public FreeSpaceBase<refVector> {

    public:

      typedef refFreeSpace  Type;

      typedef FreeSpaceBase<refVector> ParentType;

      refFreeSpace() : ParentType() {}

      refFreeSpace(const Type&) {
        myError("Cannot create from reference Free Space");
      }

      ~refFreeSpace() {}

      Type& operator=(const Type& rFS) { return *this; }

      template <template <typename> class VecType>
      Type& operator=(const FreeSpaceBase<VecType>& FS) { return *this; }

      template <template <typename> class VecType>
      void refer(const FreeSpaceBase<VecType>& FS) {}

  };

}

#endif

