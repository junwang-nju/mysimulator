
#ifndef _Array_3D_Allocate_H_
#define _Array_3D_Allocate_H_

#include "array/3d/interface.h"
#include "pointer/allocate.h"
#include "array/3d/content/init.h"

namespace mysimulator {

  template <typename T>
  void allocate(Array3D<T>& A, const unsigned int& np, const unsigned int& nl,
                const unsigned int& nr) {
    release(A);
    assert((np>0)&&(nl>0)&&(nr>0));
    unsigned int tm=np*nl;
    allocate(A.data,tm*nr);
    allocate(A.subdata2d,tm);
    allocate(A.subdata3d,np);
    init(A,A.data(),A.subdata2d(),A.subdata3d(),np,nl,nr);
  }

  template <typename T>
  void allocate(Array3D<T>& A, const int& pb, const int& pe, const int& lb,
                const int& le, const int& rb, const int& re) {
    release(A);
    assert((pe>pb)&&(le>lb)&&(re>rb));
    int tm=(pe-pb+1)*(le-lb+1);
    allocate(A.data,tm*(re-rb+1));
    allocate(A.subdata2d,tm);
    allocate(A.subdata3d,pe-pb+1);
    init(A,A.data(),A.subdata2d(),A.subdata3d(),pb,pe,lb,le,rb,re);
  }

}

#endif

