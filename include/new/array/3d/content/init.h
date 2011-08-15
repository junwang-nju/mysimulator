
#ifndef _Array_3D_Content_Init_H_
#define _Array_3D_Content_Init_H_

#include "array/3d/content/interface.h"
#include "array/2d/content/init.h"

namespace mysimulator {

  template <typename T>
  void init(Array3DContent<T>& A, const T* const& ptr,
            const Array1DContent<T>* const& s2ptr,
            const Array2DContent<T>* const& s3ptr, const unsigned int& np,
            const unsigned int& nl, const unsigned int& nr) {
    init(A.base,ptr,np*nl*nr);
    init(A.base2,s2ptr,np*nl);
    init(A.infra,s3ptr,np);
    Array1DContent<T>* p=A.base2.start;
    Array1DContent<T>* e=p+np*nl;
    T* q=const_cast<T* const&>(ptr);
    for(;p!=e;q+=nr)  init(*(p++),q,nr);
    Array2DContent<T>* p2= A.infra.start;
    Array2DContent<T>* e2=p+np;
    T* q2=const_cast<T* const&>(ptr);
    Array1DContent<T>* r2=const_cast<Array1DContent<T>*>(s2ptr);
    unsigned int pd=nl*nr;
    for(;p2!=e2;q2+=pd,r2+=nl)  init(*(p2++),q2,r2,nl,nr);
  }

  template <typename T>
  void init(Array3DContent<T>& A, const T* const& ptr,
            const Array1DContent<T>* const& s2ptr,
            const Array2DContent<T>* const& s3ptr, const int& pb, const int& pe,
            const int& lb, const int& le, const int& rb, const int& re) {
    unsigned int np,nl,nr;
    np=static_cast<unsigned int>(pe-pb+1);
    nl=static_cast<unsigned int>(le-lb+1);
    nr=static_cast<unsigned int>(re-rb+1);
    init(A.base,ptr,np*nl*nr);
    init(A.base2,s2ptr,np*nl);
    init(A.infra,s3ptr,np);
    Array1DContent<T>* p=A.base2.start;
    Array1DContent<T>* e=p+np*nl;
    T* q=const_cast<T* const&>(ptr);
    for(;p!=e;q+=nr)  init(*(p++),q,rb,re);
    Array2DContent<T>* p2= A.infra.start;
    Array2DContent<T>* e2=p+np;
    T* q2=const_cast<T* const&>(ptr);
    Array1DContent<T>* r2=const_cast<Array1DContent<T>*>(s2ptr);
    unsigned int pd=nl*nr;
    for(;p2!=e2;q2+=pd,r2+=nl)  init(*(p2++),q2,r2,lb,le,rb,re);
  }

}

#endif

