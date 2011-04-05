
#ifndef _Vector_Interface_H_
#define _Vector_Interface_H_

#include "vector/state-name.h"
#include "io/error.h"
#include "intrinsic-type/constant.h"
#include "generic/release.h"
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
      if(state==AllocatedVector)  releaseArray(pdata);
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

}

#endif

