
#ifndef _Displacement_Calculate_Direct_H_
#define _Displacement_Calculate_Direct_H_

#include "data/name/constant.h"
#include "operation/basic/util.h"
#include "operation/basic/blas.h"

namespace std {

  template <typename TA, typename TB, typename TD>
  void Displacement(const TA* va, const TB* vb, TD* vd,
                    const unsigned int dim,
                    const int aoff=iZero, const long astep=lOne,
                    const int boff=iZero, const long bstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    TA* pa=const_cast<TA*>(va)+aoff;
    TB* pb=const_cast<TB*>(vb)+boff;
    TD* pd=vd+doff;
    for(unsigned int i=0;i<dim;++i,pa+=astep,pb+=bstep,pd+=dstep) {
      copy(*pd,*pa);
      shift(*pd,-iOne,*pb);
    }
  }

  void Displacement(const double* va, const double* vb, double* vd,
                    const unsigned int dim,
                    const int aoff=iZero, const long astep=lOne,
                    const int boff=iZero, const long bstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    long n=dim;
    dcopy_(&n,const_cast<double*>(va)+aoff,const_cast<long*>(&astep),
              vd+doff,const_cast<long*>(&dstep));
    daxpy_(&n,const_cast<double*>(&dNOne),const_cast<double*>(vb)+boff,
              const_cast<long*>(&bstep),vd+doff,const_cast<long*>(&dstep));
  }

  void Displacement(const float* va, const float* vb, float* vd,
                    const unsigned int dim,
                    const int aoff=iZero, const long astep=lOne,
                    const int boff=iZero, const long bstep=lOne,
                    const int doff=iZero, const long dstep=lOne) {
    long n=dim;
    scopy_(&n,const_cast<float*>(va)+aoff,const_cast<long*>(&astep),
              vd+doff,const_cast<long*>(&dstep));
    saxpy_(&n,const_cast<float*>(&fNOne),const_cast<float*>(vb)+boff,
              const_cast<long*>(&bstep),vd+dstep,const_cast<long*>(&dstep));
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename TA, typename TB, typename T>
  void Displacement(const Vector<TA>& va, const Vector<TB>& vb, Vector<T>& vd){
    unsigned int n=(va.size<vb.size?va.size:vb.size);
    n=(n<vd.size?n:vd.size);
    Displacement(va.data,vb.data,vd.data,n);
  }
}

#endif

