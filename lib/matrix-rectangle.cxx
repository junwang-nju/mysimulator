
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
    assert((this->Order>=0)&&(this->Transpose>=0));
    if(this->Transpose==Original) this->DataOrder=this->Order;
    else if(this->Transpose==Transposed) {
      if(this->Order==COrder)  this->DataOrder=FortranOrder;
      else if(this->Order==FortranOrder)  this->DataOrder=COrder;
      else myError("Unknown Order for Matrix");
    } else myError("Unknown Transpose mode for Matrix");
    if(this->DataOrder==COrder)
      this->getUnit=getCData;
    else if(this->DataOrder==FortranOrder)
      this->getUnit=getFortranData;
    else myError("Unknown data order for Matrix");
  }

  template <typename T>
  void rectMatrix<T>::allocate(unsigned int M, unsigned int N,
                               int Ord, int Trans) {
    this->clear();
    this->NRow=M;
    this->NCol=N;
    this->Order=Ord;
    this->Transpose=Trans;
    SetGetMethod();
    this->Data.allocate(M*N);
    if(this->DataOrder==COrder) {
      this->Lines.allocate(M);
      for(unsigned int i=0,n=0;i<M;++i,n+=N)
        this->Lines[i].refer(this->Data,n,N);
    } else if(this->DataOrder==FortranOrder) {
      this->Lines.allocate(N);
      for(unsigned int i=0,m=0;i<N;++i,m+=M)
        this->Lines[i].refer(this->Data,m,M);
    } else myError("Unknown data order for Matrix");
  }

}

