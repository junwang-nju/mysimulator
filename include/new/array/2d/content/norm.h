
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
  T norm(const Array2DContent<T>& A) { return norm(A.base); }

}

#endif

