
#ifndef _Matrix_Triangle_Allocator_H_
#define _Matrix_Triangle_Allocator_H_

#include "matrix.h"

namespace std {

  enum MatrixTrianglePropertyName {
    MatrixDimension=MatrixCommonNumberProperty,
    MatrixSymmetryFlag,
    MatrixTrianglePart,
    MatrixDiagonalExistFlag,
    MatrixActualDimension,
    MatrixActualTrianglePart,
    MatrixActualDataPattern,
    MatrixLineSizeFirst,
    MatrixLineSizeShift,
    MatrixTriangleNumberProperty
  };

  enum MatrixSymmetryFlagName {
    SymmetryMatrix=0,
    ASymmetryMatrix
  };

  enum MatrixDiaginalExistFlagName {
    HaveDiagonal=0,
    NullDiagonal
  };

  enum MatrixTrianglePartName {
    UpperTriangle=0,
    LowerTriangle
  };

  enum MatrixTriangleDataPatternName {
    DiagonalType=0,
    COrderUpperType,
    FortranOrderUpperType
  };

  template <typename T, unsigned int SFlag, unsigned int DFlag>
  T& GetData4CU(T** str, const unsigned int I,const unsigned int J, T& OE) {
    if((I==J)&&(DFlag==NullDiagonal)) return OE;
    unsigned int rI=I, rJ=J;
    if(rI>rJ) {
      if(SFlag==ASymmetryMatrix)  return OE;
      rI=J; rJ=I; 
    }
    return str[rI][rJ-rI-(DFlag==NullDiagonal?1:0)];
  }

  template <typename T, unsigned int SFlag, unsigned int DFlag>
  T& GetData4CL(T** str, const unsigned int I,const unsigned J, T& OE) {
    if((I==J)&&(DFlag==NullDiagonal)) return OE;
    unsigned int rI=I, rJ=J;
    if(rI<rJ) {
      if(SFlag==ASymmetryMatrix)  return OE;
      rI=J; rJ=I; 
    }
    return str[rI-(DFlag==NullDiagonal?1:0)][rJ];
  }

  template <typename T, unsigned int SFlag, unsigned int DFlag>
  T& GetData4FU(T** str, const unsigned int I,const unsigned J, T& OE) {
    if((I==J)&&(DFlag==NullDiagonal)) return OE;
    unsigned int rI=I, rJ=J;
    if(rI>rJ) {
      if(SFlag==ASymmetryMatrix)  return OE;
      rI=J; rJ=I; 
    }
    return str[rJ-(DFlag==NullDiagonal?1:0)][rI];
  }

  template <typename T, unsigned int SFlag, unsigned int DFlag>
  T& GetData4FL(T** str, const unsigned int I,const unsigned J, T& OE) {
    if((I==J)&&(DFlag==NullDiagonal)) return OE;
    unsigned int rI=I, rJ=J;
    if(rI<rJ) {
      if(SFlag==ASymmetryMatrix)  return OE;
      rI=J; rJ=I; 
    }
    return str[rJ][rI-rJ-(DFlag==NullDiagonal?1:0)];
  }

  template <typename T, unsigned int SFlag, unsigned int DFlag>
  T& GetData4DU(T** str, const unsigned int I,const unsigned J, T& OE) {
    if((I==J)&&(DFlag==NullDiagonal)) return OE;
    unsigned int rI=I, rJ=J;
    if(rI>rJ) {
      if(SFlag==ASymmetryMatrix)  return OE;
      rI=J; rJ=I; 
    }
    return str[rJ-rI-(DFlag==NullDiagonal?1:0)][rI];
  }

  template <typename T, unsigned int SFlag, unsigned int DFlag>
  T& GetData4DL(T** str, const unsigned int I,const unsigned J, T& OE) {
    if((I==J)&&(DFlag==NullDiagonal)) return OE;
    unsigned int rI=I, rJ=J;
    if(rI<rJ) {
      if(SFlag==ASymmetryMatrix)  return OE;
      rI=J; rJ=I; 
    }
    return str[rI-rJ-(DFlag==NullDiagonal?1:0)][rJ];
  }

  template <typename T>
  void allocateTriangleMatrix(
    Matrix<T>& M, const unsigned int Dim, const unsigned int DataOrder,
                  const unsigned int TransposeForm,
                  const unsigned int TrianglePart,
                  const bool SymmetryFlag, const bool DiagonalFlag) {
    M.property=new unsigned int[MatrixTriangleNumberProperty];
    M.property[MatrixType]=TriangleMatrix;
    M.property[MatrixNumberRow]=M.property[MatrixNumberColumn]=Dim;
    M.property[MatrixDimension]=Dim;
    M.property[MatrixDataOrder]=DataOrder;
    M.property[MatrixTransposeForm]=TransposeForm;
    M.property[MatrixTrianglePart]=TrianglePart;
    M.property[MatrixSymmetryFlag]=(SymmetryFlag?SymmetryMatrix:ASymmetryMatrix);
    M.property[MatrixDiagonalExistFlag]=
        (DiagonalFlag?HaveDiagonal:NullDiagonal);
    SetMatrixActualOrder(M.property);
    if(M.property[MatrixTransposeForm]==NoTranspose)
      M.property[MatrixActualTrianglePart]=M.property[MatrixTrianglePart];
    else if(M.property[MatrixTransposeForm]==Transposed) {
      if(M.property[MatrixTrianglePart]==UpperTriangle)
        M.property[MatrixActualTrianglePart]=LowerTriangle;
      else if(M.property[MatrixTrianglePart]==LowerTriangle)
        M.property[MatrixActualTrianglePart]=UpperTriangle;
      else myError("Unknown Type of Triangle Part for Matrix");
    } else myError("Unknown Transpose Form for Matrix");
    if(M.property[MatrixActualOrder]==COrder) {
      if(M.property[MatrixActualTrianglePart]==UpperTriangle) {
        M.property[MatrixActualDataPattern]=COrderUpperType;
        M.GetFunc=(SymmetryFlag?
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4CU<T,SymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4CU<T,SymmetryMatrix,NullDiagonal>)):
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4CU<T,ASymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4CU<T,ASymmetryMatrix,NullDiagonal>)));
      } else if(M.property[MatrixActualTrianglePart]==LowerTriangle) {
        M.property[MatrixActualDataPattern]=FortranOrderUpperType;
        M.GetFunc=(SymmetryFlag?
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4CL<T,SymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4CL<T,SymmetryMatrix,NullDiagonal>)):
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4CL<T,ASymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4CL<T,ASymmetryMatrix,NullDiagonal>)));
      } else myError("Unknown Triangle part for Matrix");
    } else if(M.property[MatrixActualOrder]==FortranOrder) {
      if(M.property[MatrixActualTrianglePart]==UpperTriangle) {
        M.property[MatrixActualDataPattern]=FortranOrderUpperType;
        M.GetFunc=(SymmetryFlag?
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4FU<T,SymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4FU<T,SymmetryMatrix,NullDiagonal>)):
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4FU<T,ASymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4FU<T,ASymmetryMatrix,NullDiagonal>)));
      } else if(M.property[MatrixActualTrianglePart]==LowerTriangle) {
        M.property[MatrixActualDataPattern]=COrderUpperType;
        M.GetFunc=(SymmetryFlag?
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4FL<T,SymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4FL<T,SymmetryMatrix,NullDiagonal>)):
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4FL<T,ASymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4FL<T,ASymmetryMatrix,NullDiagonal>)));
      } else myError("Unknown Triangle part for Matrix");
    } else if(M.property[MatrixActualOrder]==DiagonalOrder) {
      M.property[MatrixActualDataPattern]=DiagonalType;
      if(M.property[MatrixActualTrianglePart]==UpperTriangle)
        M.GetFunc=(SymmetryFlag?
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4DU<T,SymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4DU<T,SymmetryMatrix,NullDiagonal>)):
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4DU<T,ASymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4DU<T,ASymmetryMatrix,NullDiagonal>)));
      else if(M.property[MatrixActualTrianglePart]==LowerTriangle) {
        M.GetFunc=(SymmetryFlag?
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4DL<T,SymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4DL<T,SymmetryMatrix,NullDiagonal>)):
                  (DiagonalFlag?static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4DL<T,ASymmetryMatrix,HaveDiagonal>):
                                static_cast<typename Matrix<T>::GetFuncType>
                                (GetData4DL<T,ASymmetryMatrix,NullDiagonal>)));
      } else myError("Unknown Triangle part for Matrix");
    } else myError("Unknown or Unimplemented Data Order for Triangle Matrix");
    M.property[MatrixActualDimension]=Dim-(DiagonalFlag?0:1);
    if((M.property[MatrixActualDataPattern]==COrderUpperType)||
       (M.property[MatrixActualDataPattern]==DiagonalType)) {
      M.property[MatrixLineSizeFirst]=M.property[MatrixActualDimension];
      M.property[MatrixLineSizeShift]=static_cast<unsigned int>(-1);
    } else if(M.property[MatrixActualDataPattern]==FortranOrderUpperType) {
      M.property[MatrixLineSizeFirst]=1;
      M.property[MatrixLineSizeShift]=1;
    } else myError("Unknown Data Pattern for Triangle Matrix");
    M.property[MatrixNumberElement]=
      (M.property[MatrixActualDimension]*(M.property[MatrixActualDimension]+1))
      /2;
    M.data=new T[M.property[MatrixNumberElement]];
    M.structure=new T*[M.property[MatrixActualDimension]];
    T* PtrData=M.data;
    for(unsigned int 
        i=0,n=M.property[MatrixLineSizeFirst];
        i<M.property[MatrixActualDimension];
        ++i,PtrData+=n,n+=static_cast<int>(M.property[MatrixLineSizeShift]))
      M.structure[i]=PtrData;
    M.PtrOtherElement=(SymmetryFlag&&DiagonalFlag?NULL:new T);
  }

}

#endif
