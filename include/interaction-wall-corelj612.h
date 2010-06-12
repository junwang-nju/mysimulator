
#ifndef _Interaction_Wall_CoreLJ612_H_
#define _Interaction_Wall_CoreLJ612_H_

#include "interaction-wall-base.h"
#include "functional-corelj612.h"
#include "parameter-name-wall-corelj612.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncWallCoreLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncWallBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncCoreLJ612);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncWallCoreLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncWallBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffCoreLJ612);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncWallCoreLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncWallBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothCoreLJ612);
  }

}

#endif

