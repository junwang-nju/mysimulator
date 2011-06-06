
#ifndef _Vector_Fill_H_
#define _Vector_Fill_H_

#include "vector/interface.h"
#include "intrinsic-type/fill.h"

namespace mysimulator {

  template <typename T, typename cT>
  void fill(Vector<T>& v, const cT& d) {
    assert(IsValid(v));
    T* p=v.pdata;
    T* pend=p+v.size;
    for(;p!=pend;)  fill(*(p++),d);
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void fill(Vector<long double>& v, const long double& ld) {
    assert(IsValid(v));
    scopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<float*>(const_cast<long double*>(&ld)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lThree));
    scopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<float*>(const_cast<long double*>(&ld))+1,
           const_cast<long*>(&lZero),reinterpret_cast<float*>(v())+1,
           const_cast<long*>(&lThree));
    scopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<float*>(const_cast<long double*>(&ld))+2,
           const_cast<long*>(&lZero),reinterpret_cast<float*>(v())+2,
           const_cast<long*>(&lThree));
  }

  template <typename cT>
  void fill(Vector<long double>& v, const cT& value) {
    long double u;
    fill(u,value);
    fill(v,u);
  }

  void fill(Vector<double>& v, const double& d) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),const_cast<double*>(&d),
           const_cast<long*>(&lZero),v.pdata,const_cast<long*>(&lOne));
  }

  template <typename cT>
  void fill(Vector<double>& v, const cT& value) {
    double u;
    fill(u,value);
    fill(v,u);
  }

  void fill(Vector<float>& v, const float& f) {
    assert(IsValid(v));
    scopy_(reinterpret_cast<long*>(&(v.size)),const_cast<float*>(&f),
           const_cast<long*>(&lZero),v.pdata,const_cast<long*>(&lOne));
  }

  template <typename cT>
  void fill(Vector<float>& v, const cT& value) {
    float u;
    fill(u,value);
    fill(v,u);
  }

  void fill(Vector<long long>& v, const long long& ll) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<double*>(const_cast<long long*>(&ll)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  template <typename cT>
  void fill(Vector<long long>& v, const cT& value) {
    long long u;
    fill(u,value);
    fill(v,u);
  }

  void fill(Vector<unsigned long long>& v, const unsigned long long& ll) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<double*>(const_cast<unsigned long long*>(&ll)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  template <typename cT>
  void fill(Vector<unsigned long long>& v, const cT& value) {
    unsigned long long u;
    fill(u,value);
    fill(v,u);
  }

  void fill(Vector<int>& v, const int& i) {
    assert(IsValid(v));
    scopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<float*>(const_cast<int*>(&i)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

  template <typename cT>
  void fill(Vector<int>& v, const cT& value) {
    int u;
    fill(u,value);
    fill(v,u);
  }

  void fill(Vector<unsigned int>& v, const unsigned int& u) {
    assert(IsValid(v));
    scopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<float*>(const_cast<unsigned int*>(&u)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

  template <typename cT>
  void fill(Vector<unsigned int>& v, const cT& value) {
    unsigned int u;
    fill(u,value);
    fill(v,u);
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

  template <typename cT>
  void fill(Vector<short>& v, const cT& value) {
    short u;
    fill(u,value);
    fill(v,u);
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

  template <typename cT>
  void fill(Vector<unsigned short>& v, const cT& value) {
    unsigned short u;
    fill(u,value);
    fill(v,u);
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
