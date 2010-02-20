
#ifndef _Free_Space_H_
#define _Free_Space_H_

#include "geometry-id.h"
#include "direct-displacement.h"

namespace std {

  class FreeSpace {

    public:

      static const unsigned int TypeID;

      FreeSpace() {}

      FreeSpace(const FreeSpace& FS) {
        myError("Cannot create from free-space object");
      }

      ~FreeSpace() {}

      FreeSpace& operator=(const FreeSpace& FS) { return *this; }

  };

  const unsigned int FreeSpace::TypeID=FreeSpaceType;

  void DisplacementFunc(const VectorBase<double>& va,
                        const VectorBase<double>& vb, VectorBase<double>& Dsp,
                        const FreeSpace& FS) {
    DirectDisplacement(va,vb,Dsp);
  }

}

#endif

