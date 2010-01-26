
#ifndef _Matrix_Base_H_
#define _Matrix_Base_H_

#include "var-vector.h"
#include "ref-vector.h"

namespace std {
  enum MatrixFlag {
    UnknownOrder=-1,
    COrder,
    FortranOrder,
    DiagonalOrder,
    UnknownTranspose=-1,
    Original,
    Transposed
  };
  template <typename T>
  class MatrixBase {
    protected:
      varVector<T>  Data;
      varVector<refVector<T> >  Lines;
      int Order;
      int Transpose;
      int DataOrder;
      unsigned int NRow;
      unsigned int NCol;
    public:
      typedef T DataType;
      typedef MatrixBase<T>   Type;
      typedef T& (*GetUnitType)(varVector<refVector<T> >&,
                                unsigned int,unsigned int);
    protected:
      GetUnitType getUnit;
    public:
      MatrixBase() : Data(), Lines(), Order(UnknownOrder),
                     Transpose(UnknownTranspose), DataOrder(UnknownOrder),
                     NRow(uZero), NCol(uZero), getUnit(NULL) {}
      MatrixBase(const Type& MB) {
        myError("Cannot create from MatrixBase");
      }
      virtual ~MatrixBase() {
        getUnit=NULL;
        NCol=NRow=uZero;
        DataOrder=UnknownOrder;
        Transpose=UnknownTranspose;
        Order=UnknownOrder;
      }
      Type& operator=(const Type& MB) {
        unsigned int m=(NRow<MB.NRow?NRow:MB.NRow);
        unsigned int n=(NCol<MB.NCol?NCol:MB.NCol);
        for(unsigned int i=0;i<m;++i)
        for(unsigned int j=0;j<n;++j)
          operator()(i,j)=MB(i,j);
        return *this;
      }
      template <typename inputT>
      Type& operator=(const inputT& V) {
        Data=V;
        return *this;
      }
      void clear();
      varVector<T>& data();
      const varVector<T>& data() const;
      const unsigned int& NumberRow() const;
      const unsigned int& NumberColumn() const;
      const int& MatrixOrder() const;
      const int& MatrixTransposeStatus() const;
      const int& MatrixDataOrder() const;
      void SetSize(const unsigned int NR, const unsigned int NC);
      void SetMatrixOrder(const int MOrd);
      void SetMatrixTransposeStatus(const int MTrans);
      void SetDataOrder(const int DOrd);
      void AssignGetMethod(const GetUnitType& iGetUnit);
      T& operator()(unsigned int I, unsigned int J);
      const T& operator()(unsigned int I, unsigned int J) const;
      virtual const char* type() const = 0;
  };
}

#endif

