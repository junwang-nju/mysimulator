
#ifndef _System_Interaction_Function_Dihedral_GetPre_forEG_H_
#define _System_Interaction_Function_Dihedral_GetPre_forEG_H_

#include "system/interaction/function/dihedral/_get_pre_for_g.h"

namespace mysimulator {

  template <typename GT,unsigned int DIM>
  void _get_pre_for_eg_dihedral(
      Array<InteractionFunction<GT,DIM>*> const& _neighbor,
      Array<Double>& _pre,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME> const&
        _vec) {
    _get_pre_for_g_dihedral(_neighbor,_pre,_vec);
  }

}

#endif

