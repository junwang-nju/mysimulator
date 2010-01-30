
#include "matrix-rectangle-base.h"

namespace std {

  template <typename T>
  static T& getCData(varVector<refVector<T> >& Ls, unsigned int I,
                     unsigned int J, T& Other) {
    return Ls[I][J];
  }

  template <typename T>
  static T& getFortranData(varVector<refVector<T> >& Ls, unsigned int I,
                     unsigned int J, T& Other) {
    return Ls[J][I];
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  void RectMatrixBase<T,MType,VecType>::SetGetMethod() {
    assert(this->MatrixOrder()>=0);
    assert(this->MatrixTransposeState()>=0);
    if(this->MatrixTransposeState()==NoTranspose)
      this->SetActualOrder(this->MatrixOrder());
    else if(this->MatrixTransposeState()==WithTranspose) {
      if(this->MatrixOrder()==COrder) this->SetActualOrder(FortranOrder);
      else if(this->MatrixOrder()==FortranOrder)  this->SetActualOrder(COrder);
      else myError("matrix order is not proper");
    } else myError("unknown mode of transpose state for matrix");
    if(this->MatrixActualOrder()==Corder) this->AssignGetMethod(getCData);
    else if(MatrixActualOrder==FortranOrder)
        this->AssignGetMethod(getFortranData);
    else myErro("improper actual order for matrix rectangle more");
  }

}

