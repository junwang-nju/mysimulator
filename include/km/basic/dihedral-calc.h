
#ifndef _Basic_Dihedral_Calc_H_
#define _Basic_Dihedral_Calc_H_

#include "distance/calc.h"
#include "boundary/free/interface.h"
#include "type/is-float-point.h"
#include "basic/acos.h"

namespace mysimulator {

  template <typename T>
  T DihedralValue(const ArrayNumeric<T>& A1, const ArrayNumeric<T>& A2,
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

