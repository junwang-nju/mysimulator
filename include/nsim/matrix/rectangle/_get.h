
#ifndef _Matrix_Rectange_Get_Func_H_
#define _Matrix_Rectange_Get_Func_H_

#include "array/2d/interface.h"

namespace mysimulator {

  template <typename T>
  T& _GetRegularC(Array2D<T>& V,unsigned int m,unsigned int n) {
    return V[m][n];
  }

  template <typename T>
  T& _GetRegularFortran(Array2D<T>& V,unsigned int m,unsigned int n) {
    return V[n][m];
  }

}

#endif

