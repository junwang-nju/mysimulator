
#ifndef _Wall_Type_H_
#define _Wall_Type_H_

#include "distance-evaluate-wall.h"

namespace std {

  enum WallTypeName {
    PlaneType=0,
    SphereType
  };

  const unsigned int WallShapeDataSize(const unsigned int walltype,
                                       const unsigned int dim) {
    if(walltype==PlaneType) return dim+dim;
    else if(walltype==SphereType) return 2+dim;
    else myError("Unknown Wall Type!");
    return 0;
  }

  template <typename DistEvalMethod, typename GeomType>
  void* WallDistanceFuncPointer(const unsigned int walltype) {
    typedef void (*DFType)(
                const Vector<double>*,const unsigned int*,
                const UniqueParameter*,DistEvalMethod&,const GeomType&);
    DFType df=NULL;
    if(walltype==PlaneType)
      df=(DistanceDisplacement2Plane<DistEvalMethod,GeomType>);
    else if(walltype==SphereType)
      df=(DistanceDisplacement2Sphere<DistEvalMethod,GeomType>);
    else myError("Unknown Wall Type!");
    return reinterpret_cast<void*>(df);
  }

}

#endif

