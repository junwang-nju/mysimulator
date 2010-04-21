
#ifndef _Vector_H_
#define _Vector_H_

#include "vector-impl.h"
#include "storage-state-name.h"
#include "error-proc.h"
#include "util.h"

namespace std {

  template <typename T>
  struct Vector {

    typedef Vector<T>   Type;

    T* data;
    unsigned int size;
    unsigned int state;

    Vector() : data(NULL), size(uZero), state(Unused) {}
    Vector(const Type&) { myError("Cannot create from Vector"); }
    Type& operator=(const Type& V) { assign(*this,V); return *this; }
    ~Vector() { release(*this); }

    T*& operator()() { return data; }
    const T* operator()() const { return data; }
    T& operator[](const int I) { return data[I]; }
    const T& operator[](const int I) const { return data[I]; }

  };

  template <typename T>
  void allocate(Vector<T>& v, const unsigned int vsize) {
    release(v);
    allocate(v(),vsize);
    v.size=vsize;
    v.state=Allocated;
  }

  template <typename T>
  void release(Vector<T>& v) {
    if(v.state==Allocated)  release(v());
    else v()=NULL;
    v.size=0;
    v.state=Unused;
  }

  template <typename T>
  void refer(Vector<T>& dest, const Vector<T>& src) {
    release(dest);
    dest()=src();
    dest.size=src.size();
    dest.state=Reference;
  }

  template <typename T>
  void assign(Vector<T>& dest, const Vector<T>& src) {
    unsigned int n=(dest.size<src.size?dest.size:src.size);
    assign(dest(),src(),n);
  }

  template <typename T>
  void assign(Vector<T>& v, const T& value) { assign(v(),value,v.size); }

  void assign(Vector<unsigned int>& v, const unsigned int value) {
    assign(v(),value,v.size);
  }

  void assign(Vector<int>& v, const int value) { assign(v(),value,v.size); }

  void assign(Vector<double>& v, const double value) {
    assign(v(),value,v.size);
  }

  template <typename T>
  void scale(Vector<T>& v, const T& value) { scale(v(),value,v.size); }

  template <typename T>
  void scale(Vector<T>& v, const Vector<T>& vf) {
    unsigned int n=(v.size<vf.size?v.size:vf.size);
    scale(v(),vf(),n);
  }

  template <typename T>
  void shift(Vector<T>& v, const T& fac, const Vector<T>& vfac) {
    unsigned int n=(v.size<vfac.size?v.size:vfac.size);
    shift(v(),fac,vfac(),n);
  }

  template <typename T>
  void shift(Vector<T>& v, const Vector<T>& vfac) {
    unsigned int n=(v.size<vfac.size?v.size:vfac.size);
    shift(v(),vfac(),n);
  }

  template <typename T>
  void shift(Vector<T>& v, const T& fac) { shift(v(),fac,v.size); }

  template <typename T>
  void shift(Vector<T>& v, const Vector<T>& vfac, const T& fac) {
    shift(v,fac,vfac);
  }

  template <typename T>
  void scaleshift(Vector<T>& v, const T& dfac, const T& fac,
                  const Vector<T>& sfac, const Vector<T>& vfac) {
    unsigned int n=(v.size<vfac.size?v.size:vfac.size);
    n=(n<sfac.size?n:sfac.size);
    scaleshift(v(),dfac,fac,sfac(),vfac(),n);
  }

  template <typename T>
  void scaleshift(Vector<T>& v, const T& dfac, const T& fac,
                  const Vector<T>& vfac) {
    unsigned int n=(v.size<vfac.size?v.size:vfac.size);
    scaleshift(v(),dfac,fac,vfac(),n);
  }

  template <typename T>
  void shift(Vector<T>& v, const T& fac, const Vector<T>& sfac,
             const Vector<T>& vfac) {
    unsigned int n=(v.size<vfac.size?v.size:vfac.size);
    n=(n<sfac.size?n:sfac.size);
    shift(v(),fac,sfac(),vfac(),n);
  }

  template <typename T>
  void exchange(Vector<T>& va, Vector<T>& vb) {
    unsigned int n=(va.size<vb.size?va.size:vb.size);
    exchange(va(),vb(),n);
  }

  template <typename T>
  void swap(Vector<T>& va, Vector<T>& vb) {
    swap(va.data,vb.data);
    swap(va.size,vb.size);
    swap(va.state,vb.state);
  }

  template <typename T>
  T dot(const Vector<T>& va, const Vector<T>& vb) {
    unsigned int n=(va.size<vb.size?va.size:vb.size);
    return dot(va(),vb(),n);
  }

  template <typename T>
  T normSQ(const Vector<T>& v) { return normSQ(v(),v.size); }

  double norm(const Vector<double>& v) { return norm(v(),v.size); }

  template <typename T>
  T asum(const Vector<T>& v) { return asum(v(),v.size); }

  template <typename T>
  bool IsAvailable(const Vector<T>& v){ return IsAvailable(v()); }

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

