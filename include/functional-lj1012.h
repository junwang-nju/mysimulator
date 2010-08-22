
/**
 * @file functional-lj1012.h
 * @brief the functional format for Lennard-Jones 10-12 function
 *
 * This file gives the functions to calculate value and/or gradient of
 * Lennard-Jones 10-12 function. The distance and parameters are inputs
 * for the corresponding functions.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Functional_LJ1012_H_
#define _Functional_LJ1012_H_

#include "parameter-name-lj1012.h"

namespace std {

  /**
   * @brief calculate value of LJ1012-type function
   *
   * Based on the input distance information, the corresponding value of
   * LJ1012-type function is calculated. The corresponding parameters are
   * also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define LJ1012-type function
   * @param func [out] the output function value
   * @return nothing
   */
  void FuncLJ1012(const double dsq, const UniqueParameter* prm,
                  double& func) {
    double ivr2=prm[LJ1012EqRadiusSQ].d/dsq;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr2*ivr4;
    double tmd=ivr6-ivr4;
    func=prm[LJ1012EqEnergyDepth].d*ivr6*(5*tmd-ivr4);
  }

  /**
   * @brief differentiation for LJ1012-type interaction
   *
   * Based on the input distance information, the differentiation of
   * LJ1012-type function is calculated. The corresponding parameters are
   * also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define LJ1012-type function
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void DiffLJ1012(const double dsq, const UniqueParameter* prm,
                  double& diff) {
    double ivd2=1./dsq;
    double ivr2=prm[LJ1012EqRadiusSQ].d*ivd2;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr4*ivr2;
    diff=prm[LJ1012SixtyEqEnergyDepth].d*ivr6*(ivr4-ivr6)*ivd2;
  }

  /**
   * @brief function value and differentiation of LJ1012-type function
   *
   * Based on the distance information, the value and differentiation of
   * LJ1012-type function are calculated at the same time. The corresponding
   * parameters are also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array to define LJ1012-type function
   * @param func [out] the output function value
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void BothLJ1012(const double dsq, const UniqueParameter* prm,
                  double& func, double& diff) {
    double ivd2=1./dsq;
    double ivr2=prm[LJ1012EqRadiusSQ].d*ivd2;
    double ivr4=ivr2*ivr2;
    double ivr6=ivr4*ivr2;
    double tmd=ivr6-ivr4;
    func=prm[LJ1012EqEnergyDepth].d*ivr6*(5*tmd-ivr4);
    diff=-prm[LJ1012SixtyEqEnergyDepth].d*ivr6*tmd*ivd2;
  }

}

#endif

