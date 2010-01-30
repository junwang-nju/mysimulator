
#ifndef _Matrix_Rectangle_H_
#define _Matrix_Rectangle_H_

#include "matrix-base.h"

namespace std {
  enum RectangleInfoItems {
    RectangleNumberItems=NumberCommonItems
  };
  template <typename T, template<typename> class VecType>
  class RectMatrixBase : public MatrixBase<T,Rectangle,VecType> {
    public:
      typedef RectMatrixBase<T,VecType>   Type;
      typedef MatrixBase<T,Rectangle,VecType>   ParentType;
      RectMatrixBase() : ParentType() {}
      RectMatrixBase(const Type& RMB) {
        myError("Cannot create from rectangle matrix base");
      }
      virtual ~RectMatrixBase() {}
      Type& operator=(const Type& RMB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(RMB));
        return *this;
      }
      template <unsigned int iMType, template<typename> class iVecType>
      Type& operator=(const MatrixBase<T,iMType,iVecType>& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }
      Type& operator=(const VectorBase<T>& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }
      Type& operator=(const T& D) {
        static_cast<ParentType*>(this)->operator=(D);
        return *this;
      }
    protected:
      void SetGetMethod();
  };
}

#endif

