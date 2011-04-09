
#ifndef _Matrix_Triangle_Property_Name_H_
#define _Matrix_Triangle_Property_Name_H_

#include "matrix/base/property-name.h"

namespace mysimulator {

  enum MatrixTrianglePropertyName {
    MatrixDimension=NumberMatrixBaseProperty,
    MatrixSymmetryFlag,
    MatrixTrianglePart,
    MatrixDiagonalExistFlag,
    MatrixActualDimension,
    MatrixActualTrianglePart,
    MatrixActualDataPattern,
    NumberMatrixTriangleProperty
  };

}

#endif

