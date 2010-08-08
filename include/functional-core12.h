
/**
 * @file functional-core12.h
 * @brief the function format for core-12 interaction
 *
 * This file gives the functions to calculate value and/or gradient of
 * the function with 12-order repulsive core. The distance and parameters
 * are inputs for the corresponding functions.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Functional_Core12_H_
#define _Functional_Core12_H_

#include "parameter-name-core12.h"

namespace std {

  /**
   * @brief calculate value of core-12 function
   *
   * Based on the input distance information, the corresponding value of
   * harmonic function is calculated. The corresponding parameters are also
   * included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define core-12 function
   * @param func [out] the output function value
   * @return nothing
   */
  void FuncCore12(const double dsq, const UniqueParameter* prm,
                  double& func) {
    double tmd=1./dsq;
    tmd*=tmd*tmd;
    tmd*=tmd;
    func=prm[Core12EqStrength].d*tmd;
  }

  /**
   * @brief differentiation for core-12 function
   *
   * Based on the input distance information, the differentiation of core-12
   * function is calculated. The corresponding parameters are also included
   * for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define the core-12 function
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void DiffCore12(const double dsq, const UniqueParameter* prm,
                  double& diff) {
    double tmd=1./dsq;
    double tmd2=tmd*tmd;
    tmd2*=tmd2*tmd2;
    diff=-prm[Core12TwlfEqStrength].d*tmd*tmd2;
  }

  /**
   * @brief function value and differentiation for core-12 function
   *
   * based on the input distance information, the value and differentiation
   * of core-12 function are calculated. The corresponding parameters are also
   * included for flexibility
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define core-12 function
   * @param func [out] the output function value
   * @param diff [out] the output differentiation value
   */
  void BothCore12(const double dsq, const UniqueParameter* prm,
                  double& func, double& diff) {
    double tmd=1./dsq;
    double tmd2=tmd*tmd;
    tmd2*=tmd2*tmd2;
    func=prm[Core12EqStrength].d*tmd2;
    diff=-prm[Core12TwlfEqStrength].d*tmd*tmd2;
  }

}

#endif

