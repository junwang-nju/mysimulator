
#ifndef _Matrix_H_
#define _Matrix_H_

namespace std {

  template <typename T>
  struct Matrix : public Vector<T> {
    typedef Matrix<T> Type;
    typedef Vector<T> ParentType;
    typedef T& (*GetFuncType)(T**,const int,const int,T&);
    
    T** Structure;
  };

}

#endif
