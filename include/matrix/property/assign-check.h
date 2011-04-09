
#ifndef _Matrix_Property_Assign_Check_H_
#define _Matrix_Property_Assign_Check_H_

#include "vector/interface.h"
#include "matrix/base/property-name.h"
#include "matrix/type-name.h"
#include "matrix/triangle/property-name.h"
#include "matrix/triangle/symmetry-name.h"

namespace mysimulator {

  bool AssignCheck(const Vector<unsigned int>& p,
                   const Vector<unsigned int>& cp) {
    if(p[MatrixType]!=MatrixTriangle)   return true;
    if(cp[MatrixType]==MatrixTriangle)
      if(cp[MatrixDiagonalExistFlag]==p[MatrixDiagonalExistFlag])
        if(cp[MatrixSymmetryFlag]==p[MatrixSymmetryFlag]) {
          if(p[MatrixSymmetryFlag]==SymmetryMatrix) return true;
          if(p[MatrixActualTrianglePart]==cp[MatrixActualTrianglePart])
            return true;
        }
    return false;
  }

}

#endif

