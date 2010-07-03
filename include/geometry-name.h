
/**
 * @file geometry-name.h
 * @brief the name of geometry
 *
 * This file contains the descriptions for the names of various geometry.
 *
 * @author Jun Wang (junwang.nju@gamil.com)
 */
#ifndef _Geometry_H_
#define _Geometry_H_

namespace std {

  /**
   * @brief the collection of names of geometry
   *
   * This is a collection of the names for various kinds of geometry.
   */
  enum GeometryIDName {
    /**
     * @brief the name for the geometry with no boundary
     */
    FreeSpaceType=0,
    /**
     * @brief the name of the geometry with periodicity along certain cooridinates
     */
    PeriodicBoxType
  };

}

#endif

