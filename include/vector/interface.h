
#ifndef _Vector_Interface_H_
#define _Vector_Interface_H_

#include "vector/state-name.h"
#include "io/error.h"
#include "intrinsic-type/constant.h"
#include <cassert>

namespace mysimulator {

  template <typename T>
  struct Vector {

    typedef Vector<T>   Type;

    T* pdata;
    unsigned int size;
    VectorStateName state;

    Vector() : pdata(NULL), size(uZero), state(UnusedVector) {}
    Vector(const unsigned int n)
      : pdata(NULL), size(uZero), state(UnusedVector) {
      allocate(*this,n);
    }
    Vector(const Type&) { Error("Copier of Vector Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Vector Disabled!");
      return *this;
    }
    ~Vector() { clearData(); }

    void clearData() {
      if(state==UnusedVector) return;
      if(state==AllocatedVector)  release(pdata);
      else pdata=NULL;
      size=uZero;
      state=UnusedVector;
    }
    T*& operator()() { return pdata; }
    const T* operator()() const { return pdata; }
    T& operator[](const int I) { assert(IsValid(*this)); return *(pdata+I); }
    const T& operator[](const int I) const {
      assert(IsValid(*this));
      return *(pdata+I);
    }

  };

  template <typename T>
  bool IsValid(const Vector<T>& v) {
    return (v()!=NULL)&&(v.state!=UnusedVector);
  }
  template <typename T>
  void release(Vector<T>& v) { v.clearData(); }
  template <typename T>
  void allocate(Vector<T>& v, const unsigned int n) {
    assert(n>0);
    release(v);
    v.pdata=new T[n];
    v.size=n;
    v.state=AllocatedVector;
  }
  template <typename T>
  void imprint(Vector<T>& v, const Vector<T>& cv) {
    assert(IsValid(cv));
    release(v);
    allocate(v,cv.size);
    for(unsigned int i=0;i<v.size;++i) imprint(v[i],cv[i]);
  }
  template <typename T>
  void getSubvec(Vector<T>& v, const T* ptr, const unsigned int sz) {
    assert((ptr!=NULL)&&(sz>0));
    release(v);
    v.data=const_cast<T*>(ptr);
    v.size=sz;
    v.state=SubVector;
  }
  template <typename T>
  void getSubvec(Vector<T>& v, const Vector<T>& cv) {
    getSubvec(v,cv.pdata,cv.size);
  }
  template <typename T, typename cT>
  void copy(Vector<T>& v, const Vector<cT>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    unsigned int n=(v.size<cv.size?v.size:cv.size);
    T* p=v.pdata;
    cT* cp=const_cast<cT*>(cv.pdata);
    T* pend=p+n;
    for(;p!=pend;) copy(*(p++),*(cp++));
  }
  template <typename T, typename cT>
  void copy(Vector<T>& v, const cT& d) {
    assert(IsValid(v));
    T* p=v.pdata;
    T* pend=p+v.size;
    for(;p!=pend;)  copy(*(p++),d);
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void copy(Vector<double>& v, const Vector<double>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,const_cast<double*>(cv()),const_cast<long*>(&lOne),
           v(),const_cast<long*>(&lOne));
  }
  void copy(Vector<double>& v, const double& d) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),const_cast<double*>(&d),
           const_cast<long*>(&lZero),v.pdata,const_cast<long*>(&lOne));
  }
  template <typename T>
  void copy(Vector<double>& v, const T& d) {
    double dd;
    copy(dd,d);
    copy(v,dd);
  }

  void copy(Vector<float>& v, const Vector<float>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,const_cast<float*>(cv()),const_cast<long*>(&lOne),
           v(),const_cast<long*>(&lOne));
  }
  void copy(Vector<float>& v, const float& f) {
    assert(IsValid(v));
    scopy_(reinterpret_cast<long*>(&(v.size)),const_cast<float*>(&f),
           const_cast<long*>(&lZero),v.pdata,const_cast<long*>(&lOne));
  }
  template <typename T>
  void copy(Vector<float>& v, const T& f) {
    float ff;
    copy(ff,f);
    copy(v,ff);
  }

  void copy(Vector<long long>& v, const Vector<long long>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,reinterpret_cast<double*>(const_cast<long long*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }
  void copy(Vector<long long>& v, const long long& ll) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<double*>(const_cast<long long*>(&ll)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<unsigned long long>& v,
            const Vector<unsigned long long>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,reinterpret_cast<double*>(const_cast<unsigned long long*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }
  void copy(Vector<unsigned long long>& v, const unsigned long long& ll) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<double*>(const_cast<unsigned long long*>(&ll)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<int>& v, const Vector<int>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<int*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }
  void copy(Vector<int>& v, const int& i) {
    assert(IsValid(v));
    scopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<float*>(const_cast<int*>(&i)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<unsigned int>& v, const Vector<unsigned int>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<unsigned int*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }
  void copy(Vector<unsigned int>& v, const unsigned int& u) {
    assert(IsValid(v));
    scopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<float*>(const_cast<unsigned int*>(&u)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

}

#include <cstring>

namespace mysimulator {

  void copy(Vector<short>& v, const Vector<short>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n+n);
  }
  void copy(Vector<short>& v, const short& s) {
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

  void copy(Vector<unsigned short>& v, const Vector<unsigned short>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n+n);
  }
  void copy(Vector<unsigned short>& v, const unsigned short& s) {
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

  void copy(Vector<char>& v, const Vector<char>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n);
  }
  void copy(Vector<char>& v, const Vector<unsigned char>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n);
  }
  void copy(Vector<char>& v, const char& c) { memset(v(),c,v.size); }
  void copy(Vector<char>& v, const unsigned char& uc) { memset(v(),uc,v.size); }

  void copy(Vector<unsigned char>& v, const Vector<unsigned char>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n);
  }
  void copy(Vector<unsigned char>& v, const Vector<char>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    memcpy(v(),cv(),n);
  }
  void copy(Vector<unsigned char>& v, const unsigned char& uc) {
    memset(v(),uc,v.size);
  }
  void copy(Vector<unsigned int>& v, const char& c) { memset(v(),c,v.size); }

}

#endif

