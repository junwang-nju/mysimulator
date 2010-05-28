
#ifndef _Interaction_Pairwise_FENE_H_
#define _Interaction_Pairwise_FENE_H_

#include "interaction-pairwise-base.h"
#include "functional-fene.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncPairwiseFENE(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*,const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncFENE);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncPairwiseFENE(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*,const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffFENE);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncPairwiseFENE(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*,const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothFENE);
  }

}

#endif

