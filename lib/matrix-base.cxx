
#include "matrix-base.h"

namespace std {

  template <typename T, template<typename> class VecType>
  void MatrixBase<T,VecType>::clear() {
    getElem=NULL;
    this->info()[NumberColumns]=uZero;
    this->info()[NumberRows]=uZero;
    this->info()[ActualOrder]=UnknownOrder;
    this->info()[TransposeState]=UnknowTranspose;
    this->info()[ExpectOrder]=UnknownOrder;
    this->data().clear();
    this->structure.clear();
  }

  template <typename T, template<typename> class VecType>
  const unsigned int& MatrixBase<T,VecType>::NumRow() const {
    return this->info()[NumberRows];
  }

  template <typename T, template<typename> class VecType>
  const unsigned int& MatrixBase<T,VecType>::NumCol() const {
    return this->info()[NumberColumns];
  }

  template <typename T, template<typename> class VecType>
  const int& MatrixBase<T,VecType>::MatrixOrder() const {
    return this->info()[ExpectOrder];
  }

  template <typename T, template<typename> class VecType>
  const int& MatrixBase<T,VecType>::MatrixTransposeState() const {
    return this->info()[TransposeState];
  }

  template <typename T, template<typename> class VecType>
  const int& MatrixBase<T,VecType>::MatrixActualOrder() const {
    return this->info()[ActualOrder];
  }

  template <typename T, template<typename> class VecType>
  void MatrixBase<T,VecType>::SetSize(const unsigned int NR,
                                      const unsigned int NC) {
    this->info()[NumberRows]=NR;
    this->info()[NumberColumns]=NC;
  }

  template <typename T, template<typename> class VecType>
  void MatrixBase<T,VecType>::SetOrder(const int Ord) {
    this->info()[ExpectOrder]=Ord;
  }

  template <typename T, template<typename> class VecType>
  void MatrixBase<T,VecType>::SetTranpose(const int Trans) {
    this->info()[TransposeState]=Trans;
  }

  template <typename T, template<typename> class VecType>
  void MatrixBase<T,VecType>::SetActualOrder(const int AOrd) {
    this->info()[ActualOrder]=AOrd;
  }

  template <typename T, template<typename> class VecType>
  void MatrixBase<T,VecType>::AssignGetMethod(
      const MatrixBase<T,VecType>::GetElemFuncType& iGMethod){
    getElem=iGMethod;
  }

  template <typename T, template<typename> class VecType>
  T& MatrixBase<T,VecType>::operator()(const unsigned int I,
                                       const unsigned int J) {
    return getElem(this->structure(),I,J,OtherElems);
  }

  template <typename T, template<typename> class VecType>
  const T& MatrixBase<T,VecType>::operator()(const unsigned int I,
                                             const unsigned int J) const {
    return getElem(this->structure(),I,J,OtherElems);
  }

}

