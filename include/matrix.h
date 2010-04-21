
#ifndef _Matrix_H_
#define _Matrix_H_

#include "vector.h"
#include <cstdarg>

namespace std {

  enum MatrixBasePropertyName {
    MatrixType=0,
    MatrixNumberElement,
    MatrixNumberRow,
    MatrixNumberColumn,
    MatrixDataState,
    MatrixDataOrder,
    MatrixTransposeForm,
    MatrixActualOrder,
    MatrixCommonNumberProperty,
  };

  enum MatrixTypeName {
    RectangleMatrix=0,
    TriangleMatrix
  };

  enum MatrixDataOrderName {
    COrder=0,
    FortranOrder,
    DiagonalOrder
  };

  enum MatrixTransposeFormName {
    NoTranspose=0,
    Transposed
  };

  template <typename T>
  struct Matrix {

    typedef Matrix<T> Type;
    typedef T& (*GetFuncType)(T**,const unsigned int,const unsigned int,T&);

    T* data;
    T** structure;
    unsigned int *property;
    T* PtrOtherElement;
    GetFuncType GetFunc;
    unsigned int state;

    Matrix()
      : data(NULL), structure(NULL), property(NULL), PtrOtherElement(NULL),
        GetFunc(NULL), state(Unused) {}
    Matrix(const Type& MB) { myError("Cannot create Matrix"); }
    Type& operator=(const Type& M) {
    assert(IsAvailable(*this));
    assert(IsAvailable(M));
      unsigned int m=
          (property[MatrixNumberRow]<M.property[MatrixNumberRow]?
           property[MatrixNumberRow]:M.property[MatrixNumberRow]);
      unsigned int n=
          (property[MatrixNumberColumn]<M.property[MatrixNumberColumn]?
           property[MatrixNumberColumn]:M.property[MatrixNumberColumn]);
      assign(*this,M,m,n);
      return *this;
    }
    ~Matrix() { release(*this); }

    T& operator()(const unsigned int I, const unsigned int J) {
      return GetFunc(structure,I,J,*PtrOtherElement);
    }
    const T& operator()(const unsigned int I, const unsigned int J) const {
      return GetFunc(const_cast<T**>(structure),I,J,
                     const_cast<T&>(*PtrOtherElement));
    }

  };

  template <typename T>
  bool IsAvailable(const Matrix<T>& M) { return IsAvailable(M.data); }

  template <typename T>
  void release(Matrix<T>& M) {
    if(M.state==Allocated) {
      safe_delete_array(M.data);
      safe_delete_array(M.structure);
      safe_delete_array(M.property);
      safe_delete(M.PtrOtherElement);
    } else {
      M.data=NULL;
      M.structure=NULL;
      M.property=NULL;
      M.PtrOtherElement=NULL;
    }
    M.GetFunc=NULL;
    M.state=Unused;
  }

  template <typename T>
  void refer(Matrix<T>& destM, const Matrix<T>& srcM) {
    assert(IsAvailable(srcM));
    release(destM);
    destM.data=const_cast<T*>(srcM.data);
    destM.structure=const_cast<T**>(srcM.structure);
    destM.property=const_cast<unsigned int*>(srcM.property);
    destM.PtrOtherElement=const_cast<T*>(srcM.PtrOtherElement);
    destM.GetFunc=srcM.GetFunc;
    destM.state=Reference;
  }

  template <typename T>
  ostream& operator<<(ostream& os, const Matrix<T>& M) {
    os<<M(0,0);
    for(unsigned int j=1;j<M.property[MatrixNumberColumn];++j)
      os<<"\t"<<M(0,j);
    for(unsigned int i=1;i<M.property[MatrixNumberRow];++i) {
      os<<endl<<M(i,0);
      for(unsigned int j=1;j<M.property[MatrixNumberColumn];++j)
        os<<"\t"<<M(i,j);
    }
    return os;
  }

  template <typename T>
  void allocate(Matrix<T>& M, const unsigned int MatrixType, ...) {
    release(M);
    va_list vl;
    va_start(vl,MatrixType);
    if(MatrixType==RectangleMatrix) {
      unsigned int nRow=va_arg(vl,unsigned int);
      unsigned int nCol=va_arg(vl,unsigned int);
      unsigned int DataOrder=va_arg(vl,unsigned int);
      unsigned int TransForm=va_arg(vl,unsigned int);
      allocateRectangleMatrix(M,nRow,nCol,DataOrder,TransForm);
    }
    else if(MatrixType==TriangleMatrix) {
      unsigned int Dim=va_arg(vl,unsigned int);
      unsigned int DataOrder=va_arg(vl,unsigned int);
      unsigned int TransForm=va_arg(vl,unsigned int);
      unsigned int TPart=va_arg(vl,unsigned int);
      bool SFlag=static_cast<bool>(va_arg(vl,int));
      bool DFlag=static_cast<bool>(va_arg(vl,int));
      allocateTriangleMatrix(M,Dim,DataOrder,TransForm,TPart,SFlag,DFlag);
    }
    else myError("Unknown or Unimplemented Matrix Type");
    va_end(vl);
  }

  template <typename T>
  void swap(Matrix<T>& Ma, Matrix<T>& Mb) {
    swap(Ma.data,Mb.data);
    swap(Ma.structure,Mb.structure);
    swap(Ma.property,Mb.property);
    swap(Ma.PtrOtherElement,Mb.PtrOtherElement);
    swap(Ma.GetFunc,Mb.GetFunc);
    swap(Ma.state,Mb.state);
  }

  void SetMatrixActualOrder(unsigned int* property) {
    if(property[MatrixTransposeForm]==NoTranspose)
      property[MatrixActualOrder]=property[MatrixDataOrder];
    else if(property[MatrixTransposeForm]==Transposed) {
      if(property[MatrixDataOrder]==COrder)
        property[MatrixActualOrder]=FortranOrder;
      else if(property[MatrixDataOrder]==FortranOrder)
        property[MatrixActualOrder]=COrder;
      else if(property[MatrixDataOrder]==DiagonalOrder)
        property[MatrixActualOrder]=DiagonalOrder;
      else myError("Unknown Data Order of Matrix");
    } else myError("Unknown Transpose Format of Matrix");
  }

}

#include "matrix-rectangle-allocator.h"
#include "matrix-triangle-allocator.h"

namespace std {

  template <typename T>
  void assign(Matrix<T>& destM, const Matrix<T>& srcM,
              const unsigned int nrow, const unsigned int ncol,
              const unsigned int sroff=uZero, const unsigned int srstep=uOne,
              const unsigned int scoff=uZero, const unsigned int scstep=uOne,
              const unsigned int droff=uZero, const unsigned int drstep=uOne,
              const unsigned int dcoff=uZero, const unsigned int dcstep=uOne) {
    assert(IsAvailable(destM));
    assert(IsAvailable(srcM));
    if(destM.property[MatrixType]==TriangleMatrix) {
      assert(srcM.property[MatrixType]!=RectangleMatrix);
      assert(srcM.property[MatrixDiagonalExistFlag]==
             destM.property[MatrixDiagonalExistFlag]);
      assert(srcM.property[MatrixSymmetryFlag]==
             destM.property[MatrixSymmetryFlag]);
      if(destM.property[MatrixSymmetryFlag]==ASymmetryMatrix)
        assert(srcM.property[MatrixActualTrianglePart]==
               destM.property[MatrixActualTrianglePart]);
    }
    for(unsigned int i=0,sr=sroff,dr=droff;i<nrow;++i,sr+=srstep,dr+=drstep)
    for(unsigned int j=0,sc=scoff,dc=dcoff;j<ncol;++j,sc+=scstep,dc+=dcstep)
      destM(dr,dc)=srcM(sr,sc);
  }

}

#endif
