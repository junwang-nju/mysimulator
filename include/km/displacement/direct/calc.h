
/** @file displacement/direct/calc.h
 * @brief calculate distance directly
 *
 * Displacement is a basic geometric property. This file implements
 * the calculation of displacement directly, that is in euclidean
 * space and without any boundary condition. This is kernal of other
 * displacement calculation.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Displacement_Direct_Calc_H_
#define _Displacement_Direct_Calc_H_

#include "array-numeric/interface.h"

namespace mysimulator {

  /** @fn void DisplacementCalcDirect(ArrayNumeric<T>&,const ArrayNumeric<T1>&,const ArrayNumeric<T2>&)
   * @brief calculate displacement between two points directly
   *
   * The displacement vector could be defined as the substraction of two
   * vectors. This is implemented with vector operations, which require
   * the elements of the input and output vectors are all numeric.
   *
   * @tparam T the type of member of output vector
   * @tparam T1,T2 the types of members of input vectors
   *
   * @param A [out] the resultant displacement vector
   * @param A1 [in] the input vector as end point of displacement
   * @param A2 [in] the input vector as start point of displacement
   */
  template <typename T,typename T1,typename T2>
  void DisplacementCalcDirect(
      ArrayNumeric<T>& A,const ArrayNumeric<T1>& A1,const ArrayNumeric<T2>& A2){
    A.Copy(A1);
    A.NegShift(A2);
  }

}

#endif

