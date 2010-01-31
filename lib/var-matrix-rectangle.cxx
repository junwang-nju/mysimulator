
#include "var-matrix-rectangle.h"

namespace std {

  template <typename T>
  void varRectMatrix<T>::allocate(const unsigned int M, const unsigned int N,
                                  const int Order, const int Trans) {
    this->clear();
    this->info().allocate(RectangleNumberItems);
    this->SetSize(M,N);
    this->SetOrder(Order);
    this->SetTransposeState(Trans);
    this->SetGetMethod();
    this->data().allocate(M*N);
    if(this->MatrixActualOrder()==COrder) {
      this->structure().allocate(M);
      for(unsigned int i=0,n=0;i<M;++i,n+=M)
        this->structure()[i].refer(this->data(),n,N);
    } else if(this->MatrixActualOrder()==FortranOrder) {
      this->structure().allocate(N);
      for(unsigned int i=0,m=0;i<N;++i,m+=N)
        this->structure()[i].refer(this->data(),m,M);
    } else myError("improper order for rectangle matrix");
  }

  template <typename T>
  const char* varRectMatrix<T>::type() const {
    return "variable Rectangle Matrix";
  }

}

