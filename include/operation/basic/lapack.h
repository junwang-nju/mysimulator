
/**
 * @file lapack.h
 * @brief The interface to use LAPACK functions
 *
 * This file contains the interfaces to use LAPACK functions, which
 * are generally defined and compiled with FORTRAN convernsion.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _LAPACK_H_
#define _LAPACK_H_

extern "C" {

  void dgeqrf_(int* M, int* N, double* A, int* LDA, double* Tau,
               double* Work, int* LWork, int* info);
  void sgeqrf_(int* M, int* N, float* A, int* LDA, float* Tau,
               float* Work, int* LWork, int* info);
  /**
   * @brief eigen-analysis for symmetric real matrix
   *
   * This procedure calculates the eigen-values and eigen-vectors
   * of the input real symmetric matrix.
   *
   * @param JobZ [in] the flag to activate calculations for eigen
   *                  -vectors. When it is 'N', only eigen values
   *                  are calculated. When it is 'V', eigen vectors
   *                  are also calculated.
   * @param UpLo [in] the flag indicating which part of matrix is
   *                  used. When it is 'U', the upper part is used.
   *                  When it is 'L', the lower part is used.
   * @param N [in] the pointer to the dimension of matrix
   * @param A [in,out] the matrix to be diagonalized. after the operation,
   *                   the orthonormal eigen vectors are stored
   * @param LDA [in] the pointer to leading dimension of matrix
   * @param W [out] the array to contain eigen values
   * @param Work [out] the temporary data with \c double data, whose size
   *                   is LWork.
   * @param LWork [in] the size of array Work. When JobZ is 'V', LWork takes
   *                   the value larger than 1+6N+2N^2. When JobZ is 'N',
   *                   LWork takes the value of 1+2N.
   * @param IWork [out] the temporary data with \c int data, whose size
   *                    is LIWork.
   * @param LIWork [in] the size of array IWork. When JobZ is 'V', LIWork
   *                    takes the value larger than 3+5N. When JobZ is 'N',
   *                    LIWork takes the value larger than 1.
   * @param info [out] the flag indicating if this operation is successful.
   * @return nothing
   */
  void dsyevd_(char* JobZ, char* UpLo, int* N, double* A, int* LDA,
               double* W, double* Work, int* LWork, int* IWork,
               int* LIWork, int* info);
  void ssyevd_(char* JobZ, char* UpLo, int* N, float* A, int* LDA,
               float* W, float* Work, int* LWork, int* IWork,
               int* LIWork, int*info);
  void dspevd_(char* JobZ, char* UpLo, int* N, double* AP, double* W,
               double* Z, int* LDA, double* Work, int* LWork,
               int* IWork, int* LIWork, int* info);
  void sspevd_(char* JobZ, char* UpLo, int* N, float* AP, float* W,
               float* Z, int* LDA, float* Work, int* LWork,
               int* IWork, int* LIWork, int* info);

}

#endif
