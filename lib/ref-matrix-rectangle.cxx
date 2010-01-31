
#include "ref-matrix-rectangle.h"

namespace std {

  template <typename T, template<typename> class VecType>
  void refRectMatrix<T,VecType>::refer(refRectMatrix<T,VecType>& rRM) {
    this->data().refer(rRM.data());
    this->structure().refer(rRM.structure());
    this->info().refer(rRM.info());
    this->SetGetMethod();
  }

  template <typename T, template<typename> class VecType>
  void refRectMatrix<T,VecType>::refer(
      ObjectWStorage<RectMatrixBase<T,VecType> >& M) {
    this->data().refer(M.data());
    this->structure().refer(M.structure());
    this->info().refer(M.info());
    this->SetGetMethod();
  }

  template <typename T, template<typename> class VecType>
  const char* refRectMatrix<T,VecType>::type() const {
    return "reference rectangle matrix";
  }

}

