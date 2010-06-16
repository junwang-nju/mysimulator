
#ifndef _Wall_Type_H_
#define _Wall_Type_H_

#include "distance-evaluate-wall.h"

namespace std {

  enum WallTypeName {
    PlaneWallType=0,
    SphereWallType
  };

  const unsigned int WallShapeDataSize(const unsigned int walltype,
                                       const unsigned int dim) {
    if(walltype==PlaneWallType) return dim+dim;
    else if(walltype==SphereWallType) return 2+dim;
    else myError("Unknown Wall Type!");
    return 0;
  }

  template <typename DistEvalMethod, typename GeomType>
  void* WallDistanceFuncPointer(const unsigned int walltype) {
    typedef void (*DFType)(
                const Vector<double>*,const unsigned int*,
                const UniqueParameter*,DistEvalMethod&,const GeomType&);
    DFType df=NULL;
    if(walltype==PlaneWallType)
      df=(DistanceDisplacement2Plane<DistEvalMethod,GeomType>);
    else if(walltype==SphereWallType)
      df=(DistanceDisplacement2Sphere<DistEvalMethod,GeomType>);
    else myError("Unknown Wall Type!");
    return reinterpret_cast<void*>(df);
  }

}

#endif

