
#ifndef _Array_2D_Content_Fill_H_
#define _Array_2D_Content_Fill_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/fill.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void fill(Array2DContent<T1>& A, const T2& d) {
    assert(IsValid(A));
    fill(A.base,d);
  }

  template <typename T1, typename T2>
  void fill(Array2DContent<T1>& A, const T2& d, const int& lb,
            const unsigned int& ld, const unsigned int& nl, const int& rb,
            const unsigned int& rd, const unsigned int& nr) {
    assert(IsValid(A,lb,ld,nl,rb,rd,nr));
    Array1DContent<T1>* p=A.infra.head+lb;
    Array1DContent<T1>* e=p+ld*nl;
    for(;p!=e;p+=ld)  fill(*p,rb,rd,nr);
  }

  template <typename T1, typename T2>
  void fill(Array2DContent<T1>& A, const T2& d, const int& lb,
            const unsigned int& nl, const int& rb, const unsigned int& nr) {
    assert(IsValid(A,lb,nl,rb,nr));
    Array1DContent<T1>* p=A.infra.head+lb;
    Array1DContent<T1>* e=p+nl;
    for(;p!=e;) fill(*(p++),rb,nr);
  }

  template <typename T1, typename T2>
  void fill(Array2DContent<T1>& A, const T2& d, const unsigned int& nl,
            const unsigned int& nr) {
    assert(IsValid(A,nl,nr));
    Array1DContent<T1>* p=A.infra.start;
    Array1DContent<T1>* e=p+nl;
    for(;p!=e;) fill(*(p++),nr);
  }

  template <typename T1, typename T2>
  void fill(Array2DContent<T1>& A, const T2& d, const int& lb,
            const unsigned int& nl) {
    assert(IsValid(A)&&IsValid(A.infra,lb,nl));
    int le=lb+static_cast<int>(nl-1);
    int ab=static_cast<int>(A[lb].start-A.infra.start->start);
    unsigned int s;
    s=static_cast<unsigned int>(A[le].head+A[le].last-A[lb].start+1);
    fill(A.base,d,ab,s);
  }

  template <typename T1, typename T2>
  void fill(Array2DContent<T1>& A, const T2& d, const unsigned int& nl) {
    assert(IsValid(A)&&IsValid(A.infra,nl));
    int le=static_cast<int>(nl-1);
    unsigned int s;
    s=static_cast<unsigned int>(A[le].head+A[le].last-A.infra.start->start+1);
    fill(A.base,d,s);
  }

}

#endif

