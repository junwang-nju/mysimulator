
#ifndef _Reference_Matrix_Rectangle_H_
#define _Reference_Matrix_Rectangle_H_

#include "matrix-rectangle-base.h"

namespace std {

  template <typename T>
  class refMatrixRectangle : public RectMatrixBase<T,refVector> {

    public:

      typedef refMatrixRectangle<T>   Type;

      typedef RectMatrixBase<T,refVector> ParentType;

      refMatrixRectangle() : ParentType() {}

      refMatrixRectangle(const Type&) {
        myError("Cannot create from reference rectangle matrix");
      }

      ~refMatrixRectangle() {}

      Type& operator=(const Type& rRM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rRM));
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

      template <template <typename> class iVecType>
      void refer(const RectMatrixBase<T,iVecType>& RMB) {
        this->data().refer(RMB.data());
        this->structure().refer(RMB.structure());
        this->info()=RMB.info();
        this->SetGetMethod();
      }

      template <template <typename> class iVecType>
      void refer(const RectMatrixBase<T,iVecType>& RMB,
                 const unsigned int off, const unsigned int size) {
        unsigned int nl=RMB.structure()[0].size();
        this->data().refer(RMB.data(),off*nl,size*nl);
        this->structure().refer(RMB.structure(),off,size);
        this->info()=RMB.info();
        if(this->MatrixActualOrder()==COrder)
          this->info()[NumberRows]=size;
        else if(this->MatrixActualOrder()==FortranOrder)
          this->info()[NumberColumns]=size;
        else
          myError("Improper Order for Rectangle Matrix");
        this->SetGetMethod();
      }

      virtual const char* type() const { return "Reference Rectangle Matrix"; }

  };

}

#endif

