
#ifndef _System_Interaction_Function_Pairwise_LJ1012_Allocate_H_
#define _System_Interaction_Function_Pairwise_LJ1012_Allocate_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/pairwise/lj1012/pre-name.h"
#include "system/interaction/function/pairwise/lj1012/post-name.h"
#include "system/interaction/function/pairwise/lj1012/vec-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <unsigned int DIM>
  void _allocate_func_pair_lj1012(
      Array<Double>& _pre, Array<Double>& _post,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec) {
    _pre.allocate(PairLJ1012PreName::NumberPre);
    _post.allocate(PairLJ1012PostName::NumberPost);
    _vec.allocate(PairLJ1012VecName::NumberVec,DIM);
  }

}

#endif

