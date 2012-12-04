
#ifndef _System_Interaction_Function_Pairwise_LJ612Cut_Allocate_H_
#define _System_Interaction_Function_Pairwise_LJ612Cut_Allocate_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/pairwise/lj612cut/pre-name.h"
#include "system/interaction/function/pairwise/lj612cut/post-name.h"
#include "system/interaction/function/pairwise/lj612cut/vec-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <unsigned int DIM>
  void _allocate_func_pair_lj612cut(
      Array<Double>& _pre, Array<Double>& _post,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec) {
    _pre.allocate(PairLJ612CutPreName::NumberPre);
    _post.allocate(PairLJ612CutPostName::NumberPost);
    _vec.allocate(PairLJ612CutVecName::NumberVec,DIM);
  }

}

#endif

