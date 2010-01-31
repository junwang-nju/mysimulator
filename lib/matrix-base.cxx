
#include "matrix-base.h"

namespace std {

  template <typename T, unsigned int MType, template<typename> class VecType>
  void MatrixBase<T,MType,VecType>::clear() {
    getElem=NULL;
    this->info()[NumberColumns]=uZero;
    this->info()[NumberRows]=uZero;
    this->info()[ActualOrder]=UnknownOrder;
    this->info()[TransposeState]=UnknowTranspose;
    this->info()[ExpectOrder]=UnknownOrder;
    static_cast<ParentType*>(this)->clear();
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  const unsigned int& MatrixBase<T,MType,VecType>::NumRow() const {
    return this->info()[NumberRows];
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  const unsigned int& MatrixBase<T,MType,VecType>::NumCol() const {
    return this->info()[NumberColumns];
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  const int& MatrixBase<T,MType,VecType>::MatrixOrder() const {
    return this->info()[ExpectOrder];
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  const int& MatrixBase<T,MType,VecType>::MatrixTransposeState()const{
    return this->info()[TransposeState];
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  const int& MatrixBase<T,MType,VecType>::MatrixActualOrder() const {
    return this->info()[ActualOrder];
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  void MatrixBase<T,MType,VecType>::SetSize(const unsigned int NR,
                                                     const unsigned int NC) {
    this->info()[NumberRows]=NR;
    this->info()[NumberColumns]=NC;
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  void MatrixBase<T,MType,VecType>::SetOrder(const int Ord) {
    this->info()[ExpectOrder]=Ord;
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  void MatrixBase<T,MType,VecType>::SetTranpose(const int Trans) {
    this->info()[TransposeState]=Trans;
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  void MatrixBase<T,MType,VecType>::SetActualOrder(const int AOrd) {
    this->info()[ActualOrder]=AOrd;
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  void MatrixBase<T,MType,VecType>::AssignGetMethod(
      const MatrixBase<T,MType,VecType>::GetElemFuncType& iGMethod){
    getElem=iGMethod;
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  T& MatrixBase<T,MType,VecType>::operator()(const unsigned int I,
                                                      const unsigned int J) {
    return getElem(this->structure(),I,J,OtherElems);
  }

  template <typename T, unsigned int MType, template<typename> class VecType>
  const T& MatrixBase<T,MType,VecType>::operator()(
      const unsigned int I, const unsigned int J) const {
    return getElem(this->structure(),I,J,OtherElems);
  }

}

