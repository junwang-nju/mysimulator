
#ifndef _Interaction_Centroid_Harmonic_H_
#define _Interaction_Centroid_Harmonic_H_

#include "interaction-centroid-base.h"
#include "functional-harmonic.h"
#include "parameter-name-centroid-harmonic.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncCentroidHarmonic(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>* tmv, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncCentroidBase(Coor,Idx,nIdx,Prm,tmv,DEval,Geo,Energy,FuncHarmonic);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncCentroidHarmonic(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>* tmv, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      Vector<double>* Gradient) {
    GFuncCentroidBase(Coor,Idx,nIdx,Prm,tmv,DEval,Geo,Gradient,DiffHarmonic);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncCentroidHarmonic(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>* tmv, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncCentroidBase(Coor,Idx,nIdx,Prm,tmv,DEval,Geo,
                      Energy,Gradient,BothHarmonic);
  }

}

#endif
