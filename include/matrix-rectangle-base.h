
#ifndef _Matrix_Rectangle_H_
#define _Matrix_Rectangle_H_

#include "matrix-base.h"

namespace std {

  template <typename T, template<typename> class VecType>
  static T& getCData(VecType<refVector<T> >& Ls, unsigned int I,
                     unsigned int J, T& Other) {
    return Ls[I][J];
  }

  template <typename T, template<typename> class VecType>
  static T& getFortranData(VecType<refVector<T> >& Ls, unsigned int I,
                           unsigned int J, T& Other) {
    return Ls[J][I];
  }

  enum RectangleInfoItems {
    RectangleNumberItems=NumberCommonItems
  };

  template <typename T, template<typename> class VecType>
  class RectMatrixBase
    : public MatrixBase<T,Rectangle,VecType,RectangleNumberItems> {

    public:

      typedef RectMatrixBase<T,VecType>   Type;

      typedef MatrixBase<T,Rectangle,VecType,RectangleNumberItems>   ParentType;

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

      template <unsigned int iMType, template<typename> class iVecType, unsigned int iNInf>
      Type& operator=(const MatrixBase<T,iMType,iVecType,iNInf>& V) {
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

      void SetGetMethod() {
        assert(this->MatrixOrder()>=0);
        assert(this->MatrixTransposeState()>=0);
        if(this->MatrixTransposeState()==NoTranspose)
          this->SetActualOrder(this->MatrixOrder());
        else if(this->MatrixTransposeState()==WithTranspose) {
          if(this->MatrixOrder()==COrder) this->SetActualOrder(FortranOrder);
          else if(this->MatrixOrder()==FortranOrder)
            this->SetActualOrder(COrder);
          else myError("matrix order is not proper");
        } else myError("unknown mode of transpose state for matrix");
        if(this->MatrixActualOrder()==COrder)
          this->AssignGetMethod(getCData<T,VecType>);
        else if(this->MatrixActualOrder()==FortranOrder)
          this->AssignGetMethod(getFortranData<T,VecType>);
        else myError("improper actual order for matrix rectangle more");
      }

  };

}

#endif

