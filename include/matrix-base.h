
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
    MatrixType=0,
    ExpectOrder,
    TransposeState,
    ActualOrder,
    NumberRows,
    NumberColumns,
    NumberCommonItems
  };
  enum RectangleInfoItems {
    RectangleNumberItems=NumberCommonItems
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
  template <typename T, template<typename> class VecType>
  class MatrixBase : DataPack<T,VecType,VecType,VecType> {
    public:
      typedef T   DataType;
      typedef MatrixBase<T,VecType>   Type;
      typedef DataPack<T,VecType,VecType,VecType> ParentType;
      typedef T& (*GetElemFuncType)(VecType<refVector<T> >&,
                                    unsigned int,unsigned int,T&);
    protected:
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
      template <typename inputT>
      Type& operator=(const inputT& V) { this->data()=V; return *this; }
      void clear();
      const unsigned int& NumRow() const;
      const unsigned int& NumCol() const;
      const int& MatrixOrder() const;
      const int& MatrixTransposeState() const;
      const int& MatrixActualOrder() const;
      void SetSize(const unsigned int NR, const unsigned int NC);
      void SetOrder(const int Ord);
      void SetTranpose(const int Trans);
      void SetActualOrder(const int AOrd);
      void AssignGetMethod(const GetElemFuncType& iGMethod);
      T& operator()(const unsigned int I, const unsigned int J);
      const T& operator()(const unsigned int I, const unsigned int J) const;
      unsigned MatrixType2NumItems(const int MatType);
  };
}

#endif

