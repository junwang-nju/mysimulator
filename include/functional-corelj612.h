
/**
 * @file functional-corelj612.h
 * @brief functional format for core function with Lennard-Jone 6-12 form
 *
 * This file gives the functions to calculate value and/or gradient of
 * core function with Lennard-Jones 6-12 form. The distance and parameter
 * are inputs for the corresponding functions.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Functional_CoreLJ612_H_
#define _Functional_CoreLJ612_H_

#include "parameter-name-corelj612.h"

namespace std {

  /**
   * @brief calculate value of CoreLJ612-type function
   *
   * Based on the input distance information, the corresponding value of
   * CoreLJ612-type function is calculated. The corresponding parameters
   * are also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define CoreLJ612-type function
   * @param func [out] the output function value
   * @param nothing
   */
  void FuncCoreLJ612(const double dsq, const UniqueParameter* prm,
                     double& func) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  func=0.;
    else {
      double tmd=prm[CoreLJ612RadiusSQ].d/dsq;
      tmd*=tmd*tmd;
      func=prm[CoreLJ612EnergyDepth].d*(tmd*(tmd-2.)+1.);
    }
  }

  /**
   * @brief differentiation for CoreLJ612-type interaction
   *
   * Based on the input distance information, the differentiation of
   * CoreLJ612-type function is calculated. The corresponding parameters
   * are also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define CoreLJ612-type function
   * @param diff [out] the output differentiation value
   * @return nothing
   */
   */
  void DiffCoreLJ612(const double dsq, const UniqueParameter* prm,
                     double& diff) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  diff=0.;
    else {
      double ivd2=1./dsq;
      double tmd=prm[CoreLJ612RadiusSQ].d*ivd2;
      tmd*=tmd*tmd;
      diff=prm[CoreLJ612TwlfEnergyDepth].d*tmd*(1.-tmd)*ivd2;
    }
  }

  /**
   * @brief function value and differentiation for CoreLJ612-type function
   *
   * Based on the distance information, the value and differentiation of
   * CoreLJ612-type function are calculated at the same time. The
   * corresponding parameters are also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array to define CoreLJ612-type function
   * @param func [out] the output function value
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void BothCoreLJ612(const double dsq, const UniqueParameter* prm,
                     double& func, double& diff) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  func=diff=0.;
    else {
      double ivd2=1./dsq;
      double tmd=prm[CoreLJ612RadiusSQ].d*ivd2;
      tmd*=tmd*tmd;
      func=prm[CoreLJ612EnergyDepth].d*(tmd*(tmd-2.)+1.);
      diff=prm[CoreLJ612TwlfEnergyDepth].d*tmd*(1.-tmd)*ivd2;
    }
  }

}

#endif

