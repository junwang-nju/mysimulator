
#ifndef _Interaction_Pairwise_LJ612Cut_H_
#define _Interaction_Pairwise_LJ612Cut_H_

#include "interaction-pairwise-base.h"
#include "functional-lj612cut.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncPairwiseLJ612Cut(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncLJ612Cut);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncPairwiseLJ612Cut(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffLJ612Cut);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncPairwiseLJ612Cut(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothLJ612Cut);
  }

}

#endif

