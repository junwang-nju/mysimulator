
#ifndef _System_Interaction_Function_Pairwise_E_H_
#define _System_Interaction_Function_Pairwise_E_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/pairwise/pre-name.h"
#include "system/interaction/function/pairwise/vec-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  template <typename GT,unsigned int DIM> class InteractionFunction;
  class InteractionParameter;

  template <typename GT,unsigned int DIM>
  void _E_pairwise(
      Array2D<Float,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME> const& X,
      Array<UInt> const& ID, Array<Float>& _pre, Array<Float>& _post,
      Array2D<Float,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec,
      Array<InteractionFunction<GT,DIM>*> const& _neighbor,
      InteractionFuncDataState& _status,
      const InteractionParameter& P, GT const& Geo, double& Energy,
      float (*_distance_sq)(Array<Float>&,Array<Float> const&,
                            Array<Float> const&,GT const&),
      void (*_pre_2_post_for_e)(Array<Float> const&,Array<Float>&,
                                InteractionFuncDataState&,
                                const InteractionParameter&),
      void (*_efunc)(Array<Float> const&,const InteractionParameter&,float*)) {
    assert((bool)X);
    assert((bool)ID);
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)_vec);
    assert((bool)P);
    assert((bool)Geo);
    assert(_distance_sq!=nullptr);
    assert(_pre_2_post_for_e!=nullptr);
    assert(_efunc!=nullptr);
    if( _status.IsReady4Energy() ) {
      unsigned int I=ID[0], J=ID[1];
      _pre[PairwisePreName::PairDistanceSQ] =
        _distance_sq(_vec[PairwiseVecName::PairBondVecIJ],X[I],X[J],Geo);
      _pre_2_post_for_e(_pre,_post,_status,P);
    }
    float ee;
    _efunc(_post,P,&ee);
    Energy+=ee;
  }

}

#endif

