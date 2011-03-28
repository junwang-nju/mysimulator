
#ifndef _Vector_Exchange_H_
#define _Vector_Exchange_H_

#include "vector/interface.h"
#include "intrinsic-type/exchange.h"

namespace mysimulator {

  template <typename T>
  void exchange(Vector<T>& va, Vector<T>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    unsigned int n=(va.size<vb.size?va.size:vb.size);
    T* ap=va();
    T* bp=vb();
    T* pend=ap+n;
    for(;ap!=pend;) exchange(*(ap++),*(bp++));
  }

  void exchange(Vector<long double>& va, Vector<long double>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    long dn=n+n;
    dswap_(&dn,reinterpret_cast<double*>(va()),const_cast<long*>(&lOne),
               reinterpret_cast<double*>(vb()),const_cast<long*>(&lOne));
  }

  void exchange(Vector<double>& va, Vector<double>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    dswap_(&n,va(),const_cast<long*>(&lOne),vb(),const_cast<long*>(&lOne));
  }

  void exchange(Vector<float>& va, Vector<float>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    sswap_(&n,va(),const_cast<long*>(&lOne),vb(),const_cast<long*>(&lOne));
  }

  void exchange(Vector<long long>& va, Vector<long long>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    long dn=n+n;
    dswap_(&dn,reinterpret_cast<double*>(va()),const_cast<long*>(&lOne),
               reinterpret_cast<double*>(vb()),const_cast<long*>(&lOne));
  }

  void exchange(Vector<unsigned long long>& va,Vector<unsigned long long>& vb){
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    long dn=n+n;
    dswap_(&dn,reinterpret_cast<double*>(va()),const_cast<long*>(&lOne),
               reinterpret_cast<double*>(vb()),const_cast<long*>(&lOne));
  }

  void exchange(Vector<int>& va, Vector<int>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    sswap_(&n,reinterpret_cast<float*>(va()),const_cast<long*>(&lOne),
              reinterpret_cast<float*>(vb()),const_cast<long*>(&lOne));
  }

  void exchange(Vector<unsigned int>& va, Vector<unsigned int>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    sswap_(&n,reinterpret_cast<float*>(va()),const_cast<long*>(&lOne),
              reinterpret_cast<float*>(vb()),const_cast<long*>(&lOne));
  }

  void exchange(Vector<long>& va, Vector<long>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    sswap_(&n,reinterpret_cast<float*>(va()),const_cast<long*>(&lOne),
              reinterpret_cast<float*>(vb()),const_cast<long*>(&lOne));
  }

  void exchange(Vector<unsigned long>& va, Vector<unsigned long>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    sswap_(&n,reinterpret_cast<float*>(va()),const_cast<long*>(&lOne),
              reinterpret_cast<float*>(vb()),const_cast<long*>(&lOne));
  }

  void exchange(Vector<short>& va, Vector<short>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    long nd=(n>>1),nr=(n&1),nb=n-nr;
    sswap_(&nd,reinterpret_cast<float*>(va()),const_cast<long*>(&lOne),
               reinterpret_cast<float*>(vb()),const_cast<long*>(&lOne));
    if(nr!=0) exchange(va[nb],vb[nb]);
  }

  void exchange(Vector<unsigned short>& va, Vector<unsigned short>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    long n=(va.size<vb.size?va.size:vb.size);
    long nd=(n>>1),nr=(n&1),nb=n-nr;
    sswap_(&nd,reinterpret_cast<float*>(va()),const_cast<long*>(&lOne),
               reinterpret_cast<float*>(vb()),const_cast<long*>(&lOne));
    if(nr!=0) exchange(va[nb],vb[nb]);
  }

  void exchange(Vector<char>& va, Vector<char>& vb) {
    assert(IsValid(va)&&IsValid(vb));
    unsigned int n=(va.size<vb.size?va.size:vb.size);
    long nd=(n>>2);
    unsigned int nr=(n&3),nb=n-nr;
    sswap_(&nd,reinterpret_cast<float*>(va()),const_cast<long*>(&lOne),
               reinterpret_cast<float*>(vb()),const_cast<long*>(&lOne));
    for(unsigned int i=nb;i<n;++i)  exchange(va[i],vb[i]);
  }

}

#endif

