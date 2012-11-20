
#ifndef _System_Interface_H_
#define _System_Interface_H_

#include "array-2d/interface.h"
#include "system/kind/name.h"
#include "system/vec-type-selector.h"

namespace mysimulator {

  template <typename BT,unsigned int DIM>
  class System {

    public:

      typedef System<BT,DIM>  Type;

    private:

      Array<SystemKindName> __kind;
      Array2D<Float,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>  _X;
      Array2D<Float,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>  _V;
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME> _G;
      access_ptr<Double> _E;

  };

}

#endif

