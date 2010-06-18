
#ifndef _Parameter_Name_Wall_LJ612Cut_H_
#define _Parameter_Name_Wall_LJ612Cut_H_

#include "parameter-name-wall-base.h"
#include "parameter-name-lj612cut.h"

namespace std {

  enum WallLJ612CutParameterName {
    WallLJ612CutEqRadius=WallBaseNumberParameter+LJ612CutEqRadius,
    WallLJ612CutEqEnergyDepth=WallBaseNumberParameter+LJ612CutEqEnergyDepth,
    WallLJ612CutCutR=WallBaseNumberParameter+LJ612CutCutR,
    WallLJ612CutCutRSQ=WallBaseNumberParameter+LJ612CutCutRSQ,
    WallLJ612CutVc=WallBaseNumberParameter+LJ612CutVc,
    WallLJ612CutKc=WallBaseNumberParameter+LJ612CutKc,
    WallLJ612CutRealSigma6=WallBaseNumberParameter+LJ612CutRealSigma6,
    WallLJ612CutRealStrength=WallBaseNumberParameter+LJ612CutRealStrength,
    WallLJ612CutTwlfRealStrength=
        WallBaseNumberParameter+LJ612CutTwlfRealStrength,
    WallLJ612CutNumberParameter,
    WallLJ612CutParameterEnd
  };

}

#include "wall-type.h"

namespace std {

  void allocateWallLJ612CutParameter(UniqueParameter* prm,
                                     const unsigned int walltype,
                                     const unsigned int dim) {
    unsigned int n=WallLJ612CutParameterEnd+WallShapeDataSize(walltype,dim);
    prm=new UniqueParameter[n];
    prm[WallShapeName]=walltype;
    prm[WallLJ612CutNumberParameter]=n;
    prm[WallShapeParameterShift]=WallLJ612CutParameterEnd;
  }

  void allocateWallLJ612CutParameter(Vector<UniqueParameter>& prm,
                                     const unsigned int walltype,
                                     const unsigned int dim) {
    unsigned int n=WallLJ612CutParameterEnd+WallShapeDataSize(walltype,dim);
    allocate(prm,n);
    prm[WallShapeName]=walltype;
    prm[WallLJ612CutNumberParameter]=n;
    prm[WallShapeParameterShift]=WallLJ612CutParameterEnd;
  }

  template <typename DistEvalMethod, typename GeomType>
  void GenerateParameterWallLJ612Cut(UniqueParameter* prm,
                                     const DistEvalMethod&,const GeomType&) {
    GenerateParameterLJ612Cut(prm+WallBaseNumberParameter);
    prm[WallDistanceFunc]=
      WallDistanceFuncPointer<DistEvalMethod,GeomType>(prm[WallShapeName].u);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GenerateParameterWallLJ612Cut(Vector<UniqueParameter>& prm,
                                     const DistEvalMethod& DEM,
                                     const GeomType& Geo) {
    GenerateParameterWallLJ612Cut(prm(),DEM,Geo);
  }

}

#endif

