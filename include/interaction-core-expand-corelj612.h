
#ifndef _Interaction_Core_Expanded_CoreLJ612_H_
#define _Interaction_Core_Expanded_CoreLJ612_H_

#include "interaction-core-expand-base.h"
#include "functional-corelj612.h"
#include "parameter-name-core-expand-corelj612.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncCoreExpandCoreLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncCoreExpandBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncCoreLJ612);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncCoreExpandCoreLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncCoreExpandBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffCoreLJ612);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncCoreExpandCoreLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncCoreExpandBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothCoreLJ612);
  }

}

#endif

