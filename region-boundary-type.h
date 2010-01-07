
/**
 * @file region-boundary-type.h
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Region_Boundary_Type_H_
#define _Region_Boundary_Type_H_

namespace std {

  enum RegionBoundaryType {
    Close1_Open2=0,
    Close0_Open1,
    Open0_Close1,
    Open0_Open1,
    Close0_Close1
  };

}

#endif

