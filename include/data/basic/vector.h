
#ifndef _Vector_H_
#define _Vector_H_

#include "data/basic/vector-base.h"
#include "operation/basic/blas.h"
#include "operation/basic/memory.h"
#include "operation/basic/util.h"
#include <cassert>

namespace std {

  template <typename T>
  struct Vector : public VectorBase {

    typedef Vector<T>   Type;
    typedef VectorBase  ParentType;

    T* data;

    Vector() : ParentType(), data(NULL) {}
    Vector(const Type& v) : ParentType(v) {}
    Vector(const unsigned int n) : ParentType(), data(NULL) {
      allocate(*this,n);
    }
    Type& operator=(const Type& V) { myError("Copy Prohibited"); return *this; }
    ~Vector() { safe_release(data,state); }
    T*& operator()() { return data; }
    const T* operator()() const { return data; }
    T& operator[](const int I) { assert(IsAvailable(data)); return *(data+I); }
    const T& operator[](const int I) const {
      assert(IsAvailable(data));
      return *(data+I);
    }

  };

  template <typename T>
  bool IsAvailable(const Vector<T>& V) { return IsAvailable(V()); }

  template <typename T>
  void allocate(Vector<T>& V, const unsigned int n) {
    assert(n>0);
    release(V);
    V.data=new T[n];
    V.size=n;
    V.state=Allocated;
  }

  template <typename T>
  void release(Vector<T>& V) {
    safe_release(V.data,V.state);
    V.size=uZero;
    V.state=Unused;
  }

  template <typename T>
  void refer(Vector<T>& V, const Vector<T>& rV) {
    assert(IsAvailable(rV));
    release(V);
    V.data=rV.data;
    V.size=rV.size;
    V.state=Reference;
  }

  template <typename T>
  void refer(Vector<T>& V, const T* ptr, const unsigned int sz) {
    assert(IsAvailable(ptr));
    release(V);
    V.data=const_cast<T*>(ptr);
    V.size=sz;
    V.state=Reference;
  }

  template <typename T, typename cT>
  void copy(Vector<T>& V, const Vector<cT>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    unsigned int n=(V.size<cV.size?V.size:cV.size);
    T* p=V.data;
    cT* cp=const_cast<cT*>(cV.data);
    for(unsigned int i=0;i<n;++i,++p,++cp) copy(*p,*cp);
  }

  template <typename T, typename cT>
  void copy(Vector<T>& V, const cT& d) {
    assert(IsAvailable(V));
    T* p=V.data;
    for(unsigned int i=0;i<V.size;++i,++p) copy(*p,d);
  }

  void copy(Vector<double>& V, const Vector<double>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    long n=(V.size<cV.size?V.size:cV.size);
    dcopy_(&n,const_cast<double*>(cV.data),const_cast<long*>(&lOne),
           V.data,const_cast<long*>(&lOne));
  }

  void copy(Vector<double>& V, const double& d) {
    assert(IsAvailable(V));
    dcopy_(reinterpret_cast<long*>(&(V.size)),
           const_cast<double*>(&d),const_cast<long*>(&lZero),
           V.data,const_cast<long*>(&lOne));
  }

  template <typename T>
  void copy(Vector<double>& V, const T& d) {
    double dd;
    copy(dd,d);
    copy(V,dd);
  }

  void copy(Vector<float>& V, const Vector<float>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    long n=(V.size<cV.size?V.size:cV.size);
    scopy_(&n,const_cast<float*>(cV.data),const_cast<long*>(&lOne),
           V.data,const_cast<long*>(&lOne));
  }

  void copy(Vector<float>& V, const float& d) {
    assert(IsAvailable(V));
    scopy_(reinterpret_cast<long*>(&(V.size)),
           const_cast<float*>(&d),const_cast<long*>(&lZero),
           V.data,const_cast<long*>(&lOne));
  }

  template <typename T>
  void copy(Vector<float>& V, const T& d) {
    float fd;
    copy(fd,d);
    copy(V,fd);
  }

  void copy(Vector<int>& V, const Vector<int>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    long n=(V.size<cV.size?V.size:cV.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<int*>(cV.data)),
           const_cast<long*>(&lOne),
           reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne));
  }

  void copy(Vector<int>& V, const Vector<unsigned int>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    long n=(V.size<cV.size?V.size:cV.size);
    scopy_(&n,reinterpret_cast<float*>(const_cast<unsigned int*>(cV.data)),
           const_cast<long*>(&lOne),
           reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne));
  }

  void copy(Vector<int>& V, const int& d) {
    assert(IsAvailable(V));
    scopy_(reinterpret_cast<long*>(&V.size),
           reinterpret_cast<float*>(const_cast<int*>(&d)),
           const_cast<long*>(&lZero),
           reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne));
  }

  void copy(Vector<unsigned int>& V, const unsigned int& d) {
    assert(IsAvailable(V));
    scopy_(reinterpret_cast<long*>(&V.size),
           reinterpret_cast<float*>(const_cast<unsigned int*>(&d)),
           const_cast<long*>(&lZero),
           reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne));
  }

  void copy(Vector<int>& V, const unsigned int& d) {
    copy(V,static_cast<int>(d));
  }

  void copy(Vector<unsigned int>& V, const int& d) {
    copy(V,static_cast<unsigned int>(d));
  }

  template <typename T>
  ostream& operator<<(ostream& os, const Vector<T>& v) {
    assert(IsAvailable(v));
    os<<v[0];
    for(unsigned int i=1;i<v.size;++i)  os<<"\t"<<v[i];
    return os;
  }

  template <typename T>
  istream& operator>>(istream& is, Vector<T>& v) {
    assert(IsAvailable(v));
    for(unsigned int i=0;i<v.size;++i)  is>>v[i];
    return is;
  }

}

#endif
