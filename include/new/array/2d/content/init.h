
#ifndef _Array_2D_Content_Init_H_
#define _Array_2D_Content_Init_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/init.h"

namespace mysimulator {

  template <typename T>
  void init(Array2DContent<T>& A, const T* const& ptr,
            const Array1DContent<T>* const& sptr, const unsigned int& nl,
            const unsigned int& nr) {
    init(A.base,ptr,nl*nr);
    init(A.infra,sptr,nl);
    Array1DContent<T>* p=A.infra.start;
    Array1DContent<T>* e=p+nl;
    T* q=const_cast<T* const&>(ptr);
    for(;p!=e;q+=nr)  init(*(p++),q,nr);
  }

  template <typename T>
  void init(Array2DContent<T>& A, const T* const& ptr,
            const Array1DContent<T>* const& sptr, const int& lb, const int& le,
            const int& rb, const int& re) {
    unsigned int nl,nr;
    nl=static_cast<unsigned int>(le-lb+1);
    nr=static_cast<unsigned int>(re-rb+1);
    init(A.base,ptr,nl*nr);
    init(A.infra,sptr,lb,le);
    Array1DContent<T>* p=A.infra.start;
    Array1DContent<T>* e=p+nl;
    T* q=const_cast<T* const&>(ptr);
    for(;p!=e;q+=nr)  init(*(p++),q,rb,re);
  }

  template <typename T>
  void init(Array2DContent<T>& A, const T* const& ptr,
            const Array1DContent<T>* const& sptr,
            const unsigned int& s, const Array1DContent<unsigned int>& n) {
    init(A.base,ptr,s);
    init(A.infra,sptr,n.size);
    Array1DContent<T>* p=A.infra.start;
    Array1DContent<T>* e=p+n.size;
    T* q=const_cast<T* const&>(ptr);
    unsigned int* r=n.start;
    for(;p!=e;q+=*(r++))  init(*(p++),q,0,(*r)-1);
  }

  template <typename T>
  void init(Array2DContent<T>& A, const T* const& ptr,
            const Array1DContent<T>* const& sptr, 
            const unsigned int& s, const int& lfst,
            const Array1DContent<int>& fst, const Array1DContent<int>& lst) {
    init(A.base,ptr,0,s-1);
    init(A.infra,sptr,lfst,lfst+static_cast<int>(fst.size-1));
    Array1DContent<T>* p=A.infra.start;
    Array1DContent<T>* e=p+fst.size;
    T* q=const_cast<T* const&>(ptr);
    int* rb=const_cast<int*>(fst.start);
    int* re=const_cast<int*>(lst.start);
    for(;p!=e;q+=*(re++)-*(rb++)+1) init(*(p++),q,*rb,*re);
  }

}

#endif

