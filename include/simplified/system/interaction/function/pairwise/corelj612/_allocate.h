
#ifndef _System_Interaction_Function_Pairwise_CoreLJ612_Allocate_H_
#define _System_Interaction_Function_Pairwise_CoreLJ612_Allocate_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/pairwise/corelj612/pre-name.h"
#include "system/interaction/function/pairwise/corelj612/post-name.h"
#include "system/interaction/function/pairwise/corelj612/vec-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <unsigned int DIM>
  void _allocate_func_pair_corelj612(
      Array<Double>& _pre, Array<Double>& _post,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec) {
    _pre.allocate(PairCoreLJ612PreName::NumberPre);
    _post.allocate(PairCoreLJ612PostName::NumberPost);
    _vec.allocate(PairCoreLJ612VecName::NumberVec,DIM);
  }

}

#endif

