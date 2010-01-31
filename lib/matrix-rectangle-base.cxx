
#include "matrix-rectangle-base.h"

namespace std {

  template <typename T, template<typename> class VecType>
  static T& getCData(VecType<refVector<T> >& Ls, unsigned int I,
                     unsigned int J, T& Other) {
    return Ls[I][J];
  }

  template <typename T, template<typename> class VecType>
  static T& getFortranData(VecType<refVector<T> >& Ls, unsigned int I,
                           unsigned int J, T& Other) {
    return Ls[J][I];
  }

  template <typename T, template<typename> class VecType>
  void RectMatrixBase<T,VecType>::SetGetMethod() {
    assert(this->MatrixOrder()>=0);
    assert(this->MatrixTransposeState()>=0);
    if(this->MatrixTransposeState()==NoTranspose)
      this->SetActualOrder(this->MatrixOrder());
    else if(this->MatrixTransposeState()==WithTranspose) {
      if(this->MatrixOrder()==COrder) this->SetActualOrder(FortranOrder);
      else if(this->MatrixOrder()==FortranOrder)  this->SetActualOrder(COrder);
      else myError("matrix order is not proper");
    } else myError("unknown mode of transpose state for matrix");
    if(this->MatrixActualOrder()==COrder)
      this->AssignGetMethod(getCData<T,VecType>);
    else if(this->MatrixActualOrder()==FortranOrder)
      this->AssignGetMethod(getFortranData<T,VecType>);
    else myError("improper actual order for matrix rectangle more");
  }

}

