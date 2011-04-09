
#ifndef _Vector_Interface_H_
#define _Vector_Interface_H_

#include "vector/state-name.h"
#include "io/error.h"
#include "intrinsic-type/constant.h"
#include "generic/release.h"

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
      assert(n>0);
      clearData();
      pdata=new T[n];
      size=n;
      state=AllocatedVector;
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
    void getSubvec(const T* ptr, const unsigned int sz) {
      assert((ptr!=NULL)&&(sz>0));
      release(*this);
      pdata=const_cast<T*>(ptr);
      size=sz;
      state=SubVector;
    }
    void getSubvec(const Vector<T>& cv) { getSubvec(cv.pdata,cv.size); }

  };

  template <typename T>
  bool IsValid(const Vector<T>& v) {
    return (v()!=NULL)&&(v.state!=UnusedVector);
  }
  template <typename T>
  void release(Vector<T>& v) { v.clearData(); }

}

#endif

