
/**
 * @file functional-lj612.h
 * @brief the functional format for Lennard-Jones 6-12 function
 *
 * This file gives the functions to calculate value and/or gradient of
 * Lennard-Jones 6-12 function. The distance and parameters are inputs
 * for the corresponding functions.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Functional_LJ612_H_
#define _Functional_LJ612_H_

#include "parameter-name-lj612.h"
#include "unique-parameter.h"

namespace std {

  /**
   * @brief calculate value of LJ612-type function
   *
   * Based on the input distance information, the corresponding value
   * of LJ612-type function is calculated. The corresponding parameters
   * are also included for flexibility
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define LJ612-type function
   * @param func [out] the output function value
   * @return nothing
   */
  void FuncLJ612(const double dsq, const UniqueParameter* prm,
                 double& func) {
    double tmd=prm[LJ612EqRadiusSQ].d/dsq;
    tmd*=tmd*tmd;
    func=prm[LJ612EqEnergyDepth].d*tmd*(tmd-2.);
  }

  /**
   * @brief differentiation for LJ612-type interaction
   *
   * Based on the input distance information, the differentiation of
   * LJ612-type function is calculated. The corresponding parameters
   * are also included for flexibility
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define LJ612-type function
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void DiffLJ612(const double dsq, const UniqueParameter* prm,
                 double& diff) {
    double ivd2=1./dsq;
    double tmd=prm[LJ612EqRadiusSQ].d*ivd2;
    tmd*=tmd*tmd;
    diff=prm[LJ612TwlfEqEnergyDepth].d*tmd*(1.-tmd)*ivd2;
  }

  /**
   * @brief function value and differentiation for LJ612-type function
   *
   * Based on the distance information, the value and differentiation of
   * LJ612-type function are calculated at the same time. The corresponding
   * parameters are also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array to define LJ612-type function
   * @param func [out] the output function value
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void BothLJ612(const double dsq, const UniqueParameter* prm,
                 double& func, double& diff) {
    double ivd2=1./dsq;
    double tmd=prm[LJ612EqRadiusSQ].d*ivd2;
    tmd*=tmd*tmd;
    func=prm[LJ612EqEnergyDepth].d*tmd*(tmd-2.);
    diff=prm[LJ612TwlfEqEnergyDepth].d*tmd*(1.-tmd)*ivd2;
  }

}

#endif

