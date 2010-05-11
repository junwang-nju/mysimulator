
#ifndef _Interaction_Pairwise_CoreLJ612_H_
#define _Interaction_Pairwise_CoreLJ612_H_

#include "interaction-pairwise-base.h"
#include "functional-corelj612.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncPairwiseCoreLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncCoreLJ612);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncPairwiseCoreLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffCoreLJ612);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncPairwiseCoreLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothCoreLJ612);
  }

}

#endif

