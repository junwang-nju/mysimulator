
/**
 * @file functional-coulomb.h
 * @brief the functional format for coulomb interaction
 *
 * This file gives the functions to calculate value and/or gradient of
 * coulomb function. The distance and parameters are inputs
 * for the corresponding functions.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Functional_Coulomb_H_
#define _Functional_Coulomb_H_

#include "parameter-name-coulomb.h"
#include <cmath>

namespace std {

  /**
   * @brief calculate value of Coulomb function
   *
   * Based on the input distance information, the corresponding value
   * of Coulomb function is calculated. The corresponding parameters
   * are also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters for concerned function
   * @param func [out] the output function value
   * @return nothing
   */
  void FuncCoulomb(const double dsq, const UniqueParameter* prm,
                   double& func) {
    func=prm[CoulombStrength].d/sqrt(dsq);
  }

  /**
   * @brief differentiation for Coulomb interaction
   *
   * Based on the input distance information, the differentiation of Coulomb
   * function is calculated. The corresponding parameters are also included
   * for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters for concerned function
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void DiffCoulomb(const double dsq, const UniqueParameter* prm,
                   double& diff) {
    double d=sqrt(dsq)*dsq;
    diff=-prm[CoulombStrength].d/d;
  }

  /**
   * @brief function value and differentiation for Coulomb function
   *
   * Based on the input distance information, the value and differentiation
   * of Coulomb function are calculated at the same time. The corresponding
   * parameters are also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters for concerned function
   * @param func [out] the output function value
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void BothCoulomb(const double dsq, const UniqueParameter* prm,
                   double& func, double& diff) {
    double d=sqrt(dsq);
    func=prm[CoulombStrength].d/d;
    diff=-func/dsq;
  }

}

#endif

