
#ifndef _Interaction_Pairwise_Coulomb_H_
#define _Interaction_Pairwise_Coulomb_H_

#include "interaction-pairwise-base.h"
#include "functional-coulomb.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncPairwiseCoulomb(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncCoulomb);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncPairwiseCoulomb(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffCoulomb);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncPairwiseCoulomb(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothCoulomb);
  }

}

#endif

