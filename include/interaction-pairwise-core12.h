
#ifndef _Interaction_Pairwise_Core12_H_
#define _Interaction_Pairwise_Core12_H_

#include "interaction-pairwise-base.h"
#include "functional-core12.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncPairwiseCore12(const Vector<double>* Coor, const unsigned int* Idx,
                           const UniqueParameter* Prm, const unsigned int nIdx,
                           Vector<double>*, const unsigned int,
                           DistEvalMethod& DEval, const GeomType& Geo,
                           double& Energy) {
    EFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncCore12);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncPairwiseCore12(const Vector<double>* Coor, const unsigned int* Idx,
                           const UniqueParameter* Prm, const unsigned int nIdx,
                           Vector<double>*, const unsigned int,
                           DistEvalMethod& DEval, const GeomType& Geo,
                           Vector<double>* Gradient) {
    GFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffCore12);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncPairwiseCore12(const Vector<double>* Coor, const unsigned int* Idx,
                           const UniqueParameter* Prm, const unsigned int nIdx,
                           Vector<double>*, const unsigned int,
                           DistEvalMethod& DEval, const GeomType& Geo,
                           double& Energy, Vector<double>* Gradient) {
    BFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothCore12);
  }

}

#endif

