
#ifndef _Array_1D_Cross_H_
#define _Array_1D_Cross_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T1,typename T2,typename T3>
  void Cross(Array1D<T1>& A,const Array1D<T2>& B,const Array1D<T3>& C) {
    assert((A.Size()>=3)&&(B.Size()>=3)&&(C.Size()>=3));
    A[0]=B[1]*C[2]-B[2]*C[1];
    A[1]=B[2]*C[0]-B[0]*C[2];
    A[2]=B[0]*C[1]-B[1]*C[0];
  }

}

#endif

