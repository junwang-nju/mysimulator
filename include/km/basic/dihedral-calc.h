
/**
 * @file basic/dihedral-calc.h
 * @brief calculate dihedral angle based on four points
 *
 * Calculation of dihedral based on four related points is a basic geometrical
 * operation. This file implements this calculation (for 3-dimension).
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Dihedral_Calc_H_
#define _Basic_Dihedral_Calc_H_

#include "distance/calc.h"
#include "boundary/free/interface.h"
#include "type/is-float-point.h"
#include "basic/acos.h"

namespace mysimulator {

  /** @fn T Dihedral(const ArrayNumeric<T>&,const ArrayNumeric<T>&,const ArrayNumeric<T>&,const ArrayNumeric<T>&)
   * @brief calculate the dihedral based on related four points (3-d case)
   *
   * This calculation is implemented based on the geometrical meaning of the
   * dihedral. In detail, the cosine and sine of dihedral can be calculated
   * based on the dot produce and cross produce of the normal vectors of the
   * two related planes (represented as the plane \c A1-A2-A3 and \c A2-A3-A4 ).
   * The sign of dihedral is obtained from the sign of the sine of dihedral.
   * The distance is calculated based on the boundary condition of
   * \c FreeSpace.
   *
   * @tparam T the type of the coordinates for the points
   *
   * @param A1,A2,A3,A4 [in] the input locations of the sequentially connected
   *                         points.
   * @return the value of dihedral
   *
   * @note the present calculation works for 3-dimensional case only
   * @note for other boundary conditions, the input points should be moved
   *       to match the expected condition of geometry
   * @note sevral temporary ArrayNumeric object are allocated and released
   *       in calculation. Therefore it is not efficient in frequent use.
   */

  template <typename T>
  T Dihedral(const ArrayNumeric<T>& A1, const ArrayNumeric<T>& A2,
             const ArrayNumeric<T>& A3, const ArrayNumeric<T>& A4) {
    assert(A1.Size()==3);
    assert(A2.Size()==3);
    assert(A3.Size()==3);
    assert(A4.Size()==3);
    typedef typename IsFloatPoint<T>::Type  FloatPointCheck;
    FreeSpace FS;
    ArrayNumeric<T> B1,B2,B3,N1,N2,AX;
    T lN1,lN2,csD;
    B1.Allocate(3);
    B2.Allocate(3);
    B3.Allocate(3);
    N1.Allocate(3);
    N2.Allocate(3);
    AX.Allocate(3);
    DisplacementCalc(B1,A2,A1,FS);
    DisplacementCalc(B2,A3,A2,FS);
    DisplacementCalc(B3,A4,A3,FS);
    Cross(N1,B1,B2);
    Cross(N2,B2,B3);
    lN1=N1.NormSQ();
    lN2=N2.NormSQ();
    csD=_Dot(N1,N2)/__SqRoot(lN1*lN2);
    Cross(AX,N1,N2);
    T dih=_ACos(csD)*(_Dot(AX,B2)>0?1:-1);
    Clear(AX);
    Clear(N2);
    Clear(N1);
    Clear(B3);
    Clear(B2);
    Clear(B1);
    return dih;
  }

}

#endif

