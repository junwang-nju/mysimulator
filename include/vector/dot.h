
#ifndef _Vector_Dot_H_
#define _Vector_Dot_H_

#include "vector/interface.h"
#include "intrinsic-type/product-type.h"

namespace mysimulator {

  template <typename Ta, typename Tb>
  typename _Product<Ta,Tb>::Type
  dot(const Vector<Ta>& va, const Vector<Tb>& vb) {
    typedef typename _Product<Ta,Tb>::Type T;
    assert(IsValid(va)&&IsValid(vb));
    unsigned int n=(va.size<vb.size?va.size:vb.size);
    T sum;
    copy(sum,static_cast<T>(cZero));
    Ta* ap=va();
    Tb* bp=vb();
    Ta* pend=ap+n;
    for(;ap!=pend;) shift(sum,*(ap++),*(bp++));
    return sum;
  }

  double dot(const Vector<double>& va, const Vector<double>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    return ddot_(&n,const_cast<double*>(va()),const_cast<long*>(&lOne),
                    const_cast<double*>(vb()),const_cast<long*>(&lOne));
  }

  float dot(Vector<float>& va, Vector<float>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    return sdot_(&n,const_cast<float*>(va()),const_cast<long*>(&lOne),
                    const_cast<float*>(vb()),const_cast<long*>(&lOne));
  }

}

#endif

