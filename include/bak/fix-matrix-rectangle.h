
#ifndef _Fixed_Matrix_Rectangle_H_
#define _Fixed_Matrix_Rectangle_H_

#include "matrix-rectangle.h"
#include "fix-vector.h"
#include <cassert>

namespace std {

  template <typename T, unsigned int NRow, unsigned int NCol,
                        int Order=COrder, int Trans=NoTranspose,
            unsigned int NLines=
              (Trans==NoTranspose?
                  (Order==COrder?NRow:(Order==FortranOrder?NCol:0U)):
              (Trans==WithTranspose?
                  (Order==COrder?NCol:(Order==FortranOrder?NRow:0U)):0U))>
  class fixMatrixRectangle : public RectMatrix<T,refVector> {

    public:

      typedef fixMatrixRectangle<T,NRow,NCol,Order,Trans,NLines> Type;

      typedef RectMatrix<T,refVector> ParentType;

    protected:

      static const unsigned int NMerInLines;

      fixVector<T,NRow*NCol>  inData;

      fixVector<refVector<T>,NLines>  inStruct;

    public:

      fixMatrixRectangle() : ParentType() {
        assert(NLines>0);
        this->data().refer(inData);
        this->structure().refer(inStruct);
        for(unsigned int i=0,n=0;i<NLines;++i,n+=NMerInLines)
          this->structure()[i].refer(this->data(),n,NMerInLines);
        this->SetSize(NRow,NCol);
        this->SetOrder(Order);
        this->SetTransposeState(Trans);
        this->SetGetMethod();
      }

      fixMatrixRectangle(const Type&) {
        myError("Cannot create from fixed rectangle matrix");
      }

      virtual ~fixMatrixRectangle() {}

      Type& operator=(const Type& fRM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(fRM));
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

      void clear() {}

      virtual const char* type() const { return "Fixed Rectangle Matrix"; }

  };

  template <typename T, unsigned int NRow, unsigned int NCol,
                        int Order, int Trans, unsigned int NLines>
  const unsigned int
  fixMatrixRectangle<T,NRow,NCol,Order,Trans,NLines>::NMerInLines=
      (Trans==NoTranspose?
          (Order==COrder?NCol:(Order==FortranOrder?NRow:0U)):
      (Trans==WithTranspose?
          (Order==COrder?NRow:(Order==FortranOrder?NCol:0U)):0U));

}

#endif

