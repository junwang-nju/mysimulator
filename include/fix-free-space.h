
#ifndef _Fixed_Free_Space_H_
#define _Fixed_Free_Space_H_

#include "free-space-base.h"
#include "ref-vector.h"

namespace std {

  template <unsigned int Dim>
  class fixFreeSpace : public FreeSpaceBase<refVector> {

    public:

      typedef fixFreeSpace<Dim>   Type;

      typedef FreeSpaceBase<refVector>       ParentType;

      fixFreeSpace() : ParentType() {}

      fixFreeSpace(const Type&) {
        myError("Cannot create from fixed Free space");
      }

      ~fixFreeSpace() {}

      Type& operator=(const Type& fFS) { return *this; }

      template <template <typename> class VecType>
      Type& operator=(const FreeSpaceBase<VecType>& FS) { return *this; }

  };

}

#endif

