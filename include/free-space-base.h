
#ifndef _Free_Space_Base_H_
#define _Free_Space_Base_H_

#include "geometry-id.h"
#include "displacement-direct.h"

namespace std {

  template <template <typename> class VecType>
  class FreeSpaceBase {

    public:

      typedef FreeSpaceBase<VecType>  Type;

      static const unsigned int TypeID;

      static const bool IsGeometry;

      FreeSpaceBase() {}

      FreeSpaceBase(const Type& FS) {
        myError("Cannot create from free-space base object");
      }

      ~FreeSpaceBase() {}

      Type& operator=(const Type& FS) { return *this; }

      void clear() {}

  };

  template <template <typename> class VecType>
  const unsigned int FreeSpaceBase<VecType>::TypeID=FreeSpaceType;

  template <template <typename> class VecType>
  const bool FreeSpaceBase<VecType>::IsGeometry=true;

  template <template <typename> class VecType>
  void DisplacementFunc(const VectorBase<double>& va,
                        const VectorBase<double>& vb, VectorBase<double>& Dsp,
                        const FreeSpaceBase<VecType>& FS) {
    DisplacementFunc(va,vb,Dsp);
  }

}

#endif

