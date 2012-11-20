
#ifndef _System_Interaction_Function_Pairwise_Interface_H_
#define _System_Interaction_Function_Pairwise_Interface_H_

#include "system/interaction/function/interface.h"
#include "geometry/distance/calc.h"
#include "system/interaction/function/pairwise/pre-name.h"
#include "system/interaction/function/pairwise/vec-name.h"

namespace mysimulator {

  template <typename GT,unsigned int DIM>
  class InteractionFunctionPairwise : public InteractionFunction<GT,DIM> {

    public:

      typedef InteractionFunctionPairwise<GT,DIM>   Type;
      typedef InteractionFunction<GT,DIM>     ParentType;
      typedef typename ParentType::FXType     FXType;
      typedef typename ParentType::DXType     DXType;

      InteractionFunctionPairwise() : ParentType() {}
      InteractionFunctionPairwise(const Type& F)
        : ParentType((ParentType const&)F) {}
      InteractionFunctionPairwise(Type&& F) : ParentType((ParentType&&)F) {}
      virtual ~InteractionFunctionPairwise() { ParentType::reset(); }

      Type& operator=(const Type& F) {
        ParentType::operator=((ParentType const&)F);
        return *this;
      }

      double _DistanceSQ(Array<Double,__system_vec_type<DIM>::NAME>& Dsp,
                         Array<Float,__system_vec_type<DIM>::NAME> const& B,
                         Array<Float,__system_vec_type<DIM>::NAME> const& C,
                         GT const& _Geo) {
        return DistanceSQ<SystemKindName::Particle,SystemKindName::Particle>(
                  Dsp,B,C,_Geo);
      }

      virtual
      void E(FXType const& X, Array<UInt> const& ID,
             const InteractionParameter* P, GT const& Geo, double& Energy) {
        assert((bool)X);
        assert((bool)ID);
        assert(P!=NULL);
        assert((bool)Geo);
        if( (ParentType::_status & InteractionFuncDataState::EDataOK) ==
            InteractionFuncDataState::EDataOK ) {
          unsigned int I=ID[0], J=ID[1];
          ParentType::_pre[PairwisePreName::PairDistanceSQ]=
            _DistanceSQ(ParentType::_vec[PairwiseVecName::PairBondVecIJ],
                        X[I],X[J],Geo);
          Pre2Post4E(P);
        }
        double ee;
        EFunc(P,&ee);
        Energy+=ee;
      }

      virtual void EFunc(const InteractionParameter*, double*) = 0;
      virtual void Pre2Post4E(const InteractionParameter*) = 0;

  };

}

#endif

