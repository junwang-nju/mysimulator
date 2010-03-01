
#ifndef _Free_Space_Base_H_
#define _Free_Space_Base_H_

#include "geometry-id.h"
#include "displacement-direct.h"

namespace std {

  class FreeSpaceBase {

    public:

      static const unsigned int TypeID;

      FreeSpaceBase() {}

      FreeSpaceBase(const FreeSpaceBase& FS) {
        myError("Cannot create from free-space base object");
      }

      ~FreeSpaceBase() {}

      FreeSpaceBase& operator=(const FreeSpaceBase& FS) { return *this; }

      void clear() {}

  };

  const unsigned int FreeSpaceBase::TypeID=FreeSpaceType;

  void DisplacementFunc(const VectorBase<double>& va,
                        const VectorBase<double>& vb, VectorBase<double>& Dsp,
                        const FreeSpace& FS) {
    DisplacementFunc(va,vb,Dsp);
  }

}

#endif

