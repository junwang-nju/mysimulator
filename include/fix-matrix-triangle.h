
#ifndef _Fixed_Matrix_Triangle_H_
#define _Fixed_Matrix_Triangle_H_

#include "matrix-triangle-base.h"
#include "fix-vector.h"

namespace std {

  template <typename T, unsigned int Dim, unsigned int DiagFlag=WithDiagonal,
            unsigned int ADim=(DiagFlag==WithDiagonal?Dim:
                              (DiagFlag==NullDiagonal?Dim-1:0U))>
  class fixMatrixTriangle : public TriangMatrixBase<T,refVector> {

    public:

      typedef fixMatrixTriangle<T,Dim,DiagFlag,ADim>  Type;

      typedef TriangMatrixBase<T,refVector> ParentType;

    protected:

      fixVector<T,(ADim*(ADim+1))/2>  inData;

      fixVector<refVector<T>,ADim>    inStruct;

      void initStatic() {
        this->SetSize(Dim,Dim);
        this->SetDiagonalState(DiagFlag);
        this->SetActualDimension(ADim);
        this->data().refer(inData);
        this->structure().refer(inStruct);
      }

    public:

      fixMatrixTriangle() : ParentType() {
        assert(ADim>0);
        initStatic();
      }

      fixMatrixTriangle(const Type&) {
        myError("Cannot create from fixed triangle matrix");
      }

      virtual ~fixMatrixTriangle() {}

      Type& operator=(const Type& fTM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fTM));
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

      void clear() {
        static_cast<ParentType*>(this)->clear();
        for(unsigned int i=0;i<ADim;++i)  inStruct[i].clear();
        initStatic();
      }

      virtual const char* type() const { return "fixed triangle matrix"; }

      void initAs(const int Order=COrder, const int Trans=NoTranspose,
                  const int Tripart=UpperPart, const bool SymFlag=true) {
        this->SetOrder(Order);
        this->SetTransposeState(Trans);
        this->SetTrianglePart(Tripart);
        this->SetSymmetryFlag(SymFlag);
        this->SetGetMethod();
        this->SetStructure();
      }

  };

}

#endif

