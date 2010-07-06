
/**
 * @file wall-type.h
 * @brief the name and operation for various walls
 *
 * This file contains the name for various walls and some procedures
 * to obtain the properties of walls.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Wall_Type_H_
#define _Wall_Type_H_

#include "distance-evaluate-wall.h"

namespace std {

  /**
   * @brief the name of various kinds of walls
   *
   * Here give the names of various kinds of walls. This eases the
   * access of wall types.
   */
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

