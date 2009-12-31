
/**
 * @file blas.h
 * @brief head file for BLAS procedures
 *
 * This file just includes a part of headers for BLAS procedures. These
 * procedures are all have C-style interfaces in the library. Therefore,
 * \c extern \c "C" should be used. Due to the differences of the naming
 * conventions in C and Fortran language, a character "_" is used after
 * the regular name here. Also for the sake of Fortran convention, all
 * the input variables should be pointers to certain quantities.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _BLAS_H_
#define _BLAS_H_

extern "C" {

  /**
   * @brief copy \c double data from one array to another
   *
   * This procedure could copy the data from an input array to an output
   * array. The spacings of elements in the input and out arrays could
   * be controlled. This function is for \c double type values.
   *
   * @see scopy_(long* N,float* X,long* dX,float* Y,long* dY)
   *
   * @param N
   *        The number of elements to copy (input)
   *
   * @param X
   *        The array containing the input data
   *
   * @param dX
   *        The spacing between two input values
   *
   * @param Y
   *        The array containing the output data
   *
   * @param dY
   *        The spacing between two output values
   *
   */
  void dcopy_(long* N,double* X,long* dX,double* Y,long* dY);

  /**
   * @brief copy \c float data from one array to another
   *
   * This procedure could copy the data from an input array to an output
   * array. The spacings of elements in the input and out arrays could
   * be controlled. This function is for \c float type values.
   *
   * @see dcopy_(long* N,double* X,long* dX,double* Y,long* dY)
   *
   * @param N
   *        The number of elements to copy (input)
   *
   * @param X
   *        The array containing the input data
   *
   * @param dX
   *        The spacing between two input values
   *
   * @param Y
   *        The array containing the output data
   *
   * @param dY
   *        The spacing between two output values
   *
   */
  void scopy_(long* N,float* X,long* dX,float* Y,long* dY);

  /**
   * @brief swap two \c double arrays
   *
   * This procedure could swap the contents of two arrays. The spacings
   * of the elements in these two arrays could be controlled. This function
   * is for \c double type values.
   *
   * @see sswap_(long*,float*,long*,float*,long*)
   *
   * @param N
   *        The number of elements to swap (input)
   *
   * @param X
   *        One array to be swapped
   *
   * @param dX
   *        The spacing between two values in array X
   *
   * @param Y
   *        The other array to be swapped
   *
   * @param dY
   *        The spacing between two values in array Y
   */
  void dswap_(long* N,double* X,long* dX,double* Y,long* dY);

  /**
   * @brief swap two \c float arrays
   *
   * This procedure could swap the contents of two arrays. The spacings
   * of the elements in these two arrays could be controlled. This function
   * is for \c float type values.
   *
   * @see dswap_(long*,double*,long*,double*,long*)
   *
   * @param N
   *        The number of elements to swap (input)
   *
   * @param X
   *        One array to be swapped
   *
   * @param dX
   *        The spacing between two values in array X
   *
   * @param Y
   *        The other array to be swapped
   *
   * @param dY
   *        The spacing between two values in array Y
   */
  void sswap_(long* N,float* X,long* dX,float* Y,long* dY);

  /**
   * @brief dot product of two \c double arrays
   *
   * The arrays are viewed as vectors to carry out the dot product.
   * It corresponds to the summation of the products of elements
   * in two arrays. This function is for \c double type values.
   *
   * @see sdot_(long*,float*,long*,float*,long*)
   *
   * @param N
   *        The number of elements to calculate dot product (input)
   *
   * @param X
   *        One array for dot product
   *
   * @param dX
   *        The spacing between two values in array X
   *
   * @param Y
   *        The other array for dot product
   *
   * @param dY
   *        The spacing between two values in array Y
   *
   * @return the dot product of the arrays.
   */
  double ddot_(long* N,double* X,long* dX,double* Y,long* dY);

  /**
   * @brief dot product of two \c float arrays
   *
   * The arrays are viewed as vectors to carry out the dot product.
   * It corresponds to the summation of the products of elements
   * in two arrays. This function is for \c float type values.
   *
   * @see ddot_(long*,double*,long*,double*,long*)
   *
   * @param N
   *        The number of elements to calculate dot product (input)
   *
   * @param X
   *        One array for dot product
   *
   * @param dX
   *        The spacing between two values in array X
   *
   * @param Y
   *        The other array for dot product
   *
   * @param dY
   *        The spacing between two values in array Y
   *
   * @return the dot product of the arrays.
   */
  float sdot_(long* N,float* X,long* dX,float* Y,long* dY);

  /**
   * @brief Calculate the norm of a \c double vector
   *
   * The array is viewed as a vector. This function calculates its Euclidean
   * norm, namely the the root of the square of elements. This function is
   * for \c double type values.
   *
   * @see snrm2_(long* N,float* X,long* dX)
   *
   * @param N
   *        The number of elements to calculate norm (input)
   *
   * @param X
   *        The array for norm calculation
   *
   * @param dX
   *        The spacing between two values in array X
   *
   * @return the norm of the input vector
   */
  double dnrm2_(long* N,double* X,long* dX);

  /**
   * @brief Calculate the norm of a \c float vector
   *
   * The array is viewed as a vector. This function calculates its Euclidean
   * norm, namely the the root of the square of elements. This function is
   * for \c float type values.
   *
   * @see dnrm2_(long* N,double* X,long* dX)
   *
   * @param N
   *        The number of elements to calculate norm (input)
   *
   * @param X
   *        The array for norm calculation
   *
   * @param dX
   *        The spacing between two values in array X
   *
   * @return the norm of the input vector
   */
  float snrm2_(long* N,float* X,long* dX);

  /**
   * @brief Calculate summation of the absolute values of an array
   *
   * This function sums all the absolute values of the concerned elements
   * in the input array. This is another kinds of norm for vectors. This
   * function is for \c double type values.
   *
   * @see sasum_(long* N,float* X,long* dX)
   *
   * @param N
   *        The number of elements to calculate summation (input)
   *
   * @param X
   *        The array for summation calculation
   *
   * @param dX
   *        The spacing between two values in array X
   *
   * @return the sum of values in the input vector
   */
  double dasum_(long* N,double* X,long* dX);

  /**
   * Calculate summation of the absolute values of an array
   *
   * This function sums all the absolute values of the concerned elements
   * in the input array. This is another kinds of norm for vectors. This
   * function is for \c float type values.
   *
   * @see dasum_(long* N,double* X,long* dX)
   *
   * @param N
   *        The number of elements to calculate summation (input)
   *
   * @param X
   *        The array for summation calculation
   *
   * @param dX
   *        The spacing between two values in array X
   *
   * @return the sum of values in the input vector
   */
  float sasum_(long* N,float* X,long* dX);

  /**
   * @brief Scale a vector with a \c double constant
   *
   * The elements in the input array are scaled (namely multiplify) with
   * a constant. It is similar as the enlargement of vector with a constant
   * ratio for various components. This function is for \c double type
   * values.
   *
   * @see sscal_(long*,float*,float*,long*)
   *
   * @param N
   *        The number of elements in scale operation (input)
   *
   * @param A
   *        The constant to scale the array
   *
   * @param X
   *        The array to be scaled
   *
   * @param dX
   *        The spacing between two values in array X
   */
  void dscal_(long* N,double* A,double* X,long* dX);

  /**
   * @brief Scale a vector with a \c float constant
   *
   * The elements in the input array are scaled (namely multiplify) with
   * a constant. It is similar as the enlargement of vector with a constant
   * ratio for various components. This function is for \c float type
   * values.
   *
   * @see dscal_(long*,double*,double*,long*)
   *
   * @param N
   *        The number of elements in scale operation (input)
   *
   * @param A
   *        The constant to scale the array
   *
   * @param X
   *        The array to be scaled
   *
   * @param dX
   *        The spacing between two values in array X
   */
  void sscal_(long* N,float* A,float* X,long* dX);

  /**
   * @brief Shift a \c double vector with another scaled vector
   *
   * This function is a composite operation for vector (array). One vector
   * is scaled with a constant, then the scaled vector is added to another
   * vector. The resultant vector is output as final result (stored in the
   * later vector). This function is for \c double type values.
   *
   * @see saxpy_(long* N,float* A,float* X,long* dX,float* Y,long* dY)
   *
   * @param N
   *        The number of elements related to this operation (input)
   *
   * @param A
   *        The constant to scale the elements of array X
   *
   * @param X
   *        The array to be scaled. The scaled value would be added to
   *        array Y. The array X is unchanged after operation (input)
   *
   * @param dX
   *        The spacing between two values in array X
   *
   * @param Y
   *        The array to be added. This array would add the scaled array X
   *        as the final output. The output is stored in this array 
   *        (input and output)
   *
   * @param dY
   *        The spacing between two values in array Y
   */
  void daxpy_(long* N,double* A,double* X,long* dX,double* Y,long* dY);

  /**
   * @brief Shift a \c float vector with another scaled vector
   *
   * This function is a composite operation for vector (array). One vector
   * is scaled with a constant, then the scaled vector is added to another
   * vector. The resultant vector is output as final result (stored in the
   * later vector). This function is for \c float type values.
   *
   * @see daxpy_(long* N,double* A,double* X,long* dX,double* Y,long* dY)
   *
   * @param N
   *        The number of elements related to this operation (input)
   *
   * @param [in] A
   *        The constant to scale the elements of array X
   *
   * @param X
   *        The array to be scaled. The scaled value would be added to
   *        array Y. The array X is unchanged after operation (input)
   *
   * @param dX
   *        The spacing between two values in array X
   *
   * @param [in,out] Y
   *        The array to be added. This array would add the scaled array X
   *        as the final output. The output is stored in this array.
   *        (input & output)
   *
   * @param [in] dY
   *        The spacing between two values in array Y
   */
  void saxpy_(long* N,float* A,float* X,long* dX,float* Y,long* dY);

  /**
   * @brief Scale \c double vector with a triangular band matrix
   *
   * This is an operation related to matrix-vector product. The concerned
   * matrix is in the form of triangular band. The storage for the matrix
   * is related to the shape of the matrix. The order of elements may refer
   * to TriangularBandMatrix in IBM (http://tiny.cc/NuTpJ). This function
   * is for \c double type values.
   *
   * @see stbmv_(char* UPLO,char* TRANS,char* DIAG,long* N,long* K,float* A,
   *             long* LDA,float* X,long* dX)
   *
   * @param [in] UPLO
   *        The character flag indicating the upper or lower triangle is used
   *
   * @param [in] TRANS
   *        The character flag indicating if transpose is needed for matrix
   *
   * @param [in] DIAG
   *        The character flag indicating if diagonal elements are null
   *
   * @param [in] N
   *        The number of elements in arrays to be operated. It could be
   *        viewed as the dimension of concerned vector.
   *
   * @param [in] K
   *        The width of bands in the concerned matrix. The diagonal is
   *        omitted in counting.
   *
   * @param [in] A
   *        The triangular band matrix to scale the vector
   *
   * @param [in] LDA
   *        The leading dimension of the matrix, namely the most internal
   *        dimension of matrix data. This value depends on the programming
   *        language (C or Fortran), which may have different internal
   *        order of storage.
   *
   * @param [in,out] X
   *        The array to be scaled. The result after scaling is also stored
   *        in this array.
   *
   * @param [in] dX
   *        The spacing of the elements for array X.
   */
  void dtbmv_(char* UPLO,char* TRANS,char* DIAG,long* N,long* K,double* A,
              long* LDA,double* X,long* dX);

  /**
   * @brief Scale \c float vector with a triangular band matrix
   *
   * This is an operation related to matrix-vector product. The concerned
   * matrix is in the form of triangular band. The storage for the matrix
   * is related to the shape of the matrix. The order of elements may refer
   * to TriangularBandMatrix in IBM (http://tiny.cc/NuTpJ). This function
   * is for \c float type values.
   *
   * @see dtbmv_(char* UPLO,char* TRANS,char* DIAG,long* N,long* K,double* A,
   *             long* LDA,double* X,long* dX)
   *
   * @param [in] UPLO
   *        The character flag indicating the upper or lower triangle is used
   *
   * @param [in] TRANS
   *        The character flag indicating if transpose is needed for matrix
   *
   * @param [in] DIAG
   *        The character flag indicating if diagonal elements are null
   *
   * @param [in] N
   *        The number of elements in arrays to be operated. It could be
   *        viewed as the dimension of concerned vector.
   *
   * @param [in] K
   *        The width of bands in the concerned matrix. The diagonal is
   *        omitted in counting.
   *
   * @param [in] A
   *        The triangular band matrix to scale the vector
   *
   * @param [in] LDA
   *        The leading dimension of the matrix, namely the most internal
   *        dimension of matrix data. This value depends on the programming
   *        language (C or Fortran), which may have different internal
   *        order of storage.
   *
   * @param [in,out] X
   *        The array to be scaled. The result after scaling is also stored
   *        in this array.
   *
   * @param [in] dX
   *        The spacing of the elements for array X.
   */
  void stbmv_(char* UPLO,char* TRANS,char* DIAG,long* N,long* K,float* A,
              long* LDA,float* X,long* dX);

  /**
   * @brief Composite operation related to real symmetric band matrix
   *
   * This is an operation relation matrix-vector production, constant-vector
   * production, and addition of vectors. The detailed operations are
   * multiplying a vector with constant and matrix at first, and multiplying
   * another vector with a constant, then adding the resultant vectors
   * together. The result is stored in the later vector. The order of elements
   * for symmetric band matrix in programming may refer to SymmetricBandMatrix
   * in IBM (http://tinyurl.com/yguyb4b or http://tinyurl.com/ydesn9z). This
   * function is for \c double type values.
   *
   * @see ssbmv_(char* UPLO,long* N,long* K,float* a,float* A,long* LDA,
   *             float* X,long* dX,float* b,float* Y,long* dY)
   *
   * @param [in] UPLO
   *        The character flag indicating the upper or lower triangle is used
   *
   * @param [in] N
   *        The number of elements in arrays to be operated. It could be
   *        viewed as the dimension of concerned vector.
   *
   * @param [in] K
   *        The width of bands in the concerned matrix. The diagonal is
   *        omitted in counting.
   *
   * @param [in] a
   *        The constant to scale the vector X.
   *
   * @param [in] A
   *        The symmetric band matrix to scale the vector X
   *
   * @param [in] LDA
   *        The leading dimension of the matrix, namely the most internal
   *        dimension of matrix data. This value depends on the programming
   *        language (C or Fortran), which may have different internal
   *        order of storage. It is said to take K+1 to have best
   *        performance.
   *
   * @param [in] X
   *        The vector to be scaled with constant and matrix
   *
   * @param [in] dX
   *        The spacing of the elements for array X.
   *
   * @param [in] b
   *        The constant to scale the vector Y
   *
   * @param [in,out] Y
   *        The vector to be scaled with constant and to store the result
   *        of final output of this composite operation.
   *
   * @param [in] dY
   *        The spacing of the elements for array Y.
   *
   * @note The vector Y must have not common elements with matrix A or
   *       the vector X. Otherwise, the results are unpredictable.
   */
  void dsbmv_(char* UPLO,long* N,long* K,double* a,double* A,long* LDA,
              double* X,long* dX,double* b,double* Y,long* dY);

  /**
   * @brief Composite operation related to real symmetric band matrix
   *
   * This is an operation relation matrix-vector production, constant-vector
   * production, and addition of vectors. The detailed operations are
   * multiplying a vector with constant and matrix at first, and multiplying
   * another vector with a constant, then adding the resultant vectors
   * together. The result is stored in the later vector. The order of elements
   * for symmetric band matrix in programming may refer to SymmetricBandMatrix
   * in IBM (http://tinyurl.com/yguyb4b or http://tinyurl.com/ydesn9z). This
   * function is for \c float type values.
   *
   * @see dsbmv_(char* UPLO,long* N,long* K,double* a,double* A,long* LDA,
   *             double* X,long* dX,double* b,double* Y,long* dY)
   *
   * @param [in] UPLO
   *        The character flag indicating the upper or lower triangle is used
   *
   * @param [in] N
   *        The number of elements in arrays to be operated. It could be
   *        viewed as the dimension of concerned vector.
   *
   * @param [in] K
   *        The width of bands in the concerned matrix. The diagonal is
   *        omitted in counting.
   *
   * @param [in] a
   *        The constant to scale the vector X.
   *
   * @param [in] A
   *        The symmetric band matrix to scale the vector X
   *
   * @param [in] LDA
   *        The leading dimension of the matrix, namely the most internal
   *        dimension of matrix data. This value depends on the programming
   *        language (C or Fortran), which may have different internal
   *        order of storage. It is said to take K+1 to have best
   *        performance.
   *
   * @param [in] X
   *        The vector to be scaled with constant and matrix
   *
   * @param [in] dX
   *        The spacing of the elements for array X.
   *
   * @param [in] b
   *        The constant to scale the vector Y
   *
   * @param [in,out] Y
   *        The vector to be scaled with constant and to store the result
   *        of final output of this composite operation.
   *
   * @param [in] dY
   *        The spacing of the elements for array Y.
   *
   * @note The vector Y must have not common elements with matrix A or
   *       the vector X. Otherwise, the results are unpredictable.
   */
  void ssbmv_(char* UPLO,long* N,long* K,float* a,float* A,long* LDA,
              float* X,long* dX,float* b,float* Y,long* dY);

  /**
   * @brief Composite operation related to \c double general matrix
   *
   * This operation is similar as the subroutine dsbmv_() except that
   * the concerned matrix is a general matrix. It is realized by
   * scaling one vector with constant and matrix, scaling another
   * vector with only a constant, and then add then together. The
   * final result is stored in the later vector to be scaled. This
   * function is for \c double type values.
   *
   * @see sgemv_(char* TRANS,long* M,long* N,float* a,float* A,long* LDA,
   *             float* X,long* dX,float* b,float* Y,long* dY)
   *
   * @param [in] TRANS
   *        The character flag indicating if transpose is needed for matrix
   *
   * @param [in] M
   *        The number of rows of matrix A
   *
   * @param [in] N
   *        The number of columns of matrix A
   *
   * @param [in] a
   *        The constant to scale the vector X
   *
   * @param [in] A
   *        The \c double general matrix
   *
   * @param [in] LDA
   *        The leading dimension of the matrix, namely the most internal
   *        dimension of matrix data. This value depends on the programming
   *        language (C or Fortran), which may have different internal
   *        order of storage.
   *
   * @param [in] X
   *        The vector to be scaled with constant and matrix
   *
   * @param [in] dX
   *        The spacing between two values in array X
   *
   * @param [in] b
   *        The constant to scale the vector Y
   *
   * @param [in,out] Y
   *        The vector to be scaled with constant and to store the result
   *
   * @param [in] dY
   *        The spacing of the elements for array Y.
   */
  void dgemv_(char* TRANS,long* M,long* N,double* a,double* A,long* LDA,
              double* X,long* dX,double* b,double* Y,long* dY);

  /**
   * @brief Composite operation related to \c float general matrix
   *
   * This operation is similar as the subroutine ssbmv_() except that
   * the concerned matrix is a general matrix. It is realized by
   * scaling one vector with constant and matrix, scaling another
   * vector with only a constant, and then add then together. The
   * final result is stored in the later vector to be scaled. This
   * function is for \c float type values.
   *
   * @see dgemv_(char* TRANS,long* M,long* N,double* a,double* A,long* LDA,
   *             double* X,long* dX,double* b,double* Y,long* dY)
   *
   * @param [in] TRANS
   *        The character flag indicating if transpose is needed for matrix
   *
   * @param [in] M
   *        The number of rows of matrix A
   *
   * @param [in] N
   *        The number of columns of matrix A
   *
   * @param [in] a
   *        The constant to scale the vector X
   *
   * @param [in] A
   *        The \c float general matrix
   *
   * @param [in] LDA
   *        The leading dimension of the matrix, namely the most internal
   *        dimension of matrix data. This value depends on the programming
   *        language (C or Fortran), which may have different internal
   *        order of storage.
   *
   * @param [in] X
   *        The vector to be scaled with constant and matrix
   *
   * @param [in] dX
   *        The spacing between two values in array X
   *
   * @param [in] b
   *        The constant to scale the vector Y
   *
   * @param [in,out] Y
   *        The vector to be scaled with constant and to store the result
   *
   * @param [in] dY
   *        The spacing of the elements for array Y.
   */
  void sgemv_(char* TRANS,long* M,long* N,float* a,float* A,long* LDA,
              float* X,long* dX,float* b,float* Y,long* dY);

}

#endif

