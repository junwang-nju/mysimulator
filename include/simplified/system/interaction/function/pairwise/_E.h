
#ifndef _System_Interaction_Function_Pairwise_E_H_
#define _System_Interaction_Function_Pairwise_E_H_

#include "system/vec-type-selector.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <typename GT,unsigned int DIM>
  void _E_pairwise(
      Array<Float,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME> const& X,
      Array<UInt> const& ID, Array<Float>& _pre, Array<Float>& _post,
      Array<Float
}

#endif

      void (*_E)(FVType const&,Array<UInt> const&,Array<Float>&,Array<Float>&,
                 FVType&, Array<Type*> const&,const InteractionParameter*,
                 GT const&,double&,
                 _distance_sq_func,_pre_post_func,_kernel_single_func);
