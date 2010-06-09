
#ifndef _Distance_Evaluate_Wall_H_
#define _Distance_Evaluate_Wall_H_

#include "vector.h"
#include "unique-parameter.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void DistanceDisplacement2Plane(
      const Vector<double>* Coor, const unsigned int*, 
      const UniqueParameter* Plane,
      DistEvalMethod& DEval, const GeomType& Geo) {
    DisplacementFunc(Coor[0](),static_cast<const double*>(Plane),Coor[0].size,
                     DEval.displacement,Geo);
    DEval()=dot(static_cast<const double*>(Plane+Coor[0].size),
                DEval.displacement,Coor[0].size);
    assign(DEval.displacement,static_cast<const double*>(Plane+Coor[0].size),
           Coor[0].size);
    scale(DEval.displacementvec,DEval());
  }

  template <typename DistEvalMethod, typename GeomType>
  void DistanceDisplacement2Sphere(
      const Vector<double>* Coor, const unsigned int*,
      const UniqueParameter* Sphere,
      DistEvalMethod& DEval, const GeomType& Geo) {
    DistanceDisplacementFunc(Coor[0](),static_cast<const double*>(Sphere+1),
                             Coor[0].size,DEval.displacement,DEval(),Geo);
    double tmd=DEval()-Sphere[0].d;
    scale(DEval.displacementvec,tmd/DEval());
    DEval()=tmd;
  }

}

#endif
