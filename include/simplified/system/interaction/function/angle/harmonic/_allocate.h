
#ifndef _System_Interaction_Function_Angle_Harmonic_Allocate_H_
#define _System_Interaction_Function_Angle_Harmonic_Allocate_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/angle/harmonic/pre-name.h"
#include "system/interaction/function/angle/harmonic/post-name.h"
#include "system/interaction/function/angle/harmonic/vec-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <unsigned int DIM>
  void _allocate_func_angle_harmonic(
      Array<Double>& _pre, Array<Double>& _post,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec) {
    _pre.allocate(AngleHarmonicPreName::NumberPre);
    _post.allocate(AngleHarmonicPostName::NumberPost);
    _vec.allocate(AngleHarmonicVecName::NumberVec,DIM);
  }

}

#endif

