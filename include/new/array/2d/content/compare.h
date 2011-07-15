
#ifndef _Array_2D_Content_Compare_H_
#define _Array_2D_Content_Compare_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/compare.h"

namespace mysimulator {

  template <typename T1, typename T2>
  bool IsSameSize(const Array2DContent<T1>& A1, const Array2DContent<T2>& A2) {
    if(!IsSameSize(A1.base,A2.base))    return false;
    if(!IsSameSize(A1.infra,A2.infra))  return false;
    Array1DContent<T1>* p=const_cast<Array1DContent<T1>*>(A1.infra.start);
    Array1DContent<T2>* q=const_cast<Array1DContent<T2>*>(A2.infra.start);
    Array1DContent<T1>* e=p+A1.NumLines();
    for(;p!=e;) if(!IsSameSize(*(p++),*(q++)))  return false;
    return true;
  }

  template <typename T1, typename T2>
  bool IsSameSize(const Array2DContent<T1>& A1, const Array2DContent<T2>& A2,
                  const int& lb1, const int& lb2, const unsigned int& nl) {
    assert(IsValid(A1)&&IsValid(A2));
    assert(IsValid(A1.infra,lb1,nl)&&IsValid(A2.infra,lb2,nl));
    Array1DContent<T1>* p=const_cast<Array1DContent<T1>*>(A1.infra.head+lb1);
    Array1DContent<T2>* q=const_cast<Array1DContent<T2>*>(A2.infra.head+lb2);
    Array1DContent<T1>* e=p+nl;
    for(;p!=e;) if(!IsSameSize(*(p++),*(q++)))  return false;
    return true;
  }

  template <typename T1, typename T2>
  bool IsSameSize(const Array2DContent<T1>& A1, const Array2DContent<T2>& A2,
                  const unsigned int& nl) {
    assert(IsValid(A1)&&IsValid(A2));
    assert(IsValid(A1.infra,nl)&&IsValid(A2.infra,nl));
    Array1DContent<T1>* p=const_cast<Array1DContent<T1>*>(A1.infra.start);
    Array1DContent<T2>* q=const_cast<Array1DContent<T2>*>(A2.infra.start);
    Array1DContent<T1>* e=p+nl;
    for(;p!=e;) if(!IsSameSize(*(p++),*(q++)))  return false;
    return true;
  }

}

#endif

