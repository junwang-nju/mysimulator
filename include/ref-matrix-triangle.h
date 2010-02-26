
#ifndef _Reference_Matrix_Triangle_H_
#define _Reference_Matrix_Triangle_H_

#include "matrix-triangle-base.h"

namespace std {

  template <typename T>
  class refMatrixTriangle : public TriangMatrixBase<T,refVector> {

    public:

      typedef refMatrixTriangle<T>    Type;

      typedef TriangMatrixBase<T,refVector>   ParentType;

      refMatrixTriangle() : ParentType() {}

      refMatrixTriangle(const Type&) {
        myError("Cannot create from reference triangle matrix");
      }

      virtual ~refMatrixTriangle() {}

      Type& operator=(const Type& rTM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rTM));
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const TriangMatrixBase<T,iVecType>& TM) {
        static_cast<ParentType*>(this)->operator=(TM);
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
      void refer(const TriangMatrixBase<T,iVecType>& TM) {
        this->data().refer(TM.data());
        this->structure().refer(TM.structure());
        this->info()=TM.info();
        this->SetOtherElements(TM.OtherElements());
        this->AssignGetMethod(TM.GetElementMethod());
      }

  };

}

#endif

