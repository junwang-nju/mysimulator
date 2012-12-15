
#ifndef _System_Interaction_Function_Dihedral_E_H_
#define _System_Interaction_Function_Dihedral_E_H_

#include "system/interaction/function/data-state.h"
#include "system/interaction/function/dihedral/_get_pre_for_e.h"

namespace mysimulator {

  class InteractionParameter;

  template <typename GT,unsigned int DIM>
  void _E_dihedral(
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
      void (*_displacement)(Array<Double,__system_vec_type<DIM>::NAME>&,
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
    assert(_displacement!=nullptr);
    assert(_pre_2_post_for_e!=nullptr);
    assert(_efunc!=nullptr);
    if( !_status.IsReady4Energy() ) {
      unsigned int I=ID[0],J=ID[1],K=ID[2],L=ID[3];
      _displacement(_vec[DihedralVecName::BondJI],X[J],X[I],Geo);
      _displacement(_vec[DihedralVecName::BondKJ],X[K],X[J],Geo);
      _displacement(_vec[DihedralVecName::BondLK],X[L],X[K],Geo);
      cross(_vec[DihedralVecName::NormA],
            _vec[DihedralVecName::BondJI],_vec[DihedralVecName::BondKJ]);
      cross(_vec[DihedralVecName::NormB],
            _vec[DihedralVecName::BondKJ],_vec[DihedralVecName::BondLK]);
      cross(_vec[DihedralVecName::CrossNorm],
            _vec[DihedralVecName::NormA],_vec[DihedralVecName::NormB]);
      if((bool)_neighbor) _get_pre_for_e_dihedral(_neighbor,_pre,_vec);
      else {
        _pre[DihedralPreName::IvNormASQ]=1/NormSQ(_vec[DihedralVecName::NormA]);
        _pre[DihedralPreName::IvNormBSQ]=1/NormSQ(_vec[DihedralVecName::NormB]);
      }
      _pre[DihedralPreName::DotNormAB]=Dot(_vec[DihedralVecName::NormA],
                                           _vec[DihedralVecName::NormB]);
      _pre[DihedralPreName::CrossNormAB]=Dot(_vec[DihedralVecName::BondKJ],
                                             _vec[DihedralVecName::CrossNorm]);
      _pre_2_post_for_e(_pre,_post,_status,P);
    }
    double ee;
    _efunc(_post,P,&ee);
    Energy+=ee;
  }

}

#endif

