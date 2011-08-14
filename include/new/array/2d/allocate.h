
#ifndef _Array_2D_Allocate_H_
#define _Array_2D_Allocate_H_

#include "array/2d/interface.h"
#include "pointer/allocate.h"
#include "array/2d/content/init.h"

namespace mysimulator {

  template <typename T>
  void allocate(Array2D<T>& A, const unsigned int& nl, const unsigned int& nr){
    release(A);
    assert((nl>0)&&(nr>0));
    allocate(A.data,nl*nr);
    allocate(A.subdata,nl);
    init(A,A.data(),A.subdata(),nl,nr);
  }

  template <typename T>
  void allocate(Array2D<T>& A, const int& lb, const int& le, const int& rb,
                const int& re) {
    release(A);
    assert((le>lb)&&(re>rb));
    allocate(A.data,(le-lb+1)*(re-rb+1));
    allocate(A.subdata,le-lb+1);
    init(A,A.data(),A.subdata(),lb,le,rb,re);
  }

}

#include "array/1d/content/sum.h"

namespace mysimulator {

  template <typename T>
  void allocate(Array2D<T>& A, const Array1DContent<unsigned int>& n) {
    release(A);
    unsigned int s=sum(n);
    allocate(A.data,s);
    allocate(A.subdata,n.size);
    init(A,A.data(),A.subdata(),s,n);
  }

  template <typename T>
  void allocate(Array2D<T>& A, const int& lfst, const Array1DContent<int>& fst,
                const Array1DContent<int>& lst) {
    assert(fst.size==lst.size);
    release(A);
    unsigned int s=sum(lst)-sum(fst);
    allocate(A.data,s);
    allocate(A.subdata,fst.size);
    init(A,A.data(),A.subdata(),s,lfst,fst,lst);
  }

}

#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T>
  void allocate(Array2D<T>& A, const Array1DContent<int>& fst,
                const Array1DContent<int>& lst) {
    allocate(A,iZero,fst,lst);
  }

}

#include "array/1d/allocate.h"

namespace mysimulator {

  template <typename T>
  void imprint(Array2D<T>& A, const Array2D<T>& cA) {
    assert(IsValid(cA));
    int lfst=cA.infra.first;
    Array1D<int> fst,lst;
    allocate(fst,cA.NumLines());
    allocate(lst,cA.NumLines());
    Array1DContent<T>* p=const_cast<Array1DContent<T>*>(cA.infra.start);
    Array1DContent<T>* e=p+cA.infra.size;
    int* q=fst.start;
    int* r=lst.start;
    for(;p!=e;) { *(q++)=(*p).first;  *(r++)=(*(p++)).last; }
    allocate(A,lfst,fst,lst);
    release(fst);
    release(lst);
  }
}

#endif

