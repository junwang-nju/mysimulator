
/**
 * @file distance-evaluate-wall.h
 * @brief Distance Evaluation with wall
 *
 * This file describes the operations for distance evaluation related
 * to wall. The wall is generally considered as the boundary with fixed
 * location and various interactions with particles.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Distance_Evaluate_Wall_H_
#define _Distance_Evaluate_Wall_H_

#include "vector.h"
#include "unique-parameter.h"
#include <cmath>

namespace std {

  /**
   * @brief calculate distance and displacement related to plane wall
   *
   * To interact a plane wall, the force is perpendicular to the plane.
   * The distance is defined as the perpendicular distance to the plane.
   *
   * DistEvalMethod is the type of the method for distance evaluation.
   * GeomType is the type of geometry.
   *
   * @param Coor [in] the pointer to the list of coordinated
   * @param Idx [in] the pointer to the list of indices
   * @param Plane [in] the parameters describing the plane
   * @param DEval [in,out] the method for distance evaluation
   * @param Geo [in] the geometry
   * @return nothing
   */
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

  /**
   * @brief calculate distance and displacement related to sphere wall
   *
   * To interact a sphere wall, the force is perpendicular to the sphere
   * shell. The distance is defined as the perpendicular distance to the
   * sphere shall (along radius).
   *
   * DistEvalMethod is the type of the method for distance evaluation.
   * GeomType is the type of geometry.
   *
   * @param Coor [in] the pointer to the list of coordinated
   * @param Idx [in] the pointer to the list of indices
   * @param Sphere [in] the parameters describing the sphere
   * @param DEval [in,out] the method for distance evaluation
   * @param Geo [in] the geometry
   * @return nothing
   */
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
