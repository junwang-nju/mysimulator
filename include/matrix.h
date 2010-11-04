
#ifndef _Matrix_H_
#define _Matrix_H_

#include "matrix-name.h"
#include "property-list.h"
#include <cstdarg>

namespace std {

  template <typename T>
  struct Matrix : public PropertyList<T> {
    typedef Matrix<T> Type;
    typedef PropertyList<T> ParentType;
    typedef T& (*GetFuncType)(T**,const int,const int,T&);
    
    Vector<unsigned int> property;
    T* ptrOther;
    GetFuncType GetFunc;
    
    Matrix() : ParentType(), property(), ptrOther(NULL), GetFunc(NULL) {}
    Matrix(const Type& M) { myError("cannot create from Matrix"); }
    Type& operator=(const Type& M) { myError("cannot copy Matrix"); }
    ~Matrix() { release(*this); }

    T& operator()(const int I, const int J) {
      return GetFunc(this->structure,I,J,*ptrOther);
    }
    const  T& operator()(const int I, const int J) const {
      return GetFunc(this->structure,I,J,*ptrOther);
    }

    void SetActualOrder() {
      if(property[MatrixTransposeForm]==NoTranspose)
        property[MatrixActualOrder]=property[MatrixDataOrder];
      else if(property[MatrixTransposeForm]==Transposed) {
        if(property[MatrixDataOrder]==COrder)
          property[MatrixActualOrder]=FortranOrder;
        else if(property[MatrixDataOrder]==FortranOrder)
          property[MatrixActualOrder]=COrder;
        else if(property[MatrixDataOrder]==DiagonalOrder)
          property[MatrixActualOrder]=DiagonalOrder;
        else myError("Unknown Data Order");
      } else myError("Unknown Transpose Format");
    }

  };

  template <typename T>
  bool IsAvailable(const Matrix<T>& M) { return IsAvailable(M.property); }
  
  template <typename T>
  void release(Matrix<T>& M) {
    release(property);
    if(M.state==Allocated) safe_delete(M.ptrOther);
    else M.ptrOther=NULL;
    M.GetFunc=NULL;
    release(static_cast<PropertyList<T>&>(M));
  }

  template <typename T>
  void refer(Matrix<T>& M, const Matrix<T>& rM) {
    assert(IsAvailable(rM));
    release(M);
    refer(M.property,rM.property);
    M.ptrOther=const_cast<T*>(ptrOther);
    M.GetFunc=rM.GetFunc;
    refer(static_cast<PropertyList<T>&>(M),
          static_cast<const PropertyList<T>&>(M));
  }

  template <typename T>
  void swap(Matrix<T>& MA, Matrix<T>& MB) {
    swap(MA.property,MB,property);
    swap(MA.ptrOther,MB.ptrOther);
    swap(MA.GetFunc,MB.GetFunc);
    swap(static_cast<PropertyList<T>&>(MA),static_cast<PropertyList<T>&>(MB));
  }

  template <typename T>
  ostream& operator<<(ostream& os, const Matrix<T>& M) {
    os<<M(0,0);
    for(int j=1;j<M.property[MatrixNumberColumn];++j) os<<"\t"<<M(0,j);
    for(int i=1;i<M.property[MatrixNumberRow];++i) {
      os<<endl<<M(i,0);
      for(unsigned int j=1;j<M.property[MatrixNumberColumn];++j)
        os<<"\t"<<M(0,j);
    }
    return os;
  }

  template <typename T>
  void allocate(Matrix<T>, const unsigned int MType, ...) {
    release(M);
    va_list vl;
    va_start(vl,MType);
    if(MType==RectangleMatrix) {
      unsigned int nRow=va_arg(vl,unsigned int);
      unsigned int nColumn=va_arg(vl,unsigned int);
      unsigned int DataOrder=va_arg(vl,unsigned int);
      unsigned int TransForm=va_arg(vl,unsigned int);
      allocateRectangleMatrix(M,nRow,nColumn,DataOrder,TransForm);
    } else if(MType==TriangleMatrix) {
      unsigned int Dim=va_arg(vl,unsigned int);
      unsigned int DataOrder=va_arg(vl,unsigned int);
      unsigned int TransForm=va_arg(vl,unsigned int);
      unsigned int TPart=va_arg(vl,unsigned int);
      bool SFlag=static_cast<bool>(va_arg(vl,int));
      bool DFlag=static_cast<bool>(va_arg(vl,int));
      allocateTriangleMatrix(M,Dim,DataOrder,TransForm,TPart,SFlag,DFlag);
    } else myError("Unknown Matrix Type");
    va_end(vl);
  }

}

#endif
