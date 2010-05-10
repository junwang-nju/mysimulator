
#ifndef _Interaction_Pairwise_Harmonic_H_
#define _Interaction_Pairwise_Harmonic_H_

#include "interaction-pairwise-base.h"
#include "functional-harmonic.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncPairwiseHarmonic(
    const Vector<double>* Coor, const unsigned int* Idx,
    const UniqueParameter* Prm, const unsigned int nIdx,
    Vector<double>*, const unsigned int,
    DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncHarmonic);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncPairwiseHarmonic(
    const Vector<double>* Coor, const unsigned int* Idx,
    const UniqueParameter* Prm, const unsigned int nIdx,
    Vector<double>*, const unsigned int,
    DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffHarmonic);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncPairwiseHarmonic(
    const Vector<double>* Coor, const unsigned int* Idx,
    const UniqueParameter* Prm, const unsigned int nIdx,
    Vector<double>*, const unsigned int,
    DistEvalMethod& DEval, const GeomType& Geo,
    double& Energy, Vector<double>* Gradient) {
    BFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothHarmonic);
  }

}

#endif

