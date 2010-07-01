
/**
 * @file displacement-direct.h
 * @brief calculate displacement directly (without boundary)
 *
 * This file includes procedures to calculate displacement without
 * geometry condition. This is the basic operation to calculate
 * displacement. Here, the displacement is defined in Euclidean
 * geometry.
 */

#ifndef _Displacement_Direct_H_
#define _Displacement_Direct_H_

#include "vector.h"

namespace std {

  /**
   * @brief calculate displacement based on \c double array with offsets and steps
   *
   * This operation is implemented with the assign and shift operations
   * for \c double arrays. Here, the offsets and steps are considered
   * for flexibility.
   *
   * @param va,vb [in] the pointers of \c double arrays indicating coordinates
   * @param dim [in] the dimension of the space (namely the number of elements
   *                 involved in this calculation)
   * @param Dsp [out] the pointer of \c double array indicating displacement
   * @param aoff,boff,doff [in] the offsets for the arrays va, vb, and Dsp
   * @param astep,bstep,dstep [in] the separations between used elements in
   *                               the arrays va, vb, and Dsp
   * @return nothing
   * @note the order of input arrays va, and vb are meaningful.
   */
  void DisplacementFunc(const double* va, const double* vb,
                        const unsigned int dim, double* Dsp,
                        const int aoff=iZero, const long astep=lOne,
                        const int boff=iZero, const long bstep=lOne,
                        const int doff=iZero, const long dstep=lOne) {
    assign(Dsp,va,dim,aoff,astep,doff,dstep);
    shift(Dsp,-1.,vb,dim,boff,bstep,doff,dstep);
  }

  /**
   * @brief calculate displacement for vectors with \c double values
   *
   * It is implemented with assign and shift operations. No offsets or
   * steps are used for simplicity.
   *
   * @param va,vb [in] the Vector objects containing coordinates
   * @param Dsp [out] the Vector object as displacement
   * @return nothing
   * @note the order of input Vector objects va and vb are meaningful.
   */
  void DisplacementFunc(const Vector<double>& va, const Vector<double>& vb,
                        Vector<double>& Dsp) {
    assign(Dsp,va);
    shift(Dsp,-1.,vb);
  }

}

#endif
