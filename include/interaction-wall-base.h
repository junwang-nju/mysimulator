
#ifndef _Interaction_Wall_Base_H_
#define _Interaction_Wall_Base_H_

#include "vector.h"
#include "unique-parameter.h"
#include "parameter-name-wall-base.h"
#include <cmath>

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncWallBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy,
      void (*efunc)(const double,const UniqueParameter*,double&)) {
    typedef void (*DistFunc)(
                const Vector<double>*,const unsigned int*,
                const UniqueParameter*,DistEvalMethod&,const GeomType&);
    static_cast<DistFunc>(Prm[WallDistanceFunc].ptr)(
        Coor,Idx,Prm+WallShapeParameterShift,DEval,Geo);
    double dsq=DEval();
    double ee;
    efunc(dsq,Prm+WallBaseNumberParameter,ee);
    Energy+=ee;
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncWallBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient,
      void (*gfunc)(const double,const UniqueParameter*,double&)) {
    typedef void (*DistFunc)(
                const Vector<double>*,const unsigned int*,
                const UniqueParameter*,DistEvalMethod&,const GeomType&);
    static_cast<DistFunc>(Prm[WallDistanceFunc].ptr)(
        Coor,Idx,Prm+WallShapeParameterShift,DEval,Geo);
    double dsq=DEval();
    double ef;
    gfunc(dsq,Prm+WallBaseNumberParameter,ef);
    shift(Gradient[Idx[0]],+ef,DEval.displacementvec);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncWallBase(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient,
      void (*bfunc)(const double,const UniqueParameter*,double&,double&)) {
    typedef void (*DistFunc)(
                const Vector<double>*,const unsigned int*,
                const UniqueParameter*,DistEvalMethod&,const GeomType&);
    static_cast<DistFunc>(Prm[WallDistanceFunc].ptr)(
        Coor,Idx,Prm+WallShapeParameterShift,DEval,Geo);
    double dsq=DEval();
    double ee,ef;
    bfunc(dsq,Prm+WallBaseNumberParameter,ee,ef);
    Energy+=ee;
    shift(Gradient[Idx[0]],+ef,DEval.displacementvec);
  }

}

#endif
