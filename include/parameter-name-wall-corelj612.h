
#ifndef _Parameter_Name_Wall_CoreLJ612_H_
#define _Parameter_Name_Wall_CoreLJ612_H_

#include "parameter-name-wall-base.h"
#include "parameter-name-corelj612.h"

namespace std {

  enum WallCoreLJ612ParameterName {
    WallCoreLJ612Radius=CoreLJ612Radius+WallBaseNumberParameter,
    WallCoreLJ612EnergyDepth=CoreLJ612EnergyDepth+WallBaseNumberParameter,
    WallCoreLJ612RadiusSQ=CoreLJ612RadiusSQ+WallBaseNumberParameter,
    WallCoreLJ612TwlfEnergyDepth=
      CoreLJ612TwlfEnergyDepth+WallBaseNumberParameter,
    WallCoreLJ612NumberParameter,
    WallCoreLJ612ParameterEnd,
  };

}

#include "wall-type.h"

namespace std {

  void allocateWallCoreLJ612Parameter(UniqueParameter* prm,
                                      const unsigned int walltype,
                                      const unsigned int dim) {
    unsigned int n=WallCoreLJ612ParameterEnd+WallShapeDataSize(walltype,dim);
    prm=new UniqueParameter[n];
    prm[WallShapeName]=walltype;
    prm[WallCoreLJ612NumberParameter]=n;
    prm[WallShapeParameterShift]=WallCoreLJ612ParameterEnd;
  }

  void allocateWallCoreLJ612Parameter(Vector<UniqueParameter>& prm,
                                      const unsigned int walltype,
                                      const unsigned int dim) {
    unsigned int n=WallCoreLJ612ParameterEnd+WallShapeDataSize(walltype,dim);
    allocate(prm,n);
    prm[WallShapeName]=walltype;
    prm[WallCoreLJ612NumberParameter]=n;
    prm[WallShapeParameterShift]=WallCoreLJ612ParameterEnd;
  }

  template <typename DistEvalMethod, typename GeomType>
  void GenerateParameterWallCoreLJ612(UniqueParameter* prm,
                                      const DistEvalMethod&,const GeomType&) {
    GenerateParameterCoreLJ612(prm+WallBaseNumberParameter);
    prm[WallDistanceFunc]=
      WallDistanceFuncPointer<DistEvalMethod,GeomType>(prm[WallShapeName].u);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GenerateParameterWallCoreLJ612(Vector<UniqueParameter>& prm,
                                      const DistEvalMethod& DEM,
                                      const GeomType& Geo) {
    GenerateParameterWallCoreLJ612(prm(),DEM,Geo);
  }

}

#endif
