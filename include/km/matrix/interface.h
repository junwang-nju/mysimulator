
#ifndef _Matrix_Interface_H_
#define _Matrix_Interface_H_

#include "array2d-numeric/interface.h"

namespace mysimulator {

  template <typename T>
  class Matrix : public Array2DNumeric<T> {

    public:

      typedef Matrix<T>   Type;
      typedef Array2DNumeric<T>   ParentType;

    protected:

      MatrixName _name;
    private:

      Matrix(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

