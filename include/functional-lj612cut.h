
/**
 * @file functional-lj612cut.h
 * @brief The functional format for Lennard-Jones 6-12 function with cutoff
 *
 * This file gives the functions to calculate value and/or gradient of
 * Lennard-Jones 6-12 function with cutoff. The distance and parameters
 * are inputs for the corresponding functions.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 */

#ifndef _Functional_LJ612Cut_H_
#define _Functional_LJ612Cut_H_

#include "parameter-name-lj612cut.h"
#include <cmath>

namespace std {

  /**
   * @brief calculate value of LJ612-type function with cutoff
   *
   * Based on the input distance infromation, the corresponding value of
   * LJ612-type function with cutoff is calculated. The corresponding
   * parameters are also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters define the concerend function
   * @param func [out] the output function value
   * @return nothing
   */
  void FuncLJ612Cut(const double dsq, const UniqueParameter* prm,
                    double& func) {
    if(dsq>prm[LJ612CutCutRSQ].d)   func=0.;
    else {
      double d=sqrt(dsq);
      double d6=dsq*dsq*dsq;
      double ivr6=prm[LJ612CutRealSigma6].d/d6;
      func=prm[LJ612CutRealStrength].d*ivr6*(ivr6-2.)-prm[LJ612CutVc].d
          -prm[LJ612CutKc].d*(d-prm[LJ612CutCutR].d);
    }
  }

  /**
   * @brief differentiation for LJ612-type interaction with cutoff
   *
   * Based on the input distance information, the differentiation of LJ612
   * function with cutoff is calculated. The corresponding parameters are
   * also included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters define the concerend function
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void DiffLJ612Cut(const double dsq, const UniqueParameter* prm,
                    double& diff) {
    if(dsq>prm[LJ612CutCutRSQ].d)   diff=0.;
    else {
      double d=sqrt(dsq);
      double ivd=1./d;
      double ivd2=1./dsq;
      double id6=ivd2*ivd2*ivd2;
      double ivr6=prm[LJ612CutRealSigma6].d*id6;
      diff=prm[LJ612CutTwlfRealStrength].d*ivr6*(1.-ivr6)*ivd2
          -prm[LJ612CutKc].d*ivd;
    }
  }

  /**
   * @brief function value and differentiation for LJ612 function with cutoff
   *
   * Based on the input distance information, the value and differentiation
   * of LJ612 function with cutoff are calculated at the same time The
   * corresponding parameters are included for flexibility.
   *
   * @param dsq [in] the square of distance
   * @param prm [in] the array of parameters define the concerend function
   * @param func [out] the output function value
   * @param diff [out] the output differentiation value
   * @return nothing
   */
  void BothLJ612Cut(const double dsq, const UniqueParameter* prm,
                    double& func, double& diff) {
    if(dsq>prm[LJ612CutCutRSQ].d)   func=diff=0.;
    else {
      double d=sqrt(dsq);
      double ivd=1./d;
      double ivd2=1./dsq;
      double id6=ivd2*ivd2*ivd2;
      double ivr6=prm[LJ612CutRealSigma6].d*id6;
      func=prm[LJ612CutRealStrength].d*ivr6*(ivr6-2.)-prm[LJ612CutVc].d
          -prm[LJ612CutKc].d*(d-prm[LJ612CutCutR].d);
      diff=prm[LJ612CutTwlfRealStrength].d*ivr6*(1.-ivr6)*ivd2
          -prm[LJ612CutKc].d*ivd;
    }
  }

}

#endif

