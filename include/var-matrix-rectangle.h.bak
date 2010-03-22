
#ifndef _Variable_Matrix_Rectangle_H_
#define _Variable_Matrix_Rectangle_H_

#include "matrix-rectangle-base.h"
#include "var-vector.h"

namespace std {

  template <typename T>
  class varMatrixRectangle : public RectMatrixBase<T,varVector> {

    public:

      typedef varMatrixRectangle<T>   Type;

      typedef RectMatrixBase<T,varVector>   ParentType;

      varMatrixRectangle() : ParentType() {}

      varMatrixRectangle(const unsigned int M, const unsigned int N,
                         const int Order=COrder, const int Trans=NoTranspose)
        : ParentType() { allocate(M,N,Order,Trans); }

      varMatrixRectangle(const Type&) {
        myError("Cannot create from variable rectangle matrix");
      }

      virtual ~varMatrixRectangle() {}

      Type& operator=(const Type& vRM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vRM));
        return *this;
      }

      template <unsigned int iMType, template <typename> class iVecType,
                unsigned int iNInf>
      Type& operator=(const MatrixBase<T,iMType,iVecType,iNInf>& M) {
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
                    const int Order=COrder, const int Trans=NoTranspose) {
        this->clear();
        this->SetSize(M,N);
        this->SetOrder(Order);
        this->SetTransposeState(Trans);
        this->SetGetMethod();
        this->data().allocate(M*N);
        if(this->MatrixActualOrder()==COrder) {
          this->structure().allocate(M);
          for(unsigned int i=0,n=0;i<M;++i,n+=N)
            this->structure()[i].refer(this->data(),n,N);
        } else if(this->MatrixActualOrder()==FortranOrder) {
          this->structure().allocate(N);
          for(unsigned int i=0,n=0;i<N;++i,n+=M)
            this->structure()[i].refer(this->data(),n,M);
        } else myError("Improper order for rectangle matrix");
      }

      virtual const char* type() const { return "Variable Rectangle Matrix"; }

  };

}

#endif

