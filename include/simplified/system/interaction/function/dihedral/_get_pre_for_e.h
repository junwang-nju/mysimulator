
#ifndef _System_Interaction_Function_Dihedral_GetPre_forE_H_
#define _System_Interaction_Function_Dihedral_GetPre_forE_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/dihedral/pre-name.h"
#include "system/interaction/function/dihedral/vec-name.h"
#include "system/interaction/function/dihedral/neighbor-name.h"
#include "system/interaction/function/angle/post-name.h"
#include "array-2d/interface.h"
#include "basic/util/square.h"

namespace mysimulator {

  template <typename GT,unsigned int DIM> class InteractionFunction;

  template <typename GT,unsigned int DIM>
  void _get_pre_for_e_dihedral(
      Array<InteractionFunction<GT,DIM>*> const& _neighbor,
      Array<Double>& _pre,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME> const&
        _vec) {
    assert((bool)_neighbor);
    assert((bool)_pre);
    InteractionFunction<GT,DIM>* P;
    P=_neighbor[DihedralNeighborName::NormA];
    assert(P!=nullptr);
    _pre[DihedralPreName::IvNormASQ] =
      P->_status.IsReady4Gradient() ?
        __square(P->_post[AnglePostName::IvRabSin]) :
        1./NormSQ(_vec[DihedralVecName::NormA]);
    P=_neighbor[DihedralNeighborName::NormB];
    assert(P!=nullptr);
    _pre[DihedralPreName::IvNormBSQ] =
      P->_status.IsReady4Gradient() ?
        __square(P->_post[AnglePostName::IvRabSin]) :
        1./NormSQ(_vec[DihedralVecName::NormB]);
  }

}

#endif

