
#ifndef _Reference_Matrix_Triangle_H_
#define _Reference_Matrix_Triangle_H_

#include "matrix-triangle-base.h"
#include "ref-vector.h"
#include "var-vector.h"

namespace std {

  template <typename T, template <typename> class VecType=varVector>
  class refTriangMatrix
    : public refObject<TriangMatrixBase<T,refVector>,
                       TriangMatrixBase<T,VecType> > {

    public:

      typedef refTriangMatrix<T,VecType>  Type;

      typedef refObject<TriangMatrixBase<T,refVector>,
                        TriangMatrixBase<T,VecType> >
              ParentType;

      refTriangMatrix() : ParentType() {}

      refTriangMatrix(const Type& rTM) {
        myError("Cannot create from reference triangle matrix");
      }

      virtual ~refTriangMatrix() {}

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

      virtual void refer(ParentType& rTM) {
        if(this->data().IsAvailable()) this->RefInfo().remove_self();
        this->data().refer(rTM.data());
        this->structure().refer(rTM.structure());
        this->info()=rTM.info();
        this->SetGetMethod();
        rTM.RefInfo().add_before(this->RefInfo());
      }

      virtual void refer(ObjectWStorage<TriangMatrixBase<T,VecType> >& TM) {
        if(this->data().IsAvailable()) this->RefInfo().remove_self();
        this->data().refer(TM.data());
        this->structure().refer(TM.structure());
        this->info()=TM.info();
        this->SetGetMethod();
        TM.RefList().append(this->RefInfo());
      }

      virtual const char* type() const { return "reference triangle matrix"; }

  };

}

#endif

