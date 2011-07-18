
#ifndef _Array_1D_Refer_H_
#define _Array_1D_Refer_H_

#include "array/1d/interface.h"
#include "pointer/refer.h"
#include "intrinsic-type/refer.h"

namespace mysimulator {

  template <typename T>
  void refer(Array1D<T>& v, const Array1D<T>& rv,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(rv));
    typedef typename Array1D<T>::ParentType PType;
    refer(static_cast<PType&>(v),static_cast<const PType&>(rv));
    assert(parte>partb);
    assert((partb>=rv.first)&&(parte<=rv.last));
    refer(v.size,parte-partb+1);
    refer(v.first,newb);
    refer(v.last,newb+parte-partb);
    refer(v.head,rv.head+partb-newb);
    v.start=v.head+v.first;
  }

  template <typename T>
  void refer(Array1D<T>& v, const Array1D<T>& rv,
             const int& partb, const int& parte) {
    refer(v,rv,partb,parte,partb);
  }

  template <typename T>
  void refer(Array1D<T>& v, const Array1D<T> rv) {
    refer(v,rv,rv.first,rv.last);
  }

  template <typename T>
  void refer(Array1D<T>& v, const Array1D<T> rv, const unsigned int& n) {
    assert(rv.size>=n);
    refer(v,rv,rv.first,rv.first+n-1);  // first+n is not checked for overflow
  }

}

#endif

