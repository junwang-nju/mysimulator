
#ifndef _System_Interaction_Function_Pairwise_LJ612_Allocate_H_
#define _System_Interaction_Function_Pairwise_LJ612_Allocate_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/pairwise/lj612/pre-name.h"
#include "system/interaction/function/pairwise/lj612/post-name.h"
#include "system/interaction/function/pairwise/lj612/vec-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <unsigned int DIM>
  void _allocate_func_pair_lj612(
      Array<Float>& _pre, Array<Float>& _post,
      Array2D<Float,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec) {
    _pre.allocate(PairLJ612PreName::PairLJ612NumberPre);
    _post.allocate(PairLJ612PostName::PairLJ612NumberPost);
    _vec.allocate(PairLJ612VecName::PairLJ612NumberVec,DIM);
  }

}

#endif

