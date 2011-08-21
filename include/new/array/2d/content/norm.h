
#ifndef _Array_2D_Content_Norm_H_
#define _Array_2D_Content_Norm_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/norm.h"

namespace mysimulator {

  template <typename T>
  T normSQ(const Array2DContent<T>& A, const int& lb, const unsigned int& ld,
           const unsigned int& ln, const int& rb, const unsigned int& rd,
           const unsigned int& rn) {
    assert(IsValid(A,lb,ld,ln,rb,rd,rn));
    Array1DContent<T>* p=const_cast<Array1DContent<T>*>(A.infra.head)+lb;
    Array1DContent<T>* e=p+ld*ln;
    T sum;
    copy(sum,cZero);
    for(;p!=e;p+=ld)  sum+=normSQ(*p,rb,rd,rn);
    return sum;
  }

  template <typename T>
  T normSQ(const Array2DContent<T>& A, const int& lb, const unsigned int& ln,
           const int& rb, const unsigned int& rn) {
    assert(IsValid(A,lb,ln,rb,rn));
    Array1DContent<T>* p=const_cast<Array1DContent<T>*>(A.infra.head)+lb;
    Array1DContent<T>* e=p+ln;
    T sum;
    copy(sum,cZero);
    for(;p!=e;) sum+=normSQ(*(p++),rb,rn);
    return sum;
  }

  template <typename T>
  T normSQ(const Array2DContent<T>& A, const unsigned int& ln,
           const unsigned int& rn) {
    assert(IsValid(A,ln,rn));
    Array1DContent<T>* p=const_cast<Array1DContent<T>*>(A.infra.start);
    Array1DContent<T>* e=p+ln;
    T sum;
    copy(sum,cZero);
    for(;p!=e;) sum+=normSQ(*(p++),rn);
    return sum;
  }

  template <typename T>
  T normSQ(const Array2DContent<T>& A) { return normSQ(A.base); }

  template <typename T>
  T enormSQ(const Array2DContent<T>& A, const int& lb, const unsigned int& nl) {
    assert(IsValid(A)&&IsValid(A.infra,lb,nl));
    int le=lb+static_cast<int>(nl-1);
    int ab=static_cast<int>(A[lb].start-A.infra.start->start);
    unsigned int s;
    s=static_cast<unsigned int>(A[le].head+A[le].last-A[lb].start+1);
    return normSQ(A.base,ab,s);
  }

  template <typename T>
  T normSQ(const Array2DContent<T>& A, const unsigned int& nl) {
    assert(IsValid(A)&&IsValid(A.infra,nl));
    int le=static_cast<int>(nl-1);
    unsigned int s;
    s=static_cast<unsigned int>(A[le].head+A[le].last-A.infra.start->start+1);
    return normSQ(A.base,s);
  }

}

#include "intrinsic-type/square-root.h"

namespace mysimulator {

  template <typename T>
  T norm(const Array2DContent<T>& A, const int& lb, const unsigned int& ld,
         const unsigned int& ln, const int& rb, const unsigned int& rd,
         const unsigned int& rn) {
    return sqroot(normSQ(A,lb,ld,ln,rb,rd,rn));
  }

  template <typename T>
  T norm(const Array2DContent<T>& A, const int& lb, const unsigned int& ln,
         const int& rb, const unsigned int& rn) {
    return sqroot(normSQ(A,lb,ln,rb,rn));
  }

  template <typename T>
  T norm(const Array2DContent<T>& A, const unsigned int& ln,
         const unsigned int& rn) { return sqroot(normSQ(A,ln,rn));  }

  template <typename T>
  T norm(const Array2DContent<T>& A) { return norm(A.base); }

  template <typename T>
  T enorm(const Array2DContent<T>& A, const int& lb, const unsigned int& nl) {
    assert(IsValid(A)&&IsValid(A.infra,lb,nl));
    int le=lb+static_cast<int>(nl-1);
    int ab=static_cast<int>(A[lb].start-A.infra.start->start);
    unsigned int s;
    s=static_cast<unsigned int>(A[le].head+A[le].last-A[lb].start+1);
    return norm(A.base,ab,s);
  }

  template <typename T>
  T norm(const Array2DContent<T>& A, const unsigned int& nl) {
    assert(IsValid(A)&&IsValid(A.infra,nl));
    int le=static_cast<int>(nl-1);
    unsigned int s;
    s=static_cast<unsigned int>(A[le].head+A[le].last-A.infra.start->start+1);
    return norm(A.base,s);
  }

}

#endif

