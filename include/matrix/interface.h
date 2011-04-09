
#ifndef _Matrix_Interface_H_
#define _Matrix_Interface_H_

#include "list/interface.h"

namespace mysimulator {

  template <typename T>
  struct Matrix : public List<T> {

    typedef Matrix<T>   Type;
    typedef List<T>     ParentType;

    typedef T& (*GetFuncType)(Vector<Vector<T> >&,
                              const unsigned int,const unsigned int,T&);

    Vector<unsigned int> property;
    Object<T> other;
    GenFuncType GetFunc;

    Matrix() : ParentType(), property(), other(), GetFunc(NULL) {}
    Matrix(const Type&) { Error("Copier of Matrix Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Matrix Disabled!");
      return *this;
    }
    ~Matrix() { clearData(); }

    void clearData() {
      release(property);
      release(other);
      M.GetFunc=NULL;
      release(static_cast<ParentType&>(M));
    }
    T& operator()(const unsigned int I, const unsigned int J) {
      return GetFunc(infra,I,J,other());
    }
    const T& operator()(const unsigned int I, const unsigned int J) const {
      return GetFunc(infra,I,J,other());
    }

  };

  template <typename T>
  bool IsValid(const Matrix<T>& M) {
    return IsValid(M.property)&&IsValid(M.GetFunc)&&
           IsValid(static_cast<const List<T>&>(M));
  }

  template <typename T>
  void release(Matrix<T>& M) { M.clearData(); }

}

#endif

