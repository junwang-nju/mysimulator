
#ifndef _Matrix_Triangle_Allocate_H_
#define _Matrix_Triangle_Allocate_H_

#include "matrix/interface.h"
#include "matrix/triangle/property-name.h"
#include "matrix/type-name.h"
#include "matrix/triangle/symmetry-name.h"
#include "matrix/triangle/diagonal-exist-name.h"
#include "matrix/property/op.h"
#include "matrix/triangle/triangle-part-name.h"
#include "matrix/triangle/data-pattern-name.h"
#include "matrix/triangle/get-func.h"

namespace mysimulator {

  template <typename T>
  void allocateMatrixTriangle(
      Matrix<T>& M, const unsigned int dim, const unsigned int DOrder,
      const unsigned int TransForm, const unsigned int TriPart,
      const bool SFlag, const bool DFlag) {
    release(M);
    allocate(M.property,NumberMatrixTriangleProperty);
    M.property[MatrixType]=MatrixTriangle;
    M.property[MatrixNumberRows]=M.property[MatrixNumberColumns]=dim;
    M.property[MatrixDimension]=dim;
    M.property[MatrixDataOrder]=DOrder;
    M.property[MatrixTranspose]=TransForm;
    M.property[MatrixTrianglePart]=TriPart;
    M.property[MatrixSymmetryFlag]=(SFlag?SymmetryMatrix:ASymmetryMatrix);
    M.property[MatrixDiagonalExistFlag]=(DFlag?HaveDiagonal:NullDiagonal);
    _ProduceActualDataOrder(M.property);
    if(TransForm==NoTranspose)
      M.property[MatrixActualTrianglePart]=M.property[MatrixTrianglePart];
    else if(TransForm==Transposed) {
      if(TriPart==UpperTriangle)
        M.property[MatrixActualTrianglePart]=LowerTriangle;
      else if(TriPart==LowerTriangle)
        M.property[MatrixActualTrianglePart]=UpperTriangle;
      else Error("Improper Triangle Part to allocate Triangle Matrix");
    } else Error("Improper Transpose Flag to allocate Triangle Matrix!");
    if(M.property[MatrixActualOrder]==OrderC) {
      if(M.property[MatrixActualTrianglePart]==UpperTriangle) {
        M.property[MatrixActualDataPattern]=PatternCUpper;
        M.GetFunc=SFlag?(DFlag?MatrixTri_Get4CUSD<T>:MatrixTri_Get4CUSN<T>):
                        (DFlag?MatrixTri_Get4CUAD<T>:MatrixTri_Get4CUAN<T>);
      } else if(M.property[MatrixActualTrianglePart]==LowerTriangle) {
        M.property[MatrixActualDataPattern]=PatternFortranUpper;
        M.GetFunc=SFlag?(DFlag?MatrixTri_Get4CLSD<T>:MatrixTri_Get4CLSN<T>):
                        (DFlag?MatrixTri_Get4CLAD<T>:MatrixTri_Get4CLAN<T>);
      } else Error("Improper Triangle Part to allocate Triangle Matrix!");
    } else if(M.property[MatrixActualOrder]==OrderFortran) {
      if(M.property[MatrixActualTrianglePart]==UpperTriangle) {
        M.property[MatrixActualDataPattern]=PatternFortranUpper;
        M.GetFunc=SFlag?(DFlag?MatrixTri_Get4FUSD<T>:MatrixTri_Get4FUSN<T>):
                        (DFlag?MatrixTri_Get4FUAD<T>:MatrixTri_Get4FUAN<T>);
      } else if(M.property[MatrixActualTrianglePart]==LowerTriangle) {
        M.property[MatrixActualDataPattern]=PatternCUpper;
        M.GetFunc=SFlag?(DFlag?MatrixTri_Get4FLSD<T>:MatrixTri_Get4FLSN<T>):
                        (DFlag?MatrixTri_Get4FLAD<T>:MatrixTri_Get4FLAN<T>);
      } else Error("Improper Triangle Part to allocate Triangle Matrix!");
    } else if(M.property[MatrixActualOrder]==OrderDiagonal) {
      if(M.property[MatrixActualTrianglePart]==UpperTriangle) {
        M.property[MatrixActualDataPattern]=PatternDiagonal;
        M.GetFunc=SFlag?(DFlag?MatrixTri_Get4DUSD<T>:MatrixTri_Get4DUSN<T>):
                        (DFlag?MatrixTri_Get4DUAD<T>:MatrixTri_Get4DUAN<T>);
      } else if(M.property[MatrixActualTrianglePart]==LowerTriangle) {
        M.property[MatrixActualDataPattern]=PatternDiagonal;
        M.GetFunc=SFlag?(DFlag?MatrixTri_Get4DLSD<T>:MatrixTri_Get4DLSN<T>):
                        (DFlag?MatrixTri_Get4DLAD<T>:MatrixTri_Get4DLAN<T>);
      } else Error("Improper Triangle Part to allocate Triangle Matrix!");
    } else Error("Improper Actual Data Order to allocate Triangle Matrix!");
    unsigned int rdim=Dim=(DFlag?0:1);
    M.property[MatrixActualDimension]=rdim;
    int szfirst,szshift;
    if((M.property[MatrixActualDataPattern]==PatternCUpper)||
       (M.property[MatrixActualDataPattern]==PatternDiagonal)) {
      szfirst=rdim;
      szshift=-1;
    } else if(M.property[MatrixActualDataPattern]==PatternFortranUpper) {
      szfirst=1;
      szshift=1;
    } else Error("Improper Data Pattern to allocate Triangle Matrix!");
    M.property[MatrixNumberElements]=(rdim*(rdim+1))/2;
    Vector<unsigned int> sz(rdim);
    sz[0]=static_const<unsigned int>(szfirst);
    for(unsigned int i=1;i<rdim;++i)
      sz[i]=static_const<unsigned int>(static_cast<int>(sz[i-1])+szshift);
    allocate(static_cast<List<T>&>(M),sz);
    if(SFlag&&DFlag)  allocate(M.other);
  }

}

#endif

