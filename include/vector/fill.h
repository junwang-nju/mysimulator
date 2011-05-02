
#ifndef _Vector_Fill_H_
#define _Vector_Fill_H_

#include "vector/interface.h"
#include "intrinsic-type/fill.h"

namespace mysimulator {

  template <typename T>
  void fill(Vector<T>& v, const T& d) {
    assert(IsValid(v));
    T* p=v.pdata;
    T* pend=p+v.size;
    for(;p!=pend;)  fill(*(p++),d);
  }

  template <typename T, typename cT>
  void fill(Vector<T>& v, const cT& value) {
    assert(IsValid(v));
    T u;
    fill(u,value);
    fill(v,u);
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void fill(Vector<double>& v, const double& d) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),const_cast<double*>(&d),
           const_cast<long*>(&lZero),v.pdata,const_cast<long*>(&lOne));
  }

  void fill(Vector<float>& v, const float& f) {
    assert(IsValid(v));
    scopy_(reinterpret_cast<long*>(&(v.size)),const_cast<float*>(&f),
           const_cast<long*>(&lZero),v.pdata,const_cast<long*>(&lOne));
  }

  void fill(Vector<long long>& v, const long long& ll) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<double*>(const_cast<long long*>(&ll)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void fill(Vector<unsigned long long>& v, const unsigned long long& ll) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<double*>(const_cast<unsigned long long*>(&ll)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void fill(Vector<int>& v, const int& i) {
    assert(IsValid(v));
    scopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<float*>(const_cast<int*>(&i)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

  void fill(Vector<unsigned int>& v, const unsigned int& u) {
    assert(IsValid(v));
    scopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<float*>(const_cast<unsigned int*>(&u)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

}

#include <cstring>

namespace mysimulator {
  
  void fill(Vector<short>& v, const short& s) {
    assert(IsValid(v));
    unsigned long long ll=s;
    ll=(ll<<16)|ll;
    ll=(ll<<32)|ll;
    unsigned int nd=(v.size>>2),nr=(v.size&3),nb=v.size-nr;
    dcopy_(reinterpret_cast<long*>(&nd),reinterpret_cast<double*>(&ll),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
    memcpy(v()+nb,&ll,nr+nr);
  }

  void fill(Vector<unsigned short>& v, const unsigned short& s) {
    assert(IsValid(v));
    unsigned long long ll=s;
    ll=(ll<<16)|ll;
    ll=(ll<<32)|ll;
    unsigned int nd=(v.size>>2),nr=(v.size&3),nb=v.size-nr;
    dcopy_(reinterpret_cast<long*>(&nd),reinterpret_cast<double*>(&ll),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
    memcpy(v()+nb,&ll,nr+nr);
  }
  
  void fill(Vector<char>& v, const char& c) {
    assert(IsValid(v));
    memset(v(),c,v.size);
  }
  void fill(Vector<char>& v, const unsigned char& uc) {
    assert(IsValid(v));
    memset(v(),uc,v.size);
  }

  void fill(Vector<unsigned char>& v, const unsigned char& uc) {
    assert(IsValid(v));
    memset(v(),uc,v.size);
  }
  void fill(Vector<unsigned int>& v, const char& c) {
    assert(IsValid(v));
    memset(v(),c,v.size);
  }

}

#endif
