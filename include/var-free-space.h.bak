
#ifndef _Variable_Free_Space_H_
#define _Variable_Free_Space_H_

#include "free-space-base.h"
#include "var-vector.h"

namespace std {

  class varFreeSpace : public FreeSpaceBase<varVector> {

    public:

      typedef varFreeSpace  Type;

      typedef FreeSpaceBase<varVector> ParentType;

      varFreeSpace() : ParentType() {}

      varFreeSpace(const Type&) {
        myError("Cannot create from variable Free-Space");
      }

      ~varFreeSpace() {}

      Type& operator=(const Type& vFS) { return *this; }

      template <template <typename> class VecType>
      Type& operator=(const FreeSpaceBase<VecType>& FS) { return *this; }

      void clear() {}

      void allocate(const unsigned int Dim) {}

  };

}

#endif

