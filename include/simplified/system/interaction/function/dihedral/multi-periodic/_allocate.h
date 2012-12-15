
#ifndef _System_Interaction_Function_Dihedral_MultiPeriodic_Allocate_H_
#define _System_Interaction_Function_Dihedral_MultiPeriodic_Allocate_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/dihedral/multi-periodic/pre-name.h"
#include "system/interaction/function/dihedral/multi-periodic/post-name.h"
#include "system/interaction/function/dihedral/multi-periodic/vec-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <unsigned int DIM>
  void _allocate_func_dihedral_multi_periodic(
      Array<Double>& _pre, Array<Double>& _post,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec) {
    _pre.allocate(DihedralMultiPeriodicPreName::NumberPre);
    _post.allocate(DihedralMultiPeriodicPostName::NumberPost);
    _vec.allocate(DihedralMultiPeriodicVecName::NumberVec,DIM);
  }

}

#endif

