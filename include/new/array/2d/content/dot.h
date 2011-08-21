
#ifndef _Array_2D_Content_Dot_H_
#define _Array_2D_Content_Dot_H_

#include "array/2d/content/compare.h"
#include "array/1d/content/dot.h"

#define _DotTYPE(T1,T2)  typename _Dual<T1,T2>::CombineType

namespace mysimulator {

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  dot(const Array2DContent<T1>& A1, const Array2DContent<T2>& A2,
      const int& alb, const unsigned int& ald, const int& blb,
      const unsigned int& bld, const unsigned int& ln, const int& arb,
      const unsigned int& ard, const int& brb, const unsigned int& brd,
      const unsigned int& rn) {
    Array1DContent<T1>* p=const_cast<Array1DContent<T1>*>(A1.infra.head)+alb;
    Array1DContent<T1>* e=p+ln*ald;
    Array1DContent<T2>* q=const_cast<Array1DContent<T2>*>(A2.infra.head)+blb;
    _DotTYPE(T1,T2) sum;
    copy(sum,cZero);
    for(;p!=e;p+=ald,q+=bld)  sum+=dot(*p,*q,arb,ard,brb,brd,rn);
    return sum;
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  dot(const Array2DContent<T1>& A1, const Array2DContent<T2>& A2,
      const int& alb, const int& blb, const unsigned int& ln,
      const int& arb, const int& brb, const unsigned int& rn) {
    Array1DContent<T1>* p=const_cast<Array1DContent<T1>*>(A1.infra.head)+alb;
    Array1DContent<T1>* e=p+ln;
    Array1DContent<T2>* q=const_cast<Array1DContent<T2>*>(A2.infra.head)+blb;
    _DotTYPE(T1,T2) sum;
    copy(sum,cZero);
    for(;p!=e;) sum+=dot(*(p++),*(q++),arb,brb,rn);
    return sum;
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  dot(const Array2DContent<T1>& A1, const Array2DContent<T2>& A2,
      const unsigned int& ln, const unsigned int& rn) {
    Array1DContent<T1>* p=const_cast<Array1DContent<T1>*>(A1.infra.start);
    Array1DContent<T1>* e=p+ln;
    Array1DContent<T2>* q=const_cast<Array1DContent<T2>*>(A2.infra.start);
    _DotTYPE(T1,T2) sum;
    copy(sum,cZero);
    for(;p!=e;) sum+=dot(*(p++),*(q++),rn);
    return sum;
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  dot(const Array2DContent<T1>& A1, const Array2DContent<T2>& A2) {
    unsigned int n=(A1.NumLines()<A2.NumLines()?A1.NumLines():A2.NumLines());
    Array1DContent<T1>* p=const_cast<Array1DContent<T1>*>(A1.infra.start);
    Array1DContent<T1>* e=p+n;
    Array1DContent<T2>* q=const_cast<Array1DContent<T2>*>(A2.infra.start);
    _DotTYPE(T1,T2) sum;
    copy(sum,cZero);
    for(;p!=e;) sum+=dot(*(p++),*(q++));
    return sum;
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  edot(const Array2DContent<T1>& A1, const Array2DContent<T2>& A2) {
    assert(IsSameSize(A1,A2));
    return dot(A1.base,A2.base);
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  edot(const Array2DContent<T1>& A, const Array2DContent<T2>& B,
       const int& alb, const int& blb, const unsigned int& nl) {
    assert(IsSameSize(A,B,alb,blb,nl));
    int ale=alb+static_cast<int>(nl-1);
    int ab=static_cast<int>(A[alb].start-A.infra.start->start);
    int bb=static_cast<int>(B[blb].start-B.infra.start->start);
    unsigned int s;
    s=static_cast<unsigned int>(A[ale].head+A[ale].last-A[alb].start+1);
    return dot(A.base.B.base,ab,bb,s);
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  edot(const Array2DContent<T1>& A, const Array2DContent<T2>& B,
       const unsigned int& nl) {
    assert(IsSameSize(A,B,nl));
    int le=static_cast<int>(nl-1);
    unsigned int s;
    s=static_cast<unsigned int>(A[le].head+A[le].last-A.infra.start->start+1);
    return dot(A.base,B.base,s);
  }

}

#endif

