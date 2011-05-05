
#ifndef _Geometry_Displacement_Base_Calculate_H_
#define _Geometry_Displacement_Base_Calculate_H_

#include "intrinsic-type/constant.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/shift.h"

namespace mysimulator {

  template <typename TA, typename TB, typename TD>
  void DisplacementCalc(
      const TA* va, const TB* vb, TD* vd, const unsigned int dim,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int doff=iZero, const long dstep=lOne) {
    TA* pa=const_cast<TA*>(va)+aoff;
    TB* pb=const_cast<TB*>(vb)+boff;
    TD* pd=vd+doff;
    TA* pend=pa+astep*dim;
    for(;pa!=pend;pa+=astep,pb+=bstep,pd+=dstep) {
      copy(*pd,*pa);
      shift(*pd,-cOne,*pb);
    }
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void DisplacementCalc(
      const double* a, const double* b, double* d, const unsigned int n,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int doff=iZero, const long dstep=lOne) {
    dcopy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
           const_cast<double*>(a)+aoff,const_cast<long*>(&astep),
           d+doff,const_cast<long*>(&dstep));
    daxpy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
           const_cast<double*>(&dNOne),const_cast<double*>(b)+boff,
           const_cast<long*>(&bstep),d+doff,const_cast<long*>(&dstep));
  }

  void DisplacementCalc(
      const float* a, const float* b, float* d, const unsigned int n,
      const int aoff=iZero, const long astep=lOne,
      const int boff=iZero, const long bstep=lOne,
      const int doff=iZero, const long dstep=lOne) {
    scopy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
           const_cast<float*>(a)+aoff,const_cast<long*>(&astep),
           d+doff,const_cast<long*>(&dstep));
    saxpy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
           const_cast<float*>(&fNOne),const_cast<float*>(b)+boff,
           const_cast<long*>(&bstep),d+doff,const_cast<long*>(&dstep));
  }

}

#include "vector/interface.h"

namespace mysimulator {

  template <typename TA, typename TB, typename TD>
  void DisplacementCalc(
      const Vector<TA>& va, const Vector<TB>& vb, Vector<TD>& vd) {
    unsigned int n;
    n=(va.size<vb.size?va.size:vb.size);
    n=(vd.size<n?vd.size:n);
    DisplacementCalc(va.pdata,vb.pdata,vd.pdata,n);
  }

}

#endif

