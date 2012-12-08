
#ifndef _System_Interaction_Function_Dihedral_MultiPeriodic_CmPhase_Allocate_H_
#define _System_Interaction_Function_Dihedral_MultiPeriodic_CmPhase_Allocate_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/dihedral/multi-periodic-common-phase/pre-name.h"
#include "system/interaction/function/dihedral/multi-periodic-common-phase/post-name.h"
#include "system/interaction/function/dihedral/multi-periodic-common-phase/vec-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <unsigned int DIM>
  void _allocate_func_dihedral_multi_periodic_common_phase(
      Array<Double>& _pre, Array<Double>& _post,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec) {
    _pre.allocate(DihedralMultiPeriodicCommonPhasePreName::NumberPre);
    _post.allocate(DihedralMultiPeriodicCommonPhasePostName::NumberPost);
    _vec.allocate(DihedralMultiPeriodicCommonPhaseVecName::NumberVec,DIM);
  }

}

#endif

