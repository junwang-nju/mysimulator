
/**
 * @file matrix.h
 * @brief the data structure of Matrix
 *
 * This file contains the data structures of matrix and some related
 * operations.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Matrix_H_
#define _Matrix_H_

#include "vector.h"
#include <cstdarg>

namespace std {

  /**
   * @brief the names of various properties in base type of matrix
   *
   * This enumerator contains the set of the names for various properties.
   * THese names defines the order (location) of the features in the
   * storage of properties.
   */
  enum MatrixBasePropertyName {
    /**
     * @brief the type of matrix
     */
    MatrixType=0,
    /**
     * @brief the number of elements in matrix
     */
    MatrixNumberElement,
    /**
     * @brief the number of rows in matrix
     */
    MatrixNumberRow,
    /**
     * @brief the number of columns in martix
     */
    MatrixNumberColumn,
    /**
     * @brief the state of data storage
     */
    MatrixDataState,
    /**
     * @brief the order of data arrangement
     */
    MatrixDataOrder,
    /**
     * @brief the flag indicating if the matrix is transposed
     */
    MatrixTransposeForm,
    /**
     * @brief the actual order of data arrangement in matrix
     *
     * This is determined by the Order and the transpose state of the matrix
     */
    MatrixActualOrder,
    /**
     * @brief the number of the common properties of matrix
     */
    MatrixCommonNumberProperty,
  };

  /**
   * @brief the name of the type of matrix
   *
   * This enumerator contains the type name for various kinds of matrices.
   * This could be extended.
   */
  enum MatrixTypeName {
    /**
     * @brief the type indicating a matrix with a rectangle shape
     */
    RectangleMatrix=0,
    /**
     * @brief the type indicating a matrix with a triangle shape
     */
    TriangleMatrix
  };

  /**
   * @brief the name of the order type for data arrangement in matrix
   *
   * This enumerator contains the names for various orders to arrange data
   * in matrix.
   */
  enum MatrixDataOrderName {
    /**
     * @brief the order resembling the 2-d array in C-language (namely column first)
     */
    COrder=0,
    /**
     * @brief the order resembling the 2-d array in Fortran-language (namely row first)
     */
    FortranOrder,
    /**
     * @brief the order to arrange data along the diagonal direction.
     */
    DiagonalOrder
  };

  /**
   * @brief the name of the transpose states of matrix.
   *
   * This enumerator contains the names for various transpose states.
   */
  enum MatrixTransposeFormName {
    /**
     * @brief the state indicating that there are no transpose for matrix.
     */
    NoTranspose=0,
    /**
     * @brief the state indicating that the matrix is transposed.
     */
    Transposed
  };

  /**
   * @brief The data structure with matrix shape 
   *
   * This data structure is established to describe the matrix data, the
   * data with two dimensions. Various shapes and internal organizations
   * are available. The operations for different kinds of matrices are
   * implemented with generic programming.
   *
   * T is the type of the elements in matrix.
   *
   * @todo the sparse matrix is not implemented here. It is not sure if
   *       that kind of data could fit with the present structure. 
   */
  template <typename T>
  struct Matrix : public Vector<T> {

    /**
     * @brief abbreviation for the type of matrix
     */
    typedef Matrix<T> Type;
    /**
     * @brief the abbreviation for the parent type of matrix.
     *
     * It is a vector of data to enable the operations for vector.
     */
    typedef Vector<T> ParentType;
    /**
     * @brief the type of function pointer to get a certain element
     */
    typedef T& (*GetFuncType)(T**,const unsigned int,const unsigned int,T&);

    /**
     * @brief the internal structure for matrix
     *
     * This structure offers the row/column structure to ease the data
     * access.
     */
    T** structure;
    /**
     * @brief the properties of matrix
     *
     * The names of various properties follow the enumerator
     * MatrixBasePropertyName.
     */
    unsigned int *property;
    /**
     * @brief the pointer to the elements not to be access through structure
     *
     * For some special matrices, such as triangle, some elements cannot
     * be accessed (or not necessary to be accessed) through the data pointer,
     * structure. This pointer offers a way to access this kind of data.
     */
    T* PtrOtherElement;
    /**
     * @brief the function pointer to access elements
     */
    GetFuncType GetFunc;

    /**
     * @brief default initiator
     *
     * Just initiate all the pointers with NULL.
     */ 
    Matrix()
      : ParentType(), structure(NULL), property(NULL), PtrOtherElement(NULL),
        GetFunc(NULL) {}
    /**
     * @brief initiator from another Matrix object
     *
     * It is prohibited and pops out an error message.
     *
     * @param MB [in] the input Matrix object
     */
    Matrix(const Type& MB) { myError("Cannot create Matrix"); }
    /**
     * @brief copy Matrix from another Matrix object
     *
     * It is implemented with the assign operation.
     *
     * @param M [in] the input Matrix object
     * @return the reference to the resultant Matrix.
     */
    Type& operator=(const Type& M) { assign(*this,M); return *this; }
    /**
     * @brief destructor
     *
     * It is implemented with release operation.
     */
    ~Matrix() { release(*this); }

    /**
     * @brief access the elements with the indices
     *
     * It is implemented with the function pointed by the internal
     * function pointer.
     *
     * @param I,J [in] the row, column index for the element
     * @return the reference to the expected elements. If the elements
     *         cannot be accessed with regular method, the reference to
     *         the specific element is returned.
     */
    T& operator()(const unsigned int I, const unsigned int J) {
      return GetFunc(structure,I,J,*PtrOtherElement);
    }
    /**
     * @brief visit the elements with the indices
     *
     * It is implemented with the function pointed by the internal
     * function pointer.
     *
     * @param I,J [in] the row, column index for the element
     * @return the const reference to the expected elements. If the elements
     *         cannot be visited with regular method, the const reference to
     *         the specific element is returned.
     */
    const T& operator()(const unsigned int I, const unsigned int J) const {
      return GetFunc(const_cast<T**>(structure),I,J,
                     const_cast<T&>(*PtrOtherElement));
    }

  };

  /**
   * @brief check the availability of the Matrix object
   *
   * It is implemented by checking the parent vector of the matrix object.
   *
   * T is the type of the elements in matrix.
   *
   * @param M [in] the matrix object to be checked.
   * @return the flag indicating if the matrix is available.
   */
  template <typename T>
  bool IsAvailable(const Matrix<T>& M) {
    return IsAvailable(static_cast<const Vector<T>&>(M));
  }

  /**
   *  @brief release a matrix object
   *
   * Just release the internal storage and release the parent vector object.
   *
   * T is the type of the elements in matrix.
   *
   * @param M [out] the matrix object to be released.
   * @return nothing
   */
  template <typename T>
  void release(Matrix<T>& M) {
    if(M.state==Allocated) {
      safe_delete_array(M.structure);
      safe_delete_array(M.property);
      safe_delete(M.PtrOtherElement);
    } else {
      M.structure=NULL;
      M.property=NULL;
      M.PtrOtherElement=NULL;
    }
    M.GetFunc=NULL;
    release(static_cast<Vector<T>&>(M));
  }

  /**
   * @brief refer to another matrix object
   *
   * Just assign the internal pointers of the destinate matrix with those
   * in source matrix, and the parent vector is referred to that of the
   * source matrix. Before these operations, the source matrix is checked
   *  for its availability, and the destinate matrix is released.
   *
   * T is the type of elements in matrices.
   *
   * @param destM [out] the matrix to accept the input
   * @param srcM [in] the matrix containing the input information
   * @return nothing
   */
  template <typename T>
  void refer(Matrix<T>& destM, const Matrix<T>& srcM) {
    assert(IsAvailable(srcM));
    release(destM);
    destM.structure=const_cast<T**>(srcM.structure);
    destM.property=const_cast<unsigned int*>(srcM.property);
    destM.PtrOtherElement=const_cast<T*>(srcM.PtrOtherElement);
    destM.GetFunc=srcM.GetFunc;
    refer(static_cast<Vector<T>&>(destM),static_cast<const Vector<T>&>(srcM));
  }

  /**
   * @brief output the matrix through ostream
   *
   * Just write the matrix row by row. Tabs are used to separate elements
   * in lines.
   *
   * T is the type of elements in matrix.
   *
   * @param os [in,out] the ostream to accept the input
   * @param M [in] the matrix to be written out.
   * @return the ostream after this output operation.
   */
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

  /**
   * @brief allocate matrix based on the input information
   *
   * The concerned matrix is allocated based on the expected type and
   * other information in variable parameter list. It uses some
   * presumed allocation functions.
   *
   * T is the type of elements in matrix.
   *
   * @param M [out] the matrix to be allocated.
   * @param MatrixType [in] the expected type of matrix to be allocated.
   * @return nothing
   *
   * @note a variable list is used to fit different interface of allocation
   *       for various matrices. 
   * @note since the allocation function is not generic with same
   *       interface, no common pointer are assigned inside the matrix object.
   */
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
    } else if(MatrixType==TriangleMatrix) {
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

  /**
   * @brief swap two matrix objects
   *
   * Swap the internal pointers as well as the parent vector objects.
   *
   * T is the type of elements in matrix.
   *
   * @param Ma,Mb [in,out] the matrices to be swapped.
   * @return nothing
   */
  template <typename T>
  void swap(Matrix<T>& Ma, Matrix<T>& Mb) {
    swap(Ma.structure,Mb.structure);
    swap(Ma.property,Mb.property);
    swap(Ma.PtrOtherElement,Mb.PtrOtherElement);
    swap(Ma.GetFunc,Mb.GetFunc);
    swap(static_cast<Vector<T>&>(Ma),static_cast<Vector<T>&>(Mb));
  }

  /**
   * @brief set up the actual order based on internal information
   *
   * The actual order is determined by the original order and the
   * transpose state. The order and transpose state are checked
   * during running.
   *
   * @param property [in,out] the array containing properties
   * @return nothing
   */
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

  /**
   * @brief assign matrix from another
   *
   * It is implemented by assigning corresponding elements one by one
   * in destinate matrix with source matrix. The part of matrix of also
   * picked up.
   *
   * T is the type of elements in matrix.
   *
   * @param destM [in,out] the matrix to accept the input data
   * @param srcM [in] the matrix containing the input information
   * @param nrow, ncol [in] the numbers of rows and columns
   * @param sroff, scoff, droff, dcoff [in] the offests for the starting
   *                                        rows or columns in destM or
   *                                        srcM. They takes default value of
   *                                        uZero.
   * @param srstep,scstep,drstep,dcstep [in] the steps between the rows or
   *                                         columns in destM or srcM. They
   *                                         takes default value of uOne.
   * @return nothing
   *
   * @note Regularly, the assignment only works between matrices with
   *       similar structures. The checks are carried out inside the loop.
   */
  template <typename T>
  void assign(Matrix<T>& destM, const Matrix<T>& srcM,
              const unsigned int nrow=uZero, const unsigned int ncol=uZero,
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
    unsigned int nr,nc;
    if(nrow==0)
      nr=(destM.property[MatrixNumberRow]<srcM.property[MatrixNumberRow]?
          destM.property[MatrixNumberRow]:srcM.property[MatrixNumberRow]);
    if(ncol==0)
      nc=(destM.property[MatrixNumberColumn]<srcM.property[MatrixNumberColumn]?
          destM.property[MatrixNumberColumn]:srcM.property[MatrixNumberColumn]);
    for(unsigned int i=0,sr=sroff,dr=droff;i<nr;++i,sr+=srstep,dr+=drstep)
    for(unsigned int j=0,sc=scoff,dc=dcoff;j<nc;++j,sc+=scstep,dc+=dcstep)
      destM(dr,dc)=srcM(sr,sc);
  }

}

#endif
