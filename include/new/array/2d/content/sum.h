
#ifndef _Array_2D_Content_Sum_H_
#define _Array_2D_Content_Sum_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/sum.h"

namespace mysimulator {

  template <typename T>
  T sum(const Array2DContent<T>& A, const int& lb, const unsigned int& ld,
        const unsigned int& ln, const int& rb, const unsigned int& rd,
        const unsigned int& rn) {
    assert(IsValid(A,lb,ld,ln,rb,rd,rn));
    Array1DContent<T>* p=const_cast<Array1DContent<T>*>(A.infra.head)+lb;
    Array1DContent<T>* e=p+ld*ln;
    T s;
    copy(s,cZero);
    for(;p!=e;p+=ld)  s+=sum(*p,rb,rd,rn);
    return s;
  }

  template <typename T>
  T sum(const Array2DContent<T>& A, const int& lb, const unsigned int& ln,
        const int& rb, const unsigned int& rn) {
    assert(IsValid(A,lb,ln,rb,rn));
    Array1DContent<T>* p=const_cast<Array1DContent<T>*>(A.infra.head)+lb;
    Array1DContent<T>* e=p+ln;
    T s;
    copy(s,cZero);
    for(;p!=e;)  s+=sum(*(p++),rb,rn);
    return s;
  }

  template <typename T>
  T sum(const Array2DContent<T>& A, const unsigned int& ln,
        const unsigned int& rn) {
    assert(IsValid(A,ln,rn));
    Array1DContent<T>* p=const_cast<Array1DContent<T>*>(A.infra.start);
    Array1DContent<T>* e=p+ln;
    T s;
    copy(s,cZero);
    for(;p!=e;)  s+=sum(*(p++),rn);
    return s;
  }

  template <typename T>
  T sum(const Array2DContent<T>& A) { return sum(A.base); }

  template <typename T>
  T esum(const Array2DContent<T>& A, const int& lb, const unsigned int& nl) {
    assert(IsValid(A)&&IsValid(A.infra,lb,nl));
    int le=lb+static_cast<int>(nl-1);
    int ab=static_cast<int>(A[lb].start-A.infra.start->start);
    unsigned int s;
    s=static_cast<unsigned int>(A[le].head+A[le].last-A[lb].start+1);
    return sum(A.base,ab,s);
  }

  template <typename T>
  T sum(const Array2DContent<T>& A, const unsigned int& nl) {
    assert(IsValid(A)&&IsValid(A.infra,nl));
    int le=static_cast<int>(nl-1);
    unsigned int s;
    s=static_cast<unsigned int>(A[le].head+A[le].last-A.infra.start->start+1);
    return sum(A.base,s);
  }

}

#endif

