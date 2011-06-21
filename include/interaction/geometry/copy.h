
#ifndef _Interaction_Geometry_Copy_H_
#define _Interaction_Geometry_Copy_H_

#include "interaction/geometry/interface.h"

namespace mysimulator {

  template<template<typename>class DBuffer,typename GeomType,typename T>
  void copy(InteractionGeometry<DBuffer,GeomType,T>& IG,
            const InteractionGeometry<DBuffer,GeomType,T>& cIG) {
    assert(IsValid(IG)&&IsValid(cIG));
    copy(IG.DB,cIG.DB);
    copy(IG.Geo,cIG.Geo);
  }

}

#endif

