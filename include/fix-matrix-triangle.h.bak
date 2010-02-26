
#ifndef _Fixed_Matrix_Triangle_H_
#define _Fixed_Matrix_Triangle_H_

#include "matrix-triangle-base.h"
#include "fix-vector.h"
#include "ref-vector.h"

namespace std {

  template <typename T, unsigned int Dim, unsigned int DiagFlag=WithDiagonal,
            unsigned int ADim=(DiagFlag==WithDiagonal?Dim:
                              (DiagFlag==NullDiagonal?Dim-1:0))>
  class fixTriangMatrix
    : public ObjectWStorage<TriangMatrixBase<T,refVector> > {

    public:

      typedef fixTriangMatrix<T,Dim,DiagFlag,ADim>  Type;

      typedef ObjectWStorage<TriangMatrixBase<T,refVector> >  ParentType;

    protected:

      fixVector<T,(ADim*(ADim+1))/2>  inData;

      fixVector<refVector<T>,ADim>    inStruct;

    public:

      fixTriangMatrix() : ParentType() {
        assert(ADim>0);
        this->data().refer(inData);
        this->structure().refer(inStruct);
        this->SetSize(Dim,Dim);
        this->SetDiagonalState(DiagFlag);
        this->SetActualDimension(ADim);
      }

      fixTriangMatrix(const Type& fTM) {
        myError("Cannot create from fixed triangle matrix");
      }

      virtual ~fixTriangMatrix() {}

      Type& operator=(const Type& fTM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fTM));
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(TriangMatrixBase<T,iVecType>& TM) {
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

      void SetStructure(const unsigned int Order=COrder,
                        const unsigned int Trans=NoTranspose,
                        const unsigned int Tripart=UpperPart,
                        const bool SymFlag=true) {
        this->SetOrder(Order);
        this->SetTransposeState(Trans);
        this->SetTrianglePart(Tripart);
        this->SetSymmetryFlag(SymFlag);
        this->SetGetMethod();
        unsigned int n,d;
        if(this->MatrixActualOrder()==COrder) {
          if(this->MatrixActualTrianglePart()==UpperPart) {
            n=this->ActualDimension();
            d=-1;
          } else if(this->MatrixActualTrianglePart()==LowerPart) {
            n=1;
            d=1;
          }
        } else if(this->MatrixActualOrder()==FortranOrder) {
          if(this->MatrixActualTrianglePart()==UpperPart) {
            n=1;
            d=1;
          }
          else if(this->MatrixActualTrianglePart()==LowerPart) {
            n=this->ActualDimension();
            d=-1;
          }
        } else if(this->MatrixActualOrder()==DiagonalOrder) {
          n=this->ActualDimension();
          d=-1;
        } else myError("improper order for triangle matrix");
        for(unsigned int i=0,m=0;i<this->ActualDimension();++i,m+=n,n+=d)
          this->structure()[i].refer(this->data(),m,n);
      }

      void clear() {}

      virtual const char* type() const { return "fixed triangle matrix"; }

  };

}

#endif

