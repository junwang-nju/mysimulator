
#ifndef _Double_Vector_H_
#define _Double_Vector_H_

#include "vector-base.h"
#include "blas.h"
#include "memory.h"
#include "util.h"
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
    T& operator[](const int I) { return *(data+I); }
    const T& operator[](const int I) const { return *(data+I); }

  };

  template <typename T>
  bool IsAvailable(const Vector<T>& V) { return IsAvailable(V()); }

  template <typename T>
  void allocate(Vector<T>& V, const unsigned int n) {
    assert(n>0);
    release(V);
    V.data=new double[n];
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

  template <typename T, typename cT>
  void copy(Vector<T>& V, const Vector<cT>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    unsigned int n=(V.size<cV.size?V.size:cV.size);
    T* p=V.data;
    T* cp=const_cast<T*>(cV.data);
    for(unsigned int i=0;i<n;++i,++p,++cp) copy(*p,*cp);
  }

  template <typename T, typename cT>
  void copy(Vector<T>& V, const T& d) {
    assert(IsAvailable(V));
    T* p=V.data;
    for(unsigned int i=0;i<V.size;++i,++p) copy(*p,d);
  }

  void copy(Vector<double>& V, const Vector<double>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    long n=(V.size<cV.size?V.size:cV.size);
    dcopy_(&n,V.data,const_cast<long*>(&lOne),
              const_cast<double*>(cV.data),const_cast<long*>(&lOne));
  }

  void copy(Vector<double>& V, const double& d) {
    assert(IsAvailable(V));
    dcopy_(reinterpret_cast<long*>(&(V.size)),V.data,const_cast<long*>(&lOne),
           const_cast<double*>(&d),const_cast<long*>(&lOne));
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
    scopy_(&n,V.data,const_cast<long*>(&lOne),
              const_cast<float*>(cV.data),const_cast<long*>(&lOne));
  }

  void copy(Vector<float>& V, const float& d) {
    assert(IsAvailable(V));
    scopy_(reinterpret_cast<long*>(&(V.size)),V.data,const_cast<long*>(&lOne),
           const_cast<float*>(&d),const_cast<long*>(&lOne));
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
    scopy_(&n,reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne),
              reinterpret_cast<float*>(const_cast<int*>(cV.data)),
              const_cast<long*>(&lOne));
  }

  void copy(Vector<int>& V, const Vector<unsigned int>& cV) {
    assert(IsAvailable(V));
    assert(IsAvailable(cV));
    long n=(V.size<cV.size?V.size:cV.size);
    scopy_(&n,reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne),
              reinterpret_cast<float*>(const_cast<unsigned int*>(cV.data)),
              const_cast<long*>(&lOne));
  }

  void copy(Vector<int>& V, const int& d) {
    assert(IsAvailable(V));
    scopy_(reinterpret_cast<long*>(&V.size),
           reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne),
           reinterpret_cast<float*>(const_cast<int*>(&d)),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<int>& V, const unsigned int& d) {
    assert(IsAvailable(V));
    scopy_(reinterpret_cast<long*>(&V.size),
           reinterpret_cast<float*>(V.data),const_cast<long*>(&lOne),
           reinterpret_cast<float*>(const_cast<unsigned int*>(&d)),
           const_cast<long*>(&lOne));
  }

  void scale(Vector<double>& V, const double& d) {
    assert(IsAvailable(V));
    dscal_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(V.size))),
           const_cast<double*>(&d),V.data,const_cast<long*>(&lOne));
  }

  void scale(Vector<float>& V, const float& d) {
    assert(IsAvailable(V));
    sscal_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(V.size))),
           const_cast<float*>(&d),V.data,const_cast<long*>(&lOne));
  }

  template <typename T, typename sT>
  void scale(Vector<T>& V, const sT& d) {
    assert(IsAvailable(V));
    T* p=V.data;
    for(unsigned int i=0;i<V.size;++i,++p)  scale((*p),d);
  }

  template <typename sT>
  void scale(Vector<double>& V, const sT& d) {
    double dd;
    copy(dd,d);
    scale(V,dd);
  }

  template <typename sT>
  void scale(Vector<float>& V, const sT& d) {
    float fd;
    copy(fd,d);
    scale(V,fd);
  }

  void scale(Vector<double>& V, const Vector<double>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    long n=(V.size<sV.size?V.size:sV.size);
    static char flag[]="LNN";
    dtbmv_(flag,flag+1,flag+2,&n,const_cast<long*>(&lZero),
           const_cast<double*>(sV.data),const_cast<long*>(&lOne),V.data,
           const_cast<long*>(&lOne));
  }

  void scale(Vector<float>& V, const Vector<float>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    long n=(V.size<sV.size?V.size:sV.size);
    static char flag[]="LNN";
    stbmv_(flag,flag+1,flag+2,&n,const_cast<long*>(&lZero),
           const_cast<float*>(sV.data),const_cast<long*>(&lOne),V.data,
           const_cast<long*>(&lOne));
  }

  template <typename T, typename sT>
  void scale(Vector<T>& V, const Vector<sT>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    unsigned int n=(V.size<sV.size?V.size:sV.size);
    T* p=V.data;
    sT* sp=const_cast<int*>(sV.data);
    for(unsigned int i=0;i<n;++i,++p,++sp)  scale((*p),(*sp));
  }

  template <typename T, typename sT, typename fT>
  void scale(Vector<T>& V, const Vector<sT>& sV, const fT& d) {
    scale(V,sV);
    scale(V,d);
  }

  template <typename T, typename sT, typename fT>
  void scale(Vector<T>& V, const fT& d, const Vector<sT>& sV) {
    scale(V,sV);
    scale(V,d);
  }

  void shift(Vector<double>& V, const double& d, const Vector<double>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    long n=(V.size<sV.size?V.size:sV.size);
    daxpy_(&n,const_cast<double*>(&d),const_cast<double*>(sV.data),
           const_cast<long*>(&lOne),V.data,const_cast<long*>(&lOne));
  }

  void shift(Vector<float>& V, const float& d, const Vector<float>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    long n=(V.size<sV.size?V.size:sV.size);
    saxpy_(&n,const_cast<float*>(&d),const_cast<float*>(sV.data),
           const_cast<long*>(&lOne),V.data,const_cast<long*>(&lOne));
  }

  template <typename T, typename sT, typename fT>
  void shift(Vector<T>& V, const fT& d, const Vector<sT>& sV) {
    assert(IsAvailable(V));
    assert(IsAvailable(sV));
    unsigned int n=(V.size<sV.size?V.size:sV.size);
    T* p=V.data;
    sT* sp=const_cast<sT*>(sV.data);
    for(unsigned int i=0;i<n;++i,++p,++sp) shift(*p,d,*sp);
  }

  template <typename T, typename sT, typename fT>
  void shift(Vector<T>& V, const Vector<sT>& sV, const fT& d) {
    shift(V,d,sV);
  }

  template <typename T>
  void shift(Vector<double>& V, const T& d, const Vector<double>& sV) {
    double dd;
    copy(dd,d);
    shift(V,dd,sV);
  }

  template <typename T>
  void shift(Vector<float>& V, const T& d, const Vector<float>& sV) {
    float dd;
    copy(dd,d);
    shift(V,dd,sV);
  }

  template <typename T, typename sT>
  void shift(Vector<float>& V, const Vector<sT>& sV) { shift(V,lOne,sV); }

  void shift(Vector<double>& V, const double& d) {
    assert(IsAvailable(V));
    daxpy_(reinterpret_cast<long*>(&(V.size)),
           const_cast<double*>(&d),const_cast<double*>(&dOne),
           const_cast<long*>(&lZero),V.data,const_cast<long*>(&lOne));
  }

  void shift(Vector<float>& V, const float& d) {
    assert(IsAvailable(V));
    daxpy_(reinterpret_cast<long*>(&(V.size)),
           const_cast<float*>(&d),const_cast<float*>(&dOne),
           const_cast<long*>(&lZero),V.data,const_cast<long*>(&lOne));
  }

  template <typename T, typename fT>
  void shift(Vector<T>& V, const fT& d) {
    assert(IsAvailable(V));
    T* p=V.data;
    for(unsigned int i=0;i<V.size;++i,++p)  shift(*p,d,iOne);
  }
  
  template <typename T>
  void shift(Vector<double>& V, const T& d) {
    double& dd;
    copy(dd,d);
    shift(V,dd);
  }

  template <typename T>
  void shift(Vector<float>& V, const T& d) {
    float& dd;
    copy(dd,d);
    shift(V,dd);
  }

}

#endif
