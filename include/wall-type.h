
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
    /**
     * @brief the type for plane wall
     */
    PlaneWallType=0,
    /**
     * @brief the type of spherical wall
     */
    SphereWallType
  };

  /**
   * @brief get the size of a certain shape of wall
   *
   * The size of data depends on the type of wall and the dimension
   * of the concerned space.
   *
   * @param walltype [in] the type of wall
   * @param dim [in] the dimension of the space
   * @return the size of data to describe wall
   */
  const unsigned int WallShapeDataSize(const unsigned int walltype,
                                       const unsigned int dim) {
    if(walltype==PlaneWallType) return dim+dim;
    else if(walltype==SphereWallType) return 2+dim;
    else myError("Unknown Wall Type!");
    return 0;
  }

  /**
   * @brief get the function pointer of distance calculation for a wall
   *
   * The function pointer for distance from a point to a wall depends
   * on the type of wall only. This is implemented by only a judgement.
   *
   * DistEvalMethod is the type of functor for distance evaluation.
   * GeomType is the type of the cncerned geometry.
   *
   * @param walltype [in] the type of wall
   * @return the pointer of the function to calculate distance from
   *         a point to a wall.
   * @note the output pointer is converted as pointer to void, so that
   *       the pointer usage is easier.
   */
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

