
#ifndef _Variable_Matrix_Triangle_H_
#define _Variable_Matrix_Triangle_H_

#include "matrix-triangle-base.h"
#include "var-vector.h"

namespace std {

  template <typename T>
  class varMatrixTriangle : public TriangMatrixBase<T,varVector> {

    public:

      typedef varMatrixTriangle<T>  Type;

      typedef TriangMatrixBase<T,varVector> ParentType;

      varMatrixTriangle() : ParentType() {}

      varMatrixTriangle(const unsigned int Dim, const int Order=COrder,
                        const int Trans=NoTranspose,
                        const int Tripart=UpperPart,
                        const bool SymFlag=true, const bool DiagFlag=true)
        : ParentType() { allocate(Dim,Order,Trans,Tripart,SymFlag,DiagFlag); }

      varMatrixTriangle(const Type&) {
        myError("Cannot create from Variable Tirangle Matrix");
      }

      virtual ~varMatrixTriangle() {}

      Type& operator=(const Type& vTM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vTM));
        return *this;
      }

      template <template <typename> class VecType>
      Type& operator=(const TriangMatrixBase<T,VecType>& TM) {
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

      void allocate(const unsigned int Dim, const int Order=COrder,
                    const int Trans=NoTranspose, const int Tripart=UpperPart,
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
        int d=this->ActualDimension();
        int n=(d*(d+1))/2;
        this->data().allocate(n);
        this->structure().allocate(d);
        this->SetStructure();
      }

      virtual const char* type() const { return "Variable Triangle Matrix"; }

  };

}

#endif

