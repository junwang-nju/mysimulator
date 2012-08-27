
/** @file displacement/free/calc.h
 * @brief calculate displacement for free boundary condition
 *
 * This file implements the calculation of displacement for the free
 * boundary condition. This is a popular case of displacement calculation.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Displacement_Free_Calc_H_
#define _Displacement_Free_Calc_H_

#include "displacement/direct/calc.h"
#include "boundary/free/interface.h"

namespace mysimulator {

  /** @fn void DisplacementCalc(ArrayNumeric<T>&,const ArrayNumeric<T1>&,const ArrayNumeric<T2>&,const FreeSpace&)
   * @brief calculate displacement for free boundary condition
   *
   * Based on the definition of free boundary condition, this operation is
   * implemented directly with the function \c DisplacementCalcDirect.
   *
   * @tparam T the type of member of output vector
   * @tparam T1,T2 the types of members of input vectors
   *
   * @param A [out] the resultant displacement vector
   * @param A1 [in] the input vector as end point of displacement
   * @param A2 [in] the input vector as start point of displacement
   * @param F [in] the input free-space boundary condition
   */
  template <typename T, typename T1, typename T2>
  void DisplacementCalc(
      ArrayNumeric<T>& A,const ArrayNumeric<T1>& A1,const ArrayNumeric<T2>& A2,
      const FreeSpace& F){
    DisplacementCalcDirect(A,A1,A2);
  }

}

#endif

