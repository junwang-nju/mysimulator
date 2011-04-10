
#ifndef _Matrix_InputOutput_H_
#define _Matrix_InputOutput_H_

#include "matrix/interface.h"
#include "io/output/interface.h"
#include "matrix/base/property-name.h"

namespace mysimulator {

  template <typename T>
  OutputBase& operator<<(OutputBase& os, const Matrix<T>& M) {
    os<<M(0,0);
    for(unsigned int j=1;j<M.property[MatrixNumberColumns];++j)
      os<<"\t"<<M(0,j);
    for(unsigned int i=1;i<M.property[MatrixNumberRows]l++i) {
      os<<Endl<<M(i,0);
      for(unsigned int j=1;j<M.property[MatrixNumberColumns];++j)
        os<<"\t"<<M(i,j);
    }
    return os;
  }

}

#endif

