
#ifndef _System_Inteaction_Function_Dihedral_GetPre_forG_H_
#define _System_Inteaction_Function_Dihedral_GetPre_forG_H_

#include "system/interaction/function/dihedral/_get_pre_for_e.h"
#include "system/interaction/function/pairwise/pre-name.h"
#include "system/interaction/function/angle/pre-name.h"

namespace mysimulator {

  template <typename GT, unsigned int DIM>
  void _get_pre_for_g_dihedral(
      Array<InteractionFunction<GT,DIM>*> const& _neighbor,
      Array<Double>& _pre,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME> const&
        _vec) {
    _get_pre_for_e_dihedral(_neighbor,_pre,_vec);
    InteractionFunction<GT,DIM>* P;
    P=_neighbor[DihedralNeighborName::Axis];
    assert(P!=nullptr);
    _pre[DihedralPreName::AxisSQ]=P->_pre[PairwisePreName::DistanceSQ];
    P=_neighbor[DihedralNeighborName::DotAB];
    assert(P!=nullptr);
    _pre[DihedralPreName::DotBondAB]=-(P->_pre[AnglePreName::DotAB]);
    P=_neighbor[DihedralNeighborName::DotBC];
    assert(P!=nullptr);
    _pre[DihedralPreName::DotBondBC]=-(P->_pre[AnglePreName::DotAB]);
  }

}

#endif

