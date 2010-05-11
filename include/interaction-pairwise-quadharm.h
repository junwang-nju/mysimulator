
#ifndef _Interaction_Pairwise_QuadrupleHarmonic_H_
#define _Interaction_Pairwise_QuadrupleHarmonic_H_

#include "interaction-pairwise-base.h"
#include "functional-quadharm.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncPairwiseQuadHarm(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncQuadHarm);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncPairwiseQuadHarm(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffQuadHarm);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncPairwiseQuadHarm(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothQuadHarm);
  }

}

#endif

