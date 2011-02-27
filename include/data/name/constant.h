
/**
 * @file constant.h
 * @brief The constants used in package
 *
 * This file defines constants used in various procedures. These definitions
 * may make the meaning of constant more clear and ease the coding. These
 * constants are defined as static to avoid errors of multiple inclusion
 * for one quantity (This may happen when part of packages are compiled
 * separately). I also omit the \a const flag to ease the conversion from
 * constant to regular variables in some procedures (such as BLAS). The
 * invariability of these constants are assured since there are no assignment
 * operations for these variables.
 *
 * @author Jun Wang (junwang.nju@gmail.com)
 * @note Presently, the constants are defined with \c double type. If
 *       some libraries prefer to \c float types and concern the operations
 *       with low-level instructions (such as the operations in GROMACS),
 *       please be careful. Maybe some other kinds of constants need to
 *       be defined.
 */

#ifndef _Constant_H_
#define _Constant_H_

namespace std {

  /**
   * @brief \c long type zero
   *
   * This is used for BLAS.
   */
  static const long   lZero=0;

  /**
   * @brief \c long type one
   *
   * This is used for BLAS.
   */
  static const long   lOne=1;

  static const long   lTwo=2;

  static const long   lFour=4;

  /**
   * @brief \c int type zero
   */
  static const int    iZero=0;

  static const int    iOne=1;
  /**
   * @brief \c int type one
   */
  static const double dOne=1.;

  static const double dNOne=-1.;

  static const float fOne=1.;

  static const float fNOne=-1.;

  /**
   * @brief \c unsigned \c int type zero
   */
  static const unsigned int   uZero=0U;

  static const unsigned int   uOne=1U;

  /**
   * @brief minimal \c double value relative to \c double type one
   *
   * This quantity is the minimum which can be added to \c double type one
   * and the result is different from one. When the valus smalled than this
   * quantity is added to \c double type one, the result would still be
   * one.
   *
   * @note this depends on the number of bits to represent a \c double value.
   */
  static const double DRelDelta=1.1107651257113993e-16;

  static const float FRelDelta=5.9604644775390625e-8;
  /**
   * @brief square root of minimal \c double type value relative to one
   */
  static const double DSqrtRelDelta=1.0539284253265965e-8;
  
  static const float FSqrtRelDelta=0.000244140625;
  /**
   * @brief the factor for golden division
   */
  static const double Gold=0.618033988749894848205;
  
  /**
   * @brief the inverse of the factor for golden division
   */
  static const double IvGold=1.618033988749894848205; 

  static const char CharEOF=static_cast<char>(26);

  static const char Endl='\n';

}

#include "operation/basic/error-op.h"

namespace std {

  template <typename T>
  const T& RelDelta() {
    Error("Unknown T-type Relative Delta");
    return static_cast<T>(0);
  }

  template <> const double& RelDelta<double>() { return DRelDelta; }
  template <> const float& RelDelta<float>() { return FRelDelta; }

  template <typename T>
  T GoldValue() {
    Error("Unknown T-type Golden Value");
    return static_cast<T>(0);
  }

  template <> double GoldValue<double>() { return Gold; }

}

#endif
