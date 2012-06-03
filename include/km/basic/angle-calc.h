
/**
 * @file basic/angle-calc.h
 * @brief calculate angle based on three points
 *
 * Calculation of angle based on three related points is a basic geometrical
 * operation. This file implements this calculation (for 3-dimension).
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Angle_Calc_H_
#define _Basic_Angle_Calc_H_

#include "distance/calc.h"
#include "boundary/free/interface.h"
#include "type/is-float-point.h"
#include "basic/acos.h"

namespace mysimulator {

  /** @fn T Angle(const ArrayNumeric<T>&,const ArrayNumeric<T>&,const ArrayNumeric<T>&);
   * @brief calculate the angle based on related three points (3-d case)
   *
   * This calculation is implemented based on the cosine law of triangle.
   * The distance is defined based on the boundary condition of
   * \c FreeSpace.
   *
   * @param A1,A2,A3 [in] the input location of the concerned points,
   *                      in which the middle one \a A2 is vortex of the angle,
   *                      and \a A1-A2 and \a A3-A2 correspond two edges
   * @return the value of angle
   * @note the present calculation works only for 3-dimensional case
   * @note for other boundary conditions, the input points should be
   *       move to match the expected condition of triangle.
   */
  template <typename T>
  T Angle(const ArrayNumeric<T>& A1,const ArrayNumeric<T>& A2,
          const ArrayNumeric<T>& A3) {
    assert(A1.Size()==3);
    assert(A2.Size()==3);
    assert(A3.Size()==3);
    typedef typename IsFloatPoint<T>::Type  FloatPointCheck;
    T a2,b2,c2;
    FreeSpace FS;
    ArrayNumeric<T> Dsp;
    Dsp.Allocate(3);
    a2=DistanceSQ(Dsp,A1,A2,FS);
    b2=DistanceSQ(Dsp,A3,A2,FS);
    c2=DistanceSQ(Dsp,A1,A3,FS);
    T _ag=_ACos((a2+b2-c2)*0.5/__SqRoot(a2*b2));
    Clear(Dsp);
    return _ag;
  }

}

#endif

