
#ifndef _Matrix_Input_Output_H_
#define _Matrix_Input_Output_H_

#include "data/basic/matrix.h"
#include "data/basic/output-base.h"

namespace std {

  template <typename T>
  OutputBase& operator<<(OutputBase& os, const Matrix<T>& M) {
    os<<M(0,0);
    for(int j=1;j<M.property[MatrixNumberColumn];++j) os<<"\t"<<M(0,j);
    for(int i=1;i<M.property[MatrixNumberRow];++i) {
      os<<Endl<<M(i,0);
      for(int j=1;j<M.property[MatrixNumberColumn];++j) os<<"\t"<<M(i,j);
    }
    return os;
  }

}

#endif

