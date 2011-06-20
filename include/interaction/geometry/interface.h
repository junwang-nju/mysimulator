
#ifndef _Interaction_Geometry_H_
#define _Interaction_Geometry_H_

#include "io/error.h"

namespace mysimulator {

  template<template<typename>class DBuffer,typename GeomType,typename T=double>
  struct InteractionGeometry {

    typedef InteractionGeometry<DBuffer,GeomType,T> Type;

    DBuffer<T>  DB;
    GeomType   Geo;

    InteractionGeometry() : DB(), Geo() {}
    InteractionGeometry(const Type&) {
      Error("Copier of InteractionGeometry Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= of InteractionGeometry Disabled!");
      return *this;
    }
    ~InteractionGeometry() { clearData(); }

    void clearData() { release(DB); release(Geo); }
    const unsigned int Dimension() const { return DB.Dimension(); }
    const unsigned int NumUnit() const { return DB.UnitNumber(); }

  };

  template<template<typename>class DBuffer,typename GeomType,typename T>
  bool IsValid(const InteractionGeometry<DBuffer,GeomType,T>& G) {
    return IsValid(G.DB)&&IsValid(G.Geo);
  }

  template<template<typename>class DBuffer,typename GeomType,typename T>
  void release(InteractionGeometry<DBuffer,GeomType,T>& G) { G.clearData(); }

}

#endif

