
#ifndef _Array_2D_Content_Copy_H_
#define _Array_2D_Content_Copy_H_

#include "array/2d/content/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void copy(Array2DContent<T1>& A, const Array2DContent<T2>& B,
            const int& alb, const unsigned int& ald, const int& blb,
            const unsigned int& bld, const unsigned int& nl,
            const int& arb, const unsigned int& ard, const int& brb,
            const unsigned int& brd, const unsigned int& nr) {
    assert(IsValid(A,alb,ald,nl,arb,ard,nr)&&
           IsValid(B,blb,bld,nl,brb,brd,nr));
    Array1DContent<T1>* p=A.infra.head+alb;
    Array1DContent<T2>* q=const_cast<Array1DContent<T2>*>(B.infra.head+blb);
    Array1DContent<T1>* e=p+ald*nl;
    for(;p!=e;p+=ald,q+=bld)  copy(*p,*q,arb,ard,brb,brd,nr);
  }

  template <typename T1, typename T2>
  void copy(Array2DContent<T1>& A, const Array2DContent<T2>& B) {
    unsigned int n=(A.NumLines()<B.NumLines()?A.NumLines():B.NumLines());
    Array1DContent<T1>* p=A.infra.start;
    Array1DContent<T2>* q=const_cast<Array1DContent<T2>*>(B.infra.start);
    Array1DContent<T1>* e=p+n;
    for(;p!=e;) copy(*(p++),*(q++));
  }

}

#include "array/2d/content/compare.h"
#include "array/1d/content/copy.h"

namespace mysimulator {

  template <typename T>
  void ecopy(Array2DContent<T>& A, const Array2DContent<T>& B) {
    assert(IsSameSize(A,B));
    copy(A.base,B.base);
  }

}

#endif

