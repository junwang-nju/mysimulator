
#ifndef _Geometry_Displacement_Operation_H_
#define _Geometry_Displacement_Operation_H_

#include "array/interface.h"
#include "geometry/boundary/free/interface.h"
#include "system/kind/name.h"

namespace mysimulator {

  template <SystemKindName KA, SystemKindName KB, unsigned int DIM>
  class __Displacement {

    public:

      template <typename T,ArrayKernelName K,
                typename T1,ArrayKernelName K1,
                typename T2,ArrayKernelName K2>
      static inline
      void Calc(Array<Intrinsic<T>,K>&,Array<Intrinsic<T1>,K1> const&,
                Array<Intrinsic<T2>,K2> const&, FreeSpace<DIM> const&) {
        assert("Not Implemented!\n");
      }

  };

  template <unsigned int DIM>
  class __Displacement<SystemKindName::Particle,SystemKindName::Particle,DIM> {

    public:

      template <typename T,ArrayKernelName K,
                typename T1,ArrayKernelName K1,
                typename T2,ArrayKernelName K2>
      static inline
      void Calc(Array<Intrinsic<T>,K>& A,Array<Intrinsic<T1>,K1> const& A1,
                Array<Intrinsic<T2>,K2> const& A2, FreeSpace<DIM> const&) {
        assert((bool)A);
        assert((bool)A1);
        assert((bool)A2);
        A=A1-A2;
      }

  };

}

#endif

