
#ifndef _Geometry_Displacement_Calc_Operation_H_
#define _Geometry_Displacement_Calc_Operation_H_

#include "system/kind/name.h"
#include "array/interface.h"
#include "geometry/boundary/free/interface.h"

namespace mysimulator {

  template <SystemKindName KA, SystemKindName KB>
  class _Displacement {};

  template <>
  class _Displacement<SystemKindName::Particle, SystemKindName::Particle> {
    public:
      template <typename T,typename T1,typename T2>
      static
      inline void Calc(Array<T>& A,Array<T1> const& A1,Array<T2> const& A2,
                       FreeSpace const&) {
        A=A1-A2;
      }
  };

  template <>
  class _Displacement<SystemKindName::Particle,SystemKindName::Wall> {
    public:
      template <typename T,typename T1,typename T2>
      static
      inline void Calc(Array<T>& A,Array<T1> const& A1,Array<T2> const& A2,
                       FreeSpace const&) {
        assert("Not Implemented!\n");
      }
  };

}

#endif

