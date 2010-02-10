
#ifndef _Matrix_Base_H_
#define _Matrix_Base_H_

#include "data-pack.h"

namespace std {
  enum MatrixFormat {
    UnknownFormat=-1,
    Rectangle,
    Square,
    Triangle,
    Band,
    TriangleBand,
    NumberMatrixFormat
  };
  enum MatrixDataOrder {
    UnknownOrder=-1,
    COrder,
    FortranOrder,
    DiagonalOrder,
    NumberMatrixDataOrder
  };
  enum MatrixTransposeType {
    UnknowTranspose=-1,
    NoTranspose,
    WithTranspose
  };
  enum CommonInfoItems {
    ExpectOrder=0,
    TransposeState,
    ActualOrder,
    NumberRows,
    NumberColumns,
    NumberCommonItems
  };
  enum SquareInfoItems {
    SquareDimension=NumberCommonItems,
    SquareNumberItems
  };
  enum TriangleInfoItems {
    TriangleDimension=NumberCommonItems,
    SymmetryFlag,
    TrianglePart,
    TriangleNumberItems
  };
  template <typename T, unsigned int MType, template<typename> class VecType>
  class MatrixBase : DataPack<T,VecType,VecType,VecType> {
    public:
      typedef T   DataType;
      typedef MatrixBase<T,MType,VecType>   Type;
      typedef DataPack<T,VecType,VecType,VecType> ParentType;
      typedef T& (*GetElemFuncType)(VecType<refVector<T> >&,
                                    unsigned int,unsigned int,T&);
    protected:
      static const unsigned int MatType;
      T OtherElems;
      GetElemFuncType getElem;
    public:
      MatrixBase() : ParentType(), OtherElems(), getElem(NULL) {}
      MatrixBase(const Type& MB) {
        myError("Cannot create from Matrix base");
      }
      virtual ~MatrixBase() {
        getElem=NULL;
        this->info()[NumberColumns]=uZero;
        this->info()[NumberRows]=uZero;
        this->info()[ActualOrder]=UnknownOrder;
        this->info()[TransposeState]=UnknowTranspose;
        this->info()[ExpectOrder]=UnknownOrder;
      }
      Type& operator=(const Type& MB) {
        unsigned int m=(NumRow()<MB.NumRow()?NumRow():MB.NumRow());
        unsigned int n=(NumCol()<MB.NumCol()?NumCol():MB.NumCol());
        for(unsigned int i=0;i<m;++i)
        for(unsigned int j=0;j<n;++j) operator()(i,j)=MB(i,j);
        return *this;
      }
      Type& operator=(const VectorBase<T>& V) { this->data()=V; return *this; }
      Type& operator=(const T& D) { this->data()=D; return *this; }
      void clear() {
        getElem=NULL;
        this->info()[NumberColumns]=uZero;
        this->info()[NumberRows]=uZero;
        this->info()[ActualOrder]=UnknownOrder;
        this->info()[TransposeState]=UnknowTranspose;
        this->info()[ExpectOrder]=UnknownOrder;
        static_cast<ParentType*>(this)->clear();
      }
      const unsigned int& NumRow() const { return this->info()[NumberRows]; }
      const unsigned int& NumCol() const {
        return this->info()[NumberColumns];
      }
      const int& MatrixOrder() const { return this->info()[ExpectOrder]; }
      const int& MatrixTransposeState() const {
        return this->info()[TransposeState];
      }
      const int& MatrixActualOrder() const {
        return this->info()[ActualOrder];
      }
      void SetSize(const unsigned int NR, const unsigned int NC) {
        this->info()[NumberRows]=NR;
        this->info()[NumberColumns]=NC;
      }
      void SetOrder(const int Ord) { this->info()[ExpectOrder]=Ord; }
      void SetTranpose(const int Trans) { this->info()[TransposeState]=Trans; }
      void SetActualOrder(const int AOrd) { this->info()[ActualOrder]=AOrd; }
      void AssignGetMethod(const GetElemFuncType& iGMethod) {
        getElem=iGMethod;
      }
      T& operator()(const unsigned int I, const unsigned int J) {
        return getElem(this->structure(),I,J,OtherElems);
      }
      const T& operator()(const unsigned int I, const unsigned int J) const {
        return getElem(this->structure(),I,J,OtherElems);
      }
  };
  template <typename T, unsigned int MType, template<typename> class VecType>
  const unsigned int MatrixBase<T,MType,VecType>::MatType=MType;
}

#endif

