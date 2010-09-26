
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
   * @param UpLo
   */
  void dsyevd_(char* JobZ, char* UpLo, int* N, double* A, int* LDA,
               double* W, double* Work, int* LWork, int* IWork,
               int* LIWork, int*info);
  void ssyevd_(char* JobZ, char* UpLo, int* N, float* A, int* LDA,
               float* W, float* Work, int* LWork, int* IWork,
               int* LIWork, int*info);
  void dspevd_(char* JobZ, char* UpLo, int* N, double* AP, double* W,
               double* Z, int* LDA, double* Work, int* LWork,
               int* IWork, int* LIWork, int* info);
  void sspevd_(char* JobZ, char* UpLo, int* N, flaot* AP, float* W,
               float* Z, int* LDA, float* Work, int* LWork,
               int* IWork, int* LIWork, int* info);

}

#endif
