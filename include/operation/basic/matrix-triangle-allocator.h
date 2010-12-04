
#ifndef _Matrix_Triangle_Allocator_H_
#define _Matrix_Triangle_Allocator_H_

#include "data/name/matrix-triangle.h"

namespace std {

  template <typename T>
  struct Matrix;

  template <typename T, int SFlag, int DFlag>
  T& GetData4CU(Vector<T>* s, const int I, const int J, T& OE) {
    if((DFlag==NullDiagonal)&&(I==J)) return OE;
    int rI=I, rJ=J;
    if(rI>rJ) {if(SFlag==ASymmetryMatrix) return OE; rI=J; rJ=I; }
    return s[rI][rJ-rI-(DFlag==NullDiagonal?1:0)];
  }

  template <typename T, int SFlag, int DFlag>
  T& GetData4CL(Vector<T>* s, const int I, const int J, T& OE) {
    if((DFlag==NullDiagonal)&&(I==J)) return OE;
    int rI=I, rJ=J;
    if(rI<rJ) { if(SFlag==ASymmetryMatrix) return OE; rI=J; rJ=I; }
    return s[rI-(DFlag==NullDiagonal?1:0)][rJ];
  }

  template <typename T, int SFlag, int DFlag>
  T& GetData4FU(Vector<T>* s, const int I, const int J, T& OE) {
    if((DFlag==NullDiagonal)&&(I==J)) return OE;
    int rI=I, rJ=J;
    if(rI>rJ) { if(SFlag==ASymmetryMatrix) return OE; rI=J; rJ=I; }
    return s[rJ-(DFlag==NullDiagonal?1:0)][rI];
  }

  template <typename T, int SFlag, int DFlag>
  T& GetData4FL(Vector<T>* s, const int I, const int J, T& OE) {
    if((DFlag==NullDiagonal)&&(I==J)) return OE;
    int rI=I, rJ=J;
    if(rI<rJ) { if(SFlag==ASymmetryMatrix) return OE; rI=J; rJ=I; }
    return s[rJ][rI-rJ-(DFlag==NullDiagonal?1:0)];
  }

  template <typename T, int SFlag, int DFlag>
  T& GetData4DU(Vector<T>* s, const int I, const int J, T& OE) {
    if((DFlag==NullDiagonal)&&(I==J)) return OE;
    int rI=I, rJ=J;
    if(rI>rJ) { if(SFlag==ASymmetryMatrix) return OE; rI=J; rJ=I; }
    return s[rJ-rI-(DFlag==NullDiagonal?1:0)][rI];
  }

  template <typename T, int SFlag, int DFlag>
  T& GetData4DL(Vector<T>* s, const int I, const int J, T& OE) {
    if((DFlag==NullDiagonal)&&(I==J)) return OE;
    int rI=I, rJ=J;
    if(rI<rJ) { if(SFlag==ASymmetryMatrix) return OE; rI=J; rJ=I; }
    return s[rI-rJ-(DFlag==NullDiagonal?1:0)][rJ];
  }

  template <typename T>
  void allocateTriangleMatrix(Matrix<T>& M,
                              const int Dim, const int DOrder,
                              const int TForm, const int TPart,
                              const bool SFlag, const bool DFlag) {
    allocate(M.property,MatrixTriangleNumberProperty);
    M.property[MatrixType]=TriangleMatrix;
    M.property[MatrixNumberRow]=M.property[MatrixNumberColumn]=Dim;
    M.property[MatrixDimension]=Dim;
    M.property[MatrixDataOrder]=DOrder;
    M.property[MatrixTransposeForm]=TForm;
    M.property[MatrixTrianglePart]=TPart;
    M.property[MatrixSymmetryFlag]=(SFlag?SymmetryMatrix:ASymmetryMatrix);
    M.property[MatrixDiagonalExistFlag]=(DFlag?HaveDiagonal:NullDiagonal);
    M.SetActualOrder();
    if(M.property[MatrixTransposeForm]==NoTranspose)
      M.property[MatrixActualTrianglePart]=M.property[MatrixTrianglePart];
    else if(M.property[MatrixTransposeForm]==Transposed) {
      if(M.property[MatrixTrianglePart]==UpperTriangle)
        M.property[MatrixActualTrianglePart]=LowerTriangle;
      else if(M.property[MatrixTrianglePart]==LowerTriangle)
        M.property[MatrixActualTrianglePart]=UpperTriangle;
      else myError("Unknown Triangle Part");
    } else myError("Unknown Transpose Format");
    if(M.property[MatrixActualOrder]==COrder) {
      if(M.property[MatrixActualTrianglePart]==UpperTriangle) {
        M.property[MatrixActualDataPattern]=COrderUpperType;
        M.GetFunc=(SFlag?(DFlag?
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4CU<T,SymmetryMatrix,HaveDiagonal>):
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4CU<T,SymmetryMatrix,NullDiagonal>))
                        :(DFlag?
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4CU<T,ASymmetryMatrix,HaveDiagonal>):
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4CU<T,ASymmetryMatrix,NullDiagonal>)));
      } else if(M.property[MatrixActualTrianglePart]==LowerTriangle) {
        M.property[MatrixActualDataPattern]=FortranOrderUpperType;
        M.GetFunc=(SFlag?(DFlag?
        static_cast<typename Matrix<T>::GetFuncType>
          (GetData4CL<T,SymmetryMatrix,HaveDiagonal>):
        static_cast<typename Matrix<T>::GetFuncType>
          (GetData4CL<T,SymmetryMatrix,NullDiagonal>))
                        :(DFlag?
        static_cast<typename Matrix<T>::GetFuncType>
          (GetData4CL<T,ASymmetryMatrix,HaveDiagonal>):
        static_cast<typename Matrix<T>::GetFuncType>
          (GetData4CL<T,ASymmetryMatrix,NullDiagonal>)));
      } else myError("Unknown Triangle Part");
    } else if(M.property[MatrixActualOrder]==FortranOrder) {
      if(M.property[MatrixActualTrianglePart]==UpperTriangle) {
        M.property[MatrixActualDataPattern]=FortranOrderUpperType;
        M.GetFunc=(SFlag?(DFlag?
        static_cast<typename Matrix<T>::GetFuncType>
          (GetData4FU<T,SymmetryMatrix,HaveDiagonal>):
        static_cast<typename Matrix<T>::GetFuncType>
          (GetData4FU<T,SymmetryMatrix,NullDiagonal>))
                        :(DFlag?
        static_cast<typename Matrix<T>::GetFuncType>
          (GetData4FU<T,ASymmetryMatrix,HaveDiagonal>):
        static_cast<typename Matrix<T>::GetFuncType>
          (GetData4FU<T,ASymmetryMatrix,NullDiagonal>)));
      } else if(M.property[MatrixActualTrianglePart]==LowerTriangle) {
        M.property[MatrixActualDataPattern]=COrderUpperType;
        M.GetFunc=(SFlag?(DFlag?
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4FL<T,SymmetryMatrix,HaveDiagonal>):
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4FL<T,SymmetryMatrix,NullDiagonal>))
                        :(DFlag?
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4FL<T,ASymmetryMatrix,HaveDiagonal>):
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4FL<T,ASymmetryMatrix,NullDiagonal>)));
      } else myError("Unknown Triangle Part");
    } else if(M.property[MatrixActualOrder]==DiagonalOrder) {
      M.property[MatrixActualDataPattern]=DiagonalType;
      if(M.property[MatrixActualTrianglePart]==UpperTriangle) {
        M.GetFunc=(SFlag?(DFlag?
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4DU<T,SymmetryMatrix,HaveDiagonal>):
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4DU<T,SymmetryMatrix,NullDiagonal>))
                        :(DFlag?
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4DU<T,ASymmetryMatrix,HaveDiagonal>):
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4DU<T,ASymmetryMatrix,NullDiagonal>)));
      } else if(M.property[MatrixActualTrianglePart]==LowerTriangle) {
        M.GetFunc=(SFlag?(DFlag?
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4DL<T,SymmetryMatrix,HaveDiagonal>):
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4DL<T,SymmetryMatrix,NullDiagonal>))
                        :(DFlag?
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4DL<T,ASymmetryMatrix,HaveDiagonal>):
          static_cast<typename Matrix<T>::GetFuncType>
            (GetData4DL<T,ASymmetryMatrix,NullDiagonal>)));
      } else myError("Unknown Triangle Part");
    } else myError("Unknown Data Order");
    int rDim=Dim-(DFlag?0:1);
    M.property[MatrixActualDimension]=rDim;
    if((M.property[MatrixActualDataPattern]==COrderUpperType)||
       (M.property[MatrixActualDataPattern]==DiagonalType)) {
      M.property[MatrixLineSizeFirst]=M.property[MatrixActualDimension];
      M.property[MatrixLineSizeShift]=-1;
    } else if(M.property[MatrixActualDataPattern]==FortranOrderUpperType) {
      M.property[MatrixLineSizeFirst]=1;
      M.property[MatrixLineSizeShift]=1;
    } else myError("Unknown Data Pattern");
    M.property[MatrixNumberElement]=(rDim*(rDim+1))/2;
    Vector<unsigned int> sz;
    allocate(sz,rDim);
    sz[0]=M.property[MatrixLineSizeFirst];
    for(int i=1;i<rDim;++i)
      sz[i]=sz[i-1]+M.property[MatrixLineSizeShift];
    allocate(static_cast<PropertyList<T>&>(M),sz);
    M.ptrOther=(SFlag&&DFlag?NULL:new T);
  }

}

#endif
 
