
/**
 * @file distance/calc.h
 * @brief methods to calculate distance
 *
 * distance is a regular geometric property. It is generally needed to calculate
 * the distance from the points and concerned boundary condition. This
 * file implements the calculations of distance for various objects.
 * These operations encapsulate the differences of distance calculations.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Distance_Calc_H_
#define _Distance_Calc_H_

#include "distance/displacement-2-distance.h"

namespace mysimulator {

  /** @fn T DistanceSQ(ArrayNumeric<T>&,const ArrayNumeric<T1>&,const ArrayNumeric<T2>&,const GeomType&)
   * @brief calculate square of distance for concerned boundary condition
   *
   * This file calculates the square of distance based on the input points
   * and concerned boundary conditions. It is implemented with dispalcement
   * calculation and conversion from displacement to distance.
   *
   * @tparam T the type of data related to resultant distance and displacement
   * @tparam T1,T2 the types of data related to input vectors
   * @tparam GeomType the type of boundary condition
   *
   * @param Dsp [out] the vector of displacement
   * @param X [in] the vector corresponding to end point of displacement
   * @param Y [in] the vector corresponding to start point of displacement
   * @param Geo [in] the concerned boundary condition
   * @return the square of the calculated distance
   *
   * @note A temporary displacement vector is needed, which may reduce the
   *       time to allocate displacement and cankeep the information of
   *       displacement for further use.
   * @note the square of distance is calculated to save some time by avoiding
   *       calculattion of square root. This value is often useful for
   *       some kinds of potential calculations.
   */
  template <typename T,typename T1,typename T2,typename GeomType>
  T DistanceSQ(ArrayNumeric<T>& Dsp,const ArrayNumeric<T1>& X,
               const ArrayNumeric<T2>& Y,const GeomType& Geo) {
    DisplacementCalc(Dsp,X,Y,Geo);
    return Displacement2DistanceSQ(Dsp);
  }

  /** @fn T Distance(ArrayNumeric<T>&,const ArrayNumeric<T1>&,const ArrayNumeric<T2>&,const GeomType&)
   * @brief calculate distance for concerned boundary condition
   *
   * This file calculates the distance based on the input points
   * and concerned boundary conditions. It is implemented with dispalcement
   * calculation and conversion from displacement to distance.
   *
   * @tparam T the type of data related to resultant distance and displacement
   * @tparam T1,T2 the types of data related to input vectors
   * @tparam GeomType the type of boundary condition
   *
   * @param Dsp [out] the vector of displacement
   * @param X [in] the vector corresponding to end point of displacement
   * @param Y [in] the vector corresponding to start point of displacement
   * @param Geo [in] the concerned boundary condition
   * @return the calculated distance
   *
   * @note A temporary displacement vector is needed, which may reduce the
   *       time to allocate displacement and cankeep the information of
   *       displacement for further use.
   */
  template <typename T,typename T1,typename T2,typename GeomType>
  T Distance(ArrayNumeric<T>& Dsp,const ArrayNumeric<T1>& X,
             const ArrayNumeric<T2>& Y,const GeomType& Geo) {
    DisplacementCalc(Dsp,X,Y,Geo);
    return Displacement2Distance(Dsp);
  }

  /** @fn typename CombineType<typename DataType<T1>::Type,typename DataType<T2>::Type>::Type Distance2Wall(const ArrayNumeric<T1>&,const ArrayNumeric<T2>&,const GeomType&)
   * @brief calculate distance to a wall for concerned boundary condition
   *
   * The distance for a point to a wall is defined as the minimal distance
   * from the point to the wall. the concerned displacement is generally
   * related to normal direction of the place. Therefore, the displacement
   * can be eliminated in this operation. The operation is implemented with
   * a dot operation and a shift of distance value related to the wall
   * location.
   *
   * @tparam T1 the type of data related to wall
   * @tparam T2 the type of data related to point
   * @tparam GeomType the type of boundary condition
   *
   * @param W [in] the input wall information
   * @param P [in] the input point vector
   * @param Geo [in] the concerned boundary condition
   * @return the distance to the wall. the type is derived based on the
   *         types of input wall and point.
   *
   * @note geometry does not work for this calculation since wall is not 
   *       penetratable (the periodic condition has no meaning for the
   *       wall object)
   */
  template <typename T1,typename T2,typename GeomType>
  typename CombineType<typename DataType<T1>::Type,
                       typename DataType<T2>::Type>::Type
  Distance2Wall(const ArrayNumeric<T1>& W, const ArrayNumeric<T2>& P,
                const GeomType& Geo) {
    return _DotN(W,P,P.Size())-W[P.Size()];
  }

}

#include "pdb-atom-position/interface.h"

namespace mysimulator {

  /** @fn double DistanceSQ(const PDBAtomPosition&,const PDBAtomPosition&)
   * @brief calculate square of distance for atom position in pdb structure
   *
   * In pdb data structure, the position has different interface from the
   * vector. Therefore, the calculation of square of distance should have
   * different implementation. this function implemented with regular
   * euclidean definition.
   *
   * @param P1,P2 [in] two concerned atom positions in pdb data structure
   * @return the square of concerned distance
   *
   * @note this function is generally used for the post-process for pdb file.
   *       no boundary condition are included.
   */
  double DistanceSQ(const PDBAtomPosition& P1,const PDBAtomPosition& P2) {
    double X,Y,Z;
    X=P1.X()-P2.X();
    Y=P1.Y()-P2.Y();
    Z=P1.Z()-P2.Z();
    return X*X+Y*Y+Z*Z;
  }

  /** @fn double Distance(const PDBAtomPosition&,const PDBAtomPosition&)
   * @brief calculate distance for atom position in pdb structure
   *
   * In pdb data structure, the position has different interface from the
   * vector. Therefore, the calculation of distance should have
   * different implementation. this function implemented as the square
   * root of the result of \c DistancSQ.
   *
   * @param P1,P2 [in] two concerned atom positions in pdb data structure
   * @return the concerned distance
   *
   * @note this function is generally used for the post-process for pdb file.
   *       no boundary condition are included.
   */
  double Distance(const PDBAtomPosition& P1,const PDBAtomPosition& P2) {
    return __SqRoot(DistanceSQ(P1,P2));
  }

}

#endif

