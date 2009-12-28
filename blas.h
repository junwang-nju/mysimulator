
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
   * copy \c double data from one array to another
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
   * copy \c float data from one array to another
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
   * swap two \c double arrays
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
   * swap two \c float arrays
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
   * dot product of two \c double arrays
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
   * dot product of two \c float arrays
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
   * Calculate the norm of a \c double vector
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
   * Calculate the norm of a \c float vector
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
   * Calculate summation of the absolute values of an array
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
   * scale a vector with a \c double constant
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
   * scale a vector with a \c float constant
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
   * Shift a \c double vector with another scaled vector
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
   * Shift a \c float vector with another scaled vector
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
   *        as the final output. The output is stored in this array.
   *        (input & output)
   *
   * @param dY
   *        The spacing between two values in array Y
   */
  void saxpy_(long* N,float* A,float* X,long* dX,float* Y,long* dY);

  void dtbmv_(char* UPLO,char* TRANS,char* DIAG,long* N,long* K,double* A,
              long* LDA,double* X,long* dX);

  void stbmv_(char* UPLO,char* TRANS,char* DIAG,long* N,long* K,float* A,
              long* LDA,float* X,long* dX);

  void dsbmv_(char* UPLO,long* N,long* K,double* a,double* A,long* LDA,
              double* X,long* dX,double* b,double* Y,long* dY);

  void ssbmv_(char* UPLO,long* N,long* K,float* a,float* A,long* LDA,
              float* X,long* dX,float* b,float* Y,long* dY);

  void dgemv_(char* TRANS,long* M,long* N,double* a,double* A,long* LDA,
              double* X,long* dX,double* b,double* Y,long* dY);

  void sgemv_(char* TRANS,long* M,long* N,float* a,float* A,long* LDA,
              float* X,long* dX,float* b,float* Y,long* dY);

}

#endif

