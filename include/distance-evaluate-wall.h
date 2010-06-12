
#ifndef _Distance_Evaluate_Wall_H_
#define _Distance_Evaluate_Wall_H_

#include "vector.h"
#include "unique-parameter.h"
#include <cmath>

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void DistanceDisplacement2Plane(
      const Vector<double>* Coor, const unsigned int* Idx, 
      const UniqueParameter* Plane,
      DistEvalMethod& DEval, const GeomType& Geo) {
    unsigned int dim=Coor[Idx[0]].size;
    DisplacementFunc(Coor[Idx[0]](),
                     reinterpret_cast<const double*>(Plane),dim,
                     DEval.displacement,Geo);
    DEval()=dot(reinterpret_cast<const double*>(Plane+dim),
                DEval.displacement,dim);
    assign(DEval.displacement,reinterpret_cast<const double*>(Plane+dim),dim);
    scale(DEval.displacementvec,DEval());
  }

  template <typename DistEvalMethod, typename GeomType>
  void DistanceDisplacement2Sphere(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Sphere,
      DistEvalMethod& DEval, const GeomType& Geo) {
    DistanceDisplacementFunc(Coor[Idx[0]](),
                             reinterpret_cast<const double*>(Sphere+2),
                             Coor[Idx[0]].size,DEval.displacement,DEval(),Geo);
    double d=sqrt(DEval());
    double tmd=d-Sphere[0].d;
    scale(DEval.displacementvec,tmd/d);
    DEval()=tmd*Sphere[1].d;
  }

}

#endif
