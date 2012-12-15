
#ifndef _System_Interaction_Function_Angle_GetPre_ForE_H_
#define _System_Interaction_Function_Angle_GetPre_ForE_H_

#include "array/interface.h"
#include "system/interaction/function/angle/pre-name.h"
#include "system/interaction/function/angle/neighbor-name.h"
#include "system/interaction/function/pairwise/pre-name.h"

namespace mysimulator {

  template <typename GT,unsigned int DIM> class InteractionFunction;

  template <typename GT,unsigned int DIM>
  void _get_pre_for_e_angle(
      Array<InteractionFunction<GT,DIM>*> const& _neighbor,
      Array<Double>& _pre) {
    assert((bool)_neighbor);
    assert((bool)_pre);
    InteractionFunction<GT,DIM>* P;
    P=_neighbor[AngleNeighborName::EdgeA];
    assert(P!=nullptr);
    _pre[AnglePreName::EdgeASQ]=P->_pre[PairwisePreName::DistanceSQ];
    P=_neighbor[AngleNeighborName::EdgeB];
    assert(P!=nullptr);
    _pre[AnglePreName::EdgeBSQ]=P->_pre[PairwisePreName::DistanceSQ];
  }

}

#endif

