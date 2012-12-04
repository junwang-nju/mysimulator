
#ifndef _System_Interaction_Function_Angle_EG_H_
#define _System_Interaction_Function_Angle_EG_H_

#include "system/vec-type-selector.h"
#include "system/interaction/function/data-state.h"
#include "system/interaction/function/angle/_get_pre_for_eg.h"
#include "system/interaction/function/angle/vec-name.h"
#include "system/interaction/function/angle/post-name.h"
#include "array-2d/interface.h"

namespace mysimulator {

  class InteractionParameter;

  template <typename GT,unsigned int DIM>
  void _EG_pairwise(
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>const& X,
      Array<UInt> const& ID, Array<Double>& _pre, Array<Double>& _post,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& _vec,
      Array<InteractionFunction<GT,DIM>*> const& _neighbor,
      InteractionFuncDataState& _status,
      const InteractionParameter& P, GT const& Geo,double& Energy,
      Array2D<Double,ArrayKernelName::SSE,__system_vec_type<DIM>::NAME>& Grad,
      double (*_distance_sq)(Array<Double,__system_vec_type<DIM>::NAME>&,
                             Array<Double,__system_vec_type<DIM>::NAME> const&,
                             Array<Double,__system_vec_type<DIM>::NAME> const&,
                             GT const&),
      void (*_displacement)(Array<Double,__system_vec_type<DIM>::NAME>&,
                            Array<Double,__system_vec_type<DIM>::NAME> const&,
                            Array<Double,__system_vec_type<DIM>::NAME> const&,
                            GT const&),
      void (*_pre_2_post_for_eg)(Array<Double> const&,Array<Double>&,
                                 InteractionFuncDataState&,
                                 const InteractionParameter&),
      void (*_egfunc)(Array<Double> const&,const InteractionParameter&,
                      double*,double*)) {
    assert((bool)X);
    assert((bool)ID);
    assert((bool)_pre);
    assert((bool)_post);
    assert((bool)_vec);
    assert((bool)P);
    assert((bool)Geo);
    assert((bool)Grad);
    assert(_distance_sq!=nullptr);
    assert(_pre_2_post_for_eg!=nullptr);
    assert(_egfunc!=nullptr);
    unsigned int I=ID[0], J=ID[1], K=ID[2];
    if( !_status.IsReady4EnergyGradient() ) {
      _displacement(_vec[AngleVecName::BondIJ],X[I],X[J],Geo);
      _displacement(_vec[AngleVecName::BondKJ],X[K],X[J],Geo);
      if((bool)_neighbor) _get_pre_for_eg_angle(_neighbor,_pre);
      else {
        _pre[AnglePreName::EdgeASQ]=NormSQ(_vec[AngleVecName::BondIJ]);
        _pre[AnglePreName::EdgeBSQ]=NormSQ(_vec[AngleVecName::BondKJ]);
      }
      _pre[AnglePreName::DotAB] =
        Dot(_vec[AngleVecName::BondIJ],_vec[AngleVecName::BondKJ]);
      _pre_2_post_for_eg(_pre,_post,_status,P);
      _vec[AngleVecName::NormI] =
        _vec[AngleVecName::BondKJ] * Double(_post[AnglePostName::IvRabSin]) -
        _vec[AngleVecName::BondIJ] * Double(_post[AnglePostName::IvRaSQCtg]);
      _vec[AngleVecName::NormK] =
        _vec[AngleVecName::BondIJ] * Double(_post[AnglePostName::IvRabSin]) -
        _vec[AngleVecName::BondKJ] * Double(_post[AnglePostName::IvRbSQCtg]);
    }
    double ee,ef;
    _egfunc(_post,P,&ee,&ef);
    Energy+=ee;
    _vec[AngleVecName::ScaleNormI]=Double(-ef)*_vec[AngleVecName::NormI];
    _vec[AngleVecName::ScaleNormK]=Double(-ef)*_vec[AngleVecName::NormK];
    _Grad[I]+=_vec[AngleVecName::ScaleNormI];
    _Grad[K]+=_vec[AngleVecName::ScaleNormK];
    _Grad[J]-=_vec[AngleVecName::ScaleNormI] + _vec[AngleVecName::ScaleNormK];
  }

}

#endif

