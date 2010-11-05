
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
    typedef T& (*GetFuncType)(Vector<T>*,const int,const int,T&);
    
    Vector<unsigned int> property;
    T* ptrOther;
    GetFuncType GetFunc;
    
    Matrix() : ParentType(), property(), ptrOther(NULL), GetFunc(NULL) {}
    Matrix(const Type& M) { myError("cannot create from Matrix"); }
    Type& operator=(const Type& M) {
      myError("cannot copy Matrix");
      return* this;
    }
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
    release(M.property);
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
    M.ptrOther=const_cast<T*>(rM.ptrOther);
    M.GetFunc=rM.GetFunc;
    refer(static_cast<PropertyList<T>&>(M),
          static_cast<const PropertyList<T>&>(rM));
  }

  template <typename T>
  void swap(Matrix<T>& MA, Matrix<T>& MB) {
    swap(MA.property,MB.property);
    swap(MA.ptrOther,MB.ptrOther);
    swap(MA.GetFunc,MB.GetFunc);
    swap(static_cast<PropertyList<T>&>(MA),static_cast<PropertyList<T>&>(MB));
  }

  template <typename T>
  ostream& operator<<(ostream& os, const Matrix<T>& M) {
    os<<M(0,0);
    for(unsigned int j=1;j<M.property[MatrixNumberColumn];++j) os<<"\t"<<M(0,j);
    for(unsigned int i=1;i<M.property[MatrixNumberRow];++i) {
      os<<endl<<M(i,0);
      for(unsigned int j=1;j<M.property[MatrixNumberColumn];++j)
        os<<"\t"<<M(i,j);
    }
    return os;
  }

}

#include "matrix-rectangle-name.h"
#include "matrix-triangle-name.h"

namespace std {

  template <typename T>
  void copy(Matrix<T>& M, const Matrix<T>& cM,
            const int nr=iZero, const int nc=iZero,
            const int croff=iZero, const int crstep=iOne,
            const int ccoff=iZero, const int ccstep=iOne,
            const int roff=iZero, const int rstep=iOne,
            const int coff=iZero, const int cstep=iOne) {
    assert(IsAvailable(cM));
    assert(IsAvailable(M));
    assert((M.property[MatrixType]!=TriangleMatrix)||
           ((cM.property[MatrixType]!=RectangleMatrix)&&
            (cM.property[MatrixDiagonalExistFlag]
              ==M.property[MatrixDiagonalExistFlag])&&
            (cM.property[MatrixSymmetryFlag]==M.property[MatrixSymmetryFlag])&&
            ((M.property[MatrixSymmetryFlag]==SymmetryMatrix)||
             (M.property[MatrixActualTrianglePart]
              ==cM.property[MatrixActualTrianglePart]))));
    int rnr=nr,rnc=nc;
    if(nr==0)
      rnr=(M.property[MatrixNumberRow]<cM.property[MatrixNumberRow]?
           M.property[MatrixNumberRow]:cM.property[MatrixNumberRow]);
    if(nc==0)
      rnc=(M.property[MatrixNumberColumn]<cM.property[MatrixNumberColumn]?
           M.property[MatrixNumberColumn]:cM.property[MatrixNumberColumn]);
    for(int i=0,cr=croff,r=roff;i<rnr;++i,cr+=crstep,r+=rstep)
    for(int j=0,cc=ccoff,c=coff;j<rnc;++j,cc+=ccstep,c+=cstep)
      M(r,c)=cM(cr,cc);
  }

}

#include "matrix-rectangle-allocator.h"
#include "matrix-triangle-allocator.h"

namespace std {

  template <typename T>
  void allocate(Matrix<T>& M, const unsigned int MType, ...) {
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
