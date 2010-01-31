
#ifndef _Variable_Matrix_Rectangle_H_
#define _Variable_Matrix_Rectangle_H_

#include "object-with-storage.h"
#include "matrix-rectangle-base.h"
#include "var-vector.h"

namespace std {
  template <typename T>
  class varRectMatrix
    : public ObjectWStorage<RectMatrixBase<T,varVector> > {
    public:
      typedef varRectMatrix<T>    Type;
      typedef ObjectWStorage<RectMatrixBase<T,varVector> >
              ParentType;
      varRectMatrix() : ParentType() {}
      varRectMatrix(const unsigned int M, const unsigned int N,
                    const int Order=COrder, const int Trans=NoTranspose)
        : ParentType() {
        allocate(M,N,Order,Trans);
      }
      varRectMatrix(const Type& vRM) {
        myError("Cannot create from variable rectangle matrix");
      }
      virtual ~varRectMatrix() {}
      Type& operator=(const Type& vRM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vRM));
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
      void allocate(const unsigned int M, const unsigned int N,
                    const int Order=COrder, const int Trans=NoTranspose);
      virtual const char* type() const;
  };
}

#endif

