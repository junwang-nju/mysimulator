
#ifndef _Basic_Angle_Calc_H_
#define _Basic_Angle_Calc_H_

#include "distance/calc.h"
#include "boundary/free/interface.h"
#include "type/is-float-point.h"
#include "basic/acos.h"

namespace mysimulator {

  template <typename T>
  T AngleValue(const ArrayNumeric<T>& A1,const ArrayNumeric<T>& A2,
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

