
#ifndef _Matrix_Triangle_Name_H_
#define _Matrix_Triangle_Name_H_

#include "data/name/matrix-name.h"

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

}

#endif
