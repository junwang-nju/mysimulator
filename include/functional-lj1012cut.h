
/**
 * @file functional-lj1012cut.h
 * @brief the functional format for Lennard-Jones 10-12 function with cutoff
 *
 * This file gives the functions to calculate value and/or gradient of
 * Lennard-Jones 10-12 function with cutoff. The distance and parameters
 * are inputs for the corresponding functions.
 *
 * @author Jun Wnag (junwang.nju@gmail.com)
 */
#ifndef _Functional_LJ1012Cut_H_
#define _Functional_LJ1012Cut_H_

#include "parameter-name-lj1012cut.h"
#include <cmath>

namespace std {

  /**
   * @brief calculate value of LJ1012-type function with cutoff
   *
   * Based on the input distance information, the corresponding value of
   * LJ1012-type function with cutoff is calculated. The corresponding
   * parameters are also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define the concerned function
   * @param func [out] the output function value
   * @return nothing
   */
  void FuncLJ1012Cut(const double dsq, const UniqueParameter* prm,
                     double& func) {
    if(dsq>prm[LJ1012CutCutRSQ].d)  func=0.;
    else {
      double d=sqrt(dsq);
      double ivr2=prm[LJ1012CutRealRadiusSQ].d/dsq;
      double ivr4=ivr2*ivr2;
      double ivr6=ivr2*ivr4;
      double tmd=ivr6-ivr4;
      func=prm[LJ1012CutRealEnergyDepth].d*ivr6*(5*tmd-ivr4);
      func-=prm[LJ1012CutVc].d;
      func-=prm[LJ1012CutKc].d*(d-prm[LJ1012CutCutR].d);
    }
  }

  /**
   * @brief differentiation for LJ1012-type interaction with cutoff
   *
   * Based on the input distance information, the differentiation of LJ1012
   * function with cutoff is calculated. The corresponding parameters are
   * also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define the concerned function
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void DiffLJ1012Cut(const double dsq, const UniqueParameter* prm,
                     double& diff) {
    if(dsq>prm[LJ1012CutCutRSQ].d)  diff=0.;
    else {
      double d=sqrt(dsq);
      double ivd2=1./dsq;
      double ivd=1./d;
      double ivr2=prm[LJ1012CutRealRadiusSQ].d*ivd2;
      double ivr4=ivr2*ivr2;
      double ivr6=ivr2*ivr4;
      diff=prm[LJ1012CutSixtyRealEnergyDepth].d*ivr6*(ivr4-ivr6)*ivd2;
      diff-=prm[LJ1012CutKc].d*ivd;
    }
  }

  /**
   * @brief function value and differentiation for LJ1012 function with cutoff
   *
   * Based on the input distance information, the value and differentiation
   * of LJ1012 function with cutoff are calculated at the same time. The
   * corresponding parameters are included for flexibility.
   * 
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters to define the concerned function
   * @param func [out] the output function value
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void BothLJ1012Cut(const double dsq, const UniqueParameter* prm,
                     double& func, double& diff) {
    if(dsq>prm[LJ1012CutCutRSQ].d)  func=diff=0.;
    else {
      double d=sqrt(dsq);
      double ivd2=1./dsq;
      double ivd=1./d;
      double ivr2=prm[LJ1012CutRealRadiusSQ].d*ivd2;
      double ivr4=ivr2*ivr2;
      double ivr6=ivr2*ivr4;
      double tmd=ivr6-ivr4;
      func=prm[LJ1012CutRealEnergyDepth].d*ivr6*(5*tmd-ivr4);
      func-=prm[LJ1012CutVc].d;
      func-=prm[LJ1012CutKc].d*(d-prm[LJ1012CutCutR].d);
      diff=-prm[LJ1012CutSixtyRealEnergyDepth].d*ivr6*tmd*ivd2;
      diff-=prm[LJ1012CutKc].d*ivd;
    }
  }

}

#endif

