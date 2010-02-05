
#ifndef _Reference_Rectangle_Matrix_H_
#define _Reference_Rectangle_Matrix_H_

#include "matrix-rectangle-base.h"
#include "ref-object.h"
#include "var-vector.h"

namespace std {
  template <typename T, template<typename> class VecType=varVector>
  class refRectMatrix
    : public refObject<RectMatrixBase<T,refVector>,RectMatrixBase<T,VecType> >{
    public:
      typedef refRectMatrix<T,VecType>  Type;
      typedef refObject<RectMatrixBase<T,refVector>,RectMatrixBase<T,VecType> >
              ParentType;
      refRectMatrix() : ParentType() {}
      refRectMatrix(const Type& rRM) {
        myError("Cannot create from reference rectangle matrix");
      }
      ~refRectMatrix() {}
      Type& operator=(const Type& rRM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rRM));
        return *this;
      }
      template <unsigned int iMType, template<typename> class iVecType>
      Type& operator=(const MatrixBase<T,iMType,iVecType>& M) {
        static_cast<ParentType*>(this)->operator=(M);
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
      virtual void refer(ParentType& O);
      virtual void refer(ObjectWStorage<RectMatrixBase<T,VecType> >&);
      virtual const char* type() const;
  };
}

#endif

