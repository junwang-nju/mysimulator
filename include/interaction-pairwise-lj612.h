
#ifndef _Interaction_Pairwise_LJ612_H_
#define _Interaction_Pairwise_LJ612_H_

#include "interaction-pairwise-base.h"
#include "functional-lj612.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncPairwiseLJ612(const Vector<double>* Coor, const unsigned int* Idx,
                          const UniqueParameter* Prm, const unsigned int nIdx,
                          Vector<double>*, const unsigned int,
                          DistEvalMethod& DEval, const GeomType& Geo,
                          double& Energy) {
    EFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncLJ612);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncPairwiseLJ612(const Vector<double>* Coor, const unsigned int* Idx,
                          const UniqueParameter* Prm, const unsigned int nIdx,
                          Vector<double>*, const unsigned int,
                          DistEvalMethod& DEval, const GeomType& Geo,
                          Vector<double>* Gradient) {
    GFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffLJ612);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncPairwiseLJ612(const Vector<double>* Coor, const unsigned int* Idx,
                          const UniqueParameter* Prm, const unsigned int nIdx,
                          Vector<double>*, const unsigned int,
                          DistEvalMethod& DEval, const GeomType& Geo,
                          double& Energy, Vector<double>* Gradient) {
    BFuncPairwiseBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothLJ612);
  }

}

#endif

