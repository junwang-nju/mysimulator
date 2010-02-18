
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

      template <unsigned int iMType, template<typename> class iVecType,
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

      virtual void refer(ParentType& rRM) {
        if(this->data().IsAvailable()) this->RefInfo().remove_self();
        this->data().refer(rRM.data());
        this->structure().refer(rRM.structure());
        this->info()=rRM.info();
        this->SetGetMethod();
        rRM.RefInfo().add_before(this->RefInfo());
      }

      virtual void refer(ObjectWStorage<RectMatrixBase<T,VecType> >& M) {
        if(this->data().IsAvailable()) this->RefInfo().remove_self();
        this->data().refer(M.data());
        this->structure().refer(M.structure());
        this->info()=M.info();
        this->SetGetMethod();
        M.RefList().append(this->RefInfo());
      }

      void refer(ParentType& rRM, unsigned int off, unsigned int sz) {
        assert(off+sz<=rRM.structure().size());
        if(this->data().IsAvailable()) this->RefInfo().remove_self();
        unsigned int nl=rRM.structure()[0].size();
        this->data().refer(rRM.data(),off*nl,sz*nl);
        this->structure().refer(rRM.structure(),off,sz);
        this->info()=rRM.info();
        if(this->MatrixActualOrder()==COrder) this->info()[NumberRows]=sz;
        else if(this->MatrixActualOrder()==FortranOrder)  this->info()[NumberColumns]=sz;
        else myError("improper order for rectangle matrix");
        this->SetGetMethod();
        rRM.RefInfo().add_before(this->RefInfo());
      }

      void refer(ObjectWStorage<RectMatrixBase<T,VecType> >& M,
                 unsigned int off, unsigned int sz) {
        assert(off+sz<=M.structure().size());
        if(this->data().IsAvailable()) this->RefInfo().remove_self();
        unsigned int nl=M.structure()[0].size();
        this->data().refer(M.data(),off*nl,sz*nl);
        this->structure().refer(M.structure(),off,sz);
        this->info()=M.info();
        if(this->MatrixActualOrder()==COrder) this->info()[NumberRows]=sz;
        else if(this->MatrixActualOrder()==FortranOrder)  this->info()[NumberColumns]=sz;
        else myError("improper order for rectangle matrix");
        this->SetGetMethod();
        M.RefList().append(this->RefInfo());
      }

      virtual const char* type() const { return "reference rectangle matrix"; }

  };

}

#endif

