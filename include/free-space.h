
#ifndef _Free_Space_H_
#define _Free_Space_H_

#include "geometry-id.h"
#include "displacement-direct.h"

namespace std {

  template <template <typename> class VecType>
  class FreeSpace {

    public:

      typedef FreeSpace<VecType>  Type;

      static const unsigned int TypeID;

      static const bool IsGeometry;

      FreeSpace() {}

      FreeSpace(const Type& FS) {
        myError("Cannot create from free-space object");
      }

      ~FreeSpace() {}

      Type& operator=(const Type& FS) { return *this; }

      template <template <typename> class iVecType>
      Type& operator=(const FreeSpace<iVecType>& FS) { return *this; }

      void clear() {}

      void allocate(const unsigned int Dim) { myError("Not Available"); }

      template <template <typename> class iVecType>
      void refer(const FreeSpace<iVecType>& FS) { myError("Not Available"); }

  };

  template <template <typename> class VecType>
  const unsigned int FreeSpace<VecType>::TypeID=FreeSpaceType;

  template <template <typename> class VecType>
  const bool FreeSpace<VecType>::IsGeometry=true;

  template <>
  void FreeSpace<varVector>::allocate(const unsigned int Dim) {}

  template <template <typename> class iVecType>
  void FreeSpace<refVector>::refer(const FreeSpace<iVecType>& FS) {}

  template <template <typename> class VecType>
  void DisplacementFunc(const VectorBase<double>& va,
                        const VectorBase<double>& vb, VectorBase<double>& Dsp,
                        const FreeSpace<VecType>& FS) {
    DisplacementFunc(va,vb,Dsp);
  }

}

#endif

