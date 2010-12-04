
#ifndef _Matrix_Name_H_
#define _Matrix_Name_H_

namespace std {

  enum MatrixBasePropertyName {
    MatrixType=0,
    MatrixNumberElement,
    MatrixNumberRow,
    MatrixNumberColumn,
    MatrixDataOrder,
    MatrixDataState,
    MatrixTransposeForm,
    MatrixActualOrder,
    MatrixCommonNumberProperty
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

}

#endif
