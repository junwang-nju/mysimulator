
#ifndef _Matrix_Rectangle_H_
#define _Matrix_Rectangle_H_

#include "matrix-base.h"

namespace std {
  template <typename T>
  class rectMatrix : public MatrixBase<T> {
    public:
      typedef T   DataType;
      typedef rectMatrix<T>   Type;
      typedef MatrixBase<T>   ParentType;
      rectMatrix() : ParentType() {}
      rectMatrix(unsigned int M, unsigned int N,
                 int Ord=COrder, int Trans=Original) : ParentType() {
        allocate(M,N,Ord,Trans);
      }
      rectMatrix(const Type& RM) {
        myError("Cannot create from Rectangle Matrix");
      }
      virtual ~rectMatrix() {}
      Type& operator=(const Type& RM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(RM));
        return *this;
      }
      template <typename inputT>
      Type& operator=(const inputT& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }
    protected:
      void SetGetMethod();
    public:
      void allocate(unsigned int M, unsigned int N,
                    int Ord=COrder, int Trans=Original);
      virtual const char* type();
  };
}

#endif

