
#ifndef _Interaction_Wall_LJ612Cut_H_
#define _Interaction_Wall_LJ612Cut_H_

#include "interaction-wall-base.h"
#include "functional-lj612cut.h"
#include "parameter-name-wall-lj612cut.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncWallLJ612Cut(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*,const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    assert((Prm[WallShapeName].u!=SphereWallType)||
           (Prm[Prm[WallShapeParameterShift].u+1].d>0)||
           (Prm[WallLJ612CutCutR].d<Prm[Prm[WallShapeParameterShift].u].d));
    EFuncWallBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncLJ612Cut);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncWallLJ612Cut(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*,const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    assert((Prm[WallShapeName].u!=SphereWallType)||
           (Prm[Prm[WallShapeParameterShift].u+1].d>0)||
           (Prm[WallLJ612CutCutR].d<Prm[Prm[WallShapeParameterShift].u].d));
    GFuncWallBase(Coor,Idx,Prm,DEval,Geo,Gradient,DiffLJ612Cut);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncWallLJ612Cut(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*,const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    assert((Prm[WallShapeName].u!=SphereWallType)||
           (Prm[Prm[WallShapeParameterShift].u+1].d>0)||
           (Prm[WallLJ612CutCutR].d<Prm[Prm[WallShapeParameterShift].u].d));
    BFuncWallBase(Coor,Idx,Prm,DEval,Geo,Energy,Gradient,BothLJ612Cut);
  }

}

#endif
