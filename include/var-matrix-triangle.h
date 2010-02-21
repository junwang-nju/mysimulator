
#ifndef _Variable_Matrix_Triangle_H_
#define _Variable_Matrix_Triangle_H_

#include "object-with-storage.h"
#include "matrix-triangle-base.h"
#include "var-vector.h"

namespace std {

  template <typename T>
  class varTriangMatrix
    : public ObjectWStorage<TriangMatrixBase<T,varVector> > {

    public:
    
      typedef varTriangMatrix<T>  Type;
      
      typedef ObjectWStorage<TriangMatrixBase<T,varVector> >  ParentType;
      
      varTriangMatrix() : ParentType() {}

      varTriangMatrix(const unsigned int Dim, const int Order=COrder,
                      const unsigned Trans=NoTranspose,
                      const unsigned int Tripart=UpperPart,
                      const bool SymFlag=true, const bool DiagFlag=true)
        : ParentType() {
        allocate(Dim,Order,Trans,Tripart,SymFlag,DiagFlag);
      }

      varTriangMatrix(const Type& vTM) {
        myError("Cannot create from variable triangle matrix");
      }

      virtual ~varTriangMatrix() {}

      Type& operator=(const Type& vTM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vTM));
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

      void allocate(const unsigned int Dim, const unsigned int Order=COrder,
                    const unsigned int Trans=NoTranspose,
                    const unsigned int Tripart=UpperPart,
                    const bool SymFlag=true, const bool DiagFlag=true) {
        this->clear();
        this->SetSize(Dim,Dim);
        this->SetOrder(Order);
        this->SetTransposeState(Trans);
        this->SetTrianglePart(Tripart);
        this->SetSymmetryFlag(SymFlag);
        this->SetDiagonalState(DiagFlag);
        this->SetGetMethod();
        if(this->IsDiagonalExisted()) this->SetActualDimension(Dim);
        else                          this->SetActualDimension(Dim-1);
        unsigned int d=this->ActualDimension();
        unsigned int n=(d*(d+1))/2;
        this->data().allocate(n);
        this->structure().allocate(d);
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
      
      virtual const char* type() const { return "variable Triangle Matrix"; }

  };

}

#endif
