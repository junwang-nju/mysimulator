
#ifndef _System_Interaction_Function_Pairwise_Core12_Allocate_H_
#define _System_Interaction_Function_Pairwise_Core12_Allocate_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/pairwise/core12/pre-name.h"
#include "system/interaction/function/pairwise/core12/post-name.h"
#include "system/interaction/function/pairwise/core12/vec-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <unsigned int DIM>
  void _allocate_func_pair_core12(
      Array<Float>& _pre, Array<Float>& _post,
      Array2D<Float,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec) {
    _pre.allocate(PairCore12PreName::PairCore12NumberPre);
    _post.allocate(PairCore12PostName::PairCore12NumberPost);
    _vec.allocate(PairCore12VecName::PairCore12NumberVec,DIM);
  }

}

#endif

