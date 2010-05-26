
#ifndef _Interaction_Core_Expanded_LJ612_H_
#define _Interaction_Core_Expanded_LJ612_H_

#include "interaction-core-expand-base.h"
#include "functional-lj612.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncCoreExpandLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncCoreExpandBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncLJ612);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncCoreExpandLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncCoreExpandBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffLJ612);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncCoreExpandLJ612(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncCoreExpandBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothLJ612);
  }

}

#endif
