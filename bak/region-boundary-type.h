
/**
 * @file region-boundary-type.h
 * @brief constants indicating the types of region boundary 
 *
 * This file contains the declarations for the constants indicating the
 * type of boundary. This boundary information is used for the random
 * generators.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Region_Boundary_Type_H_
#define _Region_Boundary_Type_H_

namespace std {

  /**
   * @brief the type constants for region boundary
   *
   * A boundary in mathematics may be open or close. Here, for the
   * one-dimensional cases, the constants indicating the type of
   * the boundaries are given.
   */
  enum RegionBoundaryType {
    /**
     * @brief the boundary [1,2)
     */
    Close1_Open2=0,
    /**
     * @brief the boundary [0,1)
     */
    Close0_Open1,
    /**
     * @brief the boundary (0,1]
     */
    Open0_Close1,
    /**
     * @brief the boundary (0,1)
     */
    Open0_Open1,
    /**
     * @brief the boundary [0,1]
     */
    Close0_Close1
  };

}

#endif

