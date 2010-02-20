
#ifndef _Fixed_Rectangle_Matrix_H_
#define _Fixed_Rectangle_Matrix_H_

#include "matrix-rectangle-base.h"
#include "object-with-storage.h"
#include "fix-vector.h"
#include <cassert>

namespace std {

  template <typename T, unsigned int NRow, unsigned int NCol,
                        int Ord=COrder, int Transp=NoTranspose,
            int DOrd=
              (Transp==NoTranspose?Ord:
              (Transp==WithTranspose?(Ord==COrder?FortranOrder:
                                     (Ord==FortranOrder?COrder:UnknownOrder)):
              UnknownOrder)),
            unsigned int NLines=
              (Transp==NoTranspose?
                    (Ord==COrder?NRow:(Ord==FortranOrder?NCol:0U)):
              (Transp==WithTranspose?
                    (Ord==COrder?NCol:(Ord==FortranOrder?NRow:0U)):0U)),
            unsigned int NMerInLine=
              (Transp==NoTranspose?
                    (Ord==COrder?NCol:(Ord==FortranOrder?NRow:0U)):
              (Transp==WithTranspose?
                    (Ord==COrder?NRow:(Ord==FortranOrder?NCol:0U)):0U))>
  class fixRectMatrix : public ObjectWStorage<RectMatrixBase<T,refVector> > {

    public:

      typedef fixRectMatrix<T,NRow,NCol,Ord,Transp> Type;

      typedef ObjectWStorage<RectMatrixBase<T,refVector> >  ParentType;

    protected:

      fixVector<T,NRow*NCol>  inData;

      fixVector<refVector<T>,NLines>  inStruct;

    public:

      fixRectMatrix() : ParentType() {
        assert(NLines>0);
        this->data().refer(inData);
        this->structure().refer(inStruct);
        for(unsigned int i=0,n=0;i<NLines;++i,n+=NMerInLine)
          this->structure()[i].refer(this->data(),n,NMerInLine);
        this->SetSize(NRow,NCol);
        this->SetOrder(Ord);
        this->SetTransposeState(Transp);
        this->SetGetMethod();
      }

      fixRectMatrix(const Type& fRM) {
        myError("Cannot create from fixed rectangle matrix");
      }

      virtual ~fixRectMatrix() {}

      Type& operator=(const Type& fRM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fRM));
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

      void clear() {}

      virtual const char* type() const { return "fixed rectangle matrix"; }

  };

}

#endif

