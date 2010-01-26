
#include "matrix-rectangle.h"

namespace std {

  template <typename T>
  static T& getCData(varVector<refVector<T> >& L,
                     unsigned int I, unsigned int J) {
    return L[I][J];
  }

  template <typename T>
  static T& getFortranData(varVector<refVector<T> >& L,
                     unsigned int I, unsigned int J) {
    return L[J][I];
  }

  template <typename T>
  void rectMatrix<T>::SetGetMethod() {
    assert((this->MatrixOrder()>=0)&&(this->MatrixTransposeStatus()>=0));
    if(this->MatrixTransposeStatus()==Original)
      this->SetDataOrder(this->MatrixOrder());
    else if(this->MatrixTransposeStatus()==Transposed) {
      if(this->MatrixOrder()==COrder)       this->SetDataOrder(FortranOrder);
      else if(this->MatrixOrder()==FortranOrder)  this->SetDataOrder(COrder);
      else myError("Unknown Order for Matrix");
    } else myError("Unknown Transpose mode for Matrix");
    if(this->MatrixDataOrder()==COrder)
      this->AssignGetMethod(getCData);
    else if(this->MatrixDataOrder()==FortranOrder)
      this->AssignGetMethod(getFortranData);
    else myError("Unknown data order for Matrix");
  }

  template <typename T>
  void rectMatrix<T>::allocate(unsigned int M, unsigned int N,
                               int Ord, int Trans) {
    this->clear();
    this->SetSize(M,N);
    this->SetMatrixOrder(Ord);
    this->SetMatrixTransposeStatus(Trans);
    SetGetMethod();
    this->Data.allocate(M*N);
    if(this->MatrixDataOrder()==COrder) {
      this->Lines.allocate(M);
      for(unsigned int i=0,n=0;i<M;++i,n+=N)
        this->Lines[i].refer(this->data(),n,N);
    } else if(this->MatrixDataOrder()==FortranOrder) {
      this->Lines.allocate(N);
      for(unsigned int i=0,m=0;i<N;++i,m+=M)
        this->Lines[i].refer(this->data(),m,M);
    } else myError("Unknown data order for Matrix");
  }

  template <typename T>
  const char* rectMatrix<T>::type() { return "Rectangle Matrix"; }

}

