
#ifndef _Vector_Interface_H_
#define _Vector_Interface_H_

#include "vector/state-name.h"
#include "io/error.h"

namespace mysimulator {

  template <typename T>
  struct Vector {

    typedef Vector<T>   Type;

    T* pdata;
    unsigned int size;
    VectorStateName state;

    Vector() : pdata(NULL), size(uZero), state(UnusedVector) {}
    Vector(const Type&) { Error("Copier of Vector Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Vector Disabled!");
      return *this;
    }
    ~Vector() { clearData(); }

    void clearData() {
    }

  };

  template <typename T>
  void release(Vector<T>& v) { v.clearData(); }

}

#endif

