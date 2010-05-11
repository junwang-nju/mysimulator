
#ifndef _Interaction_Pairwise_LJ1012_H_
#define _Interaction_Pairwise_LJ1012_H_

#include "interaction-pairwise-base.h"
#include "functional-lj1012.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncPairwiseLJ1012(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*,const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncLJ1012);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncPairwiseLJ1012(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*,const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffLJ1012);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncPairwiseLJ1012(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*,const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothLJ1012);
  }

}

#endif

