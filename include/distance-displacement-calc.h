
/**
 * @file distance-displacement-calc.h
 * @brief the functions to calculate distance and displacement
 *
 * This file discribes the functions to calculate distance and displacement
 * with geometry condition. These are the basic forms with templates as
 * the entrances to access the calculations of distance and displacement
 * for various geometry.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 * @todo the functions with a mixture of arrays and Vector objects are
 *       not implemented.
 */

#ifndef _Distance_Displacement_Calculation_H_
#define _Distance_Displacement_Calculation_H_

#include "vector.h"

namespace std {

  /**
   * @brief calculate distance and displacement for \c double arrays
   *
   * It is implemented with DisplacementFunc operation to calculate
   * the displacement vector. The distance is defined as the norm of the
   * displacement vector.
   *
   * GeomType is the type indicating geometry condition.
   *
   * @param va, vb [in] the arrays recording the coordinates
   * @param dim [in] the dimension of the concerned space (namely the number
   *                 of elements involved in calculation)
   * @param Dsp [out] the array to store the displacement
   * @param D2 [out] the square of distance
   * @param Geo [in] the concerned geometry
   * @param aoff, boff, doff [in] the offsets for the first elements to be
   *                              used in arrays va, vb and Dsp. They take
   *                              the default value of iZero.
   * @param astep, bstep, dstep [in] the separations between elements to be
   *                                 used in arrays va, vb, and Dsp. They
   *                                 take the default value lOne.
   * @return nothing
   */
  template <typename GeomType>
  void DistanceDisplacementFunc(const double* va, const double* vb,
                                const unsigned int dim, double* Dsp, double& D2,
                                const GeomType& Geo,
                                const int aoff=iZero, const long astep=lOne,
                                const int boff=iZero, const long bstep=lOne,
                                const int doff=iZero, const long dstep=lOne) {
    DisplacementFunc(va,vb,dim,Dsp,Geo,aoff,astep,boff,bstep,doff,dstep);
    D2=normSQ(Dsp,dim,doff,dstep);
  }

  /**
   * @brief calculate distance and displacement for Vector objects
   *
   * It is implemented with the DisplacementFunc function for Vector object.
   * The distance is calculated as the norm of the displacement vector.
   * Here, the offsets and steps are omitted for simplicity.
   *
   * GeomType is the type indicating geometry condition.
   *
   * @param va, vb [in] the Vector objects recording coordinates
   * @param Dsp [out] the Vector object storing displacement
   * @param D2 [out] the square of distance.
   * @param Geo [in] the concerned geometry
   * @return nothing
   */ 
  template <typename GeomType>
  void DistanceDisplacementFunc(const Vector<double>& va,
                                const Vector<double>& vb,
                                Vector<double>& Dsp, double& D2,
                                const GeomType& Geo) {
    DisplacementFunc(va,vb,Dsp,Geo);
    D2=normSQ(Dsp);
  }

}

#endif

