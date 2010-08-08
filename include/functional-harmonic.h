
/**
 * @file functional-harmonic.h
 * @brief The function format for Hamonic interaction
 *
 * This file gives the functions to calculate value and/or gradient of
 * Harmonic function. The distance and parameters are inputs for the
 * corresponding functions.
 *
 * @author Jun Wnag (junwang.nju@gamil.com)
 */
#ifndef _Functional_Harmonic_H_
#define _Functional_Harmonic_H_

#include "parameter-name-harmonic.h"
#include "unique-parameter.h"
#include <cmath>

namespace std {

  /**
   * @brief calculate value of harmonic function
   *
   * Based on the input distance information, the corresponding value of
   * harmonic function is calculated. The corresponding parameters are also
   * included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of prarameters to define harmonic function
   * @param func [out] the output function value
   * @return nothing
   */
  void FuncHarmonic(const double dsq, const UniqueParameter* prm,
                    double& func) {
    double d=sqrt(dsq);
    double Dd=d-prm[HarmonicEqLength].d;
    func=prm[HarmonicEqStrength].d*Dd*Dd;
  }

  /**
   * @brief differentiation for harmonic function
   *
   * Based on the input distance information, the differentiation of
   * harmonic function is calculated. The corresponding parameters are
   * also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define the harmonic function
   * @param diff [out] the output differentiation value
   * @return nothing
   */ 
  void DiffHarmonic(const double dsq, const UniqueParameter* prm,
                    double& diff) {
    double d=sqrt(dsq);
    double Dd=d-prm[HarmonicEqLength].d;
    diff=prm[HarmonicDualEqStrength].d*Dd/d;
  }

  /**
   * @brief function value and differentiation for harmonic function
   *
   * Based on the input distance information, the value and differentiation
   * of harmonic function are calculated. The corresponding parameters are
   * also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define harmonic function
   * @param func [out] the output function value
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void BothHarmonic(const double dsq, const UniqueParameter* prm,
                    double& func, double& diff) {
    double d=sqrt(dsq);
    double Dd=d-prm[HarmonicEqLength].d;
    double tmd=prm[HarmonicEqStrength].d*Dd;
    func=tmd*Dd;
    diff=(tmd+tmd)/d;
  }

}

#endif

