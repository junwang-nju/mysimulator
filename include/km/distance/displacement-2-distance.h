
/** @file distance/displacement-2-distance.h
 * @brief get distance from displacement
 *
 * distance and displacement are two linked concepts. It is possible
 * to calculate distance when the displacement is ready. This file
 * implements the conversion from the displacement to distance.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Distance_Displacement2Distance_H_
#define _Distance_Displacement2Distance_H_

#include "array-numeric/interface.h"

namespace mysimulator {

  /** @fn T Displacement2DistanceSQ(const ArrayNumeric<T>&)
   * @brief calculate square of distance from displacement
   *
   * Based the geometrical relation, it is implemented with \c NormSQ method
   * of displacement. Here we assume the space is euclidean.
   *
   * @tparam T the type of data related to distance and displacement
   *
   * @param A [in] the input vector of displacement
   * @return the square of corresponding distance
   */
  template <typename T>
  T Displacement2DistanceSQ(const ArrayNumeric<T>& A) { return A.NormSQ(); }

  /** @fn T Displacement2Distance(const ArrayNumeric<T>&)
   * @brief calculate distance from displacement
   *
   * Based the geometrical relation, it is implemented with \c Norm method
   * of displacement. Here we assume the space is euclidean.
   *
   * @tparam T the type of data related to distance and displacement
   *
   * @param A [in] the input vector of displacement
   * @return the corresponding distance
   */
  template <typename T>
  T Displacement2Distance(const ArrayNumeric<T>& A) { return A.Norm(); }

}

#endif

