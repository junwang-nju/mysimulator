
#ifndef _System_Interaction_Function_Pairwise_Harmonic_Allocate_H_
#define _System_Interaction_Function_Pairwise_Harmonic_Allocate_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/pairwise/harmonic/pre-name.h"
#include "system/interaction/function/pairwise/harmonic/post-name.h"
#include "system/interaction/function/pairwise/harmonic/vec-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <unsigned int DIM>
  void _allocate_pair_harmonic(
      Array<Float>& _pre, Array<Float>& _post,
      Array2D<Float,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec) {
    _pre.allocate(PairHarmonicNumberPre);
    _post.allocate(PairHarmonicNumberPost);
    _vec.allocate(PairHarmonicNumberVec,DIM);
  }

}

#endif

