
#ifndef _Geometry_Displacement_Direct_Calculate_H_
#define _Geometry_Displacement_Direct_Calculate_H_

#include "intrinsic-type/copy.h"
#include "intrinsic-type/shift.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename TA,typename TB,typename T>
  void DisplacementCalcDirect(
      const TA* a, const TB* b, T* v, const unsigned int dim,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int off=iZero,  const long step=lOne) {
    TA* pa=const_cast<TA*>(a)+aoff;
    TB* pb=const_cast<TB*>(b)+boff;
    T*  p=v+off;
    TA* pend=pa+astep*dim;
    for(;pa!=pend;pa+=astep,pb+=bstep,p+=step) {
      copy(*p,*pa);
      shift(*p,-cOne,*pb);
    }
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void DisplacementCalcDirect(
      const double* a,const double* b,double* v,const unsigned int n,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int off=iZero,  const long step=lOne) {
    dcopy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
           const_cast<double*>(a)+aoff,const_cast<long*>(&astep),
           v+off,const_cast<long*>(&step));
    daxpy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
           const_cast<double*>(&dNOne),const_cast<double*>(b)+boff,
           const_cast<long*>(&bstep),v+off,const_cast<long*>(&step));
  }

  void DisplacementCalcDirect(
      const float* a,const float* b,float* v,const unsigned int n,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int off=iZero,  const long step=lOne) {
    scopy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
           const_cast<float*>(a)+aoff,const_cast<long*>(&astep),
           v+off,const_cast<long*>(&step));
    saxpy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
           const_cast<float*>(&fNOne),const_cast<float*>(b)+boff,
           const_cast<long*>(&bstep),v+off,const_cast<long*>(&step));
  }

}

#include "vector/interface.h"

namespace mysimulator {

  template <typename TA,typename TB,typename T>
  void DisplacementCalcDirect(
      const Vector<TA>& a,const Vector<TB>& b,Vector<T>& v) {
    unsigned int n;
    n=(a.size<b.size?a.size:b.size);
    n=(n<v.size?n:v.size);
    DisplacementCalcDirect(a.pdata,b.pdata,v.pdata,n);
  }

}

#endif

