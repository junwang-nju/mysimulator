
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
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>const& X,
      Array<UInt> const& ID, Array<Double>& _pre, Array<Double>& _post,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec,
      Array<InteractionFunction<GT,DIM>*> const& _neighbor,
      InteractionFuncDataState& _status,
      const InteractionParameter& P, GT const& Geo, double& Energy,
      double (*_distance_sq)(Array<Double,__system_vec_type<DIM>::NAME>&,
                             Array<Double,__system_vec_type<DIM>::NAME> const&,
                             Array<Double,__system_vec_type<DIM>::NAME> const&,
                             GT const&),
      void (*_pre_2_post_for_e)(Array<Double> const&,Array<Double>&,
                                InteractionFuncDataState&,
                                const InteractionParameter&),
      void (*_efunc)(Array<Double> const&,const InteractionParameter&,double*)){
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
    if( !_status.IsReady4Energy() ) {
      unsigned int I=ID[0], J=ID[1];
      _pre[PairwisePreName::DistanceSQ] =
        _distance_sq(_vec[PairwiseVecName::BondVecIJ],X[I],X[J],Geo);
      _pre_2_post_for_e(_pre,_post,_status,P);
    }
    double ee;
    _efunc(_post,P,&ee);
    Energy+=ee;
  }

}

#endif

