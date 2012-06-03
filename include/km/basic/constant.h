
/**
 * @file basic/constant.h
 * @brief some constants of basic type
 *
 * some constants are widely used in simulations (such as minimization or
 * dynamics simulation). This file includes the definitions of the constants
 * and some related interfaces to access them.
 *
 * @author Jun | junwang@gmail.com
 */

#ifndef _Basic_Constant_H_
#define _Basic_Constant_H_

namespace mysimulator {

  /** @var FRelDelta
   * @brief the minimal value respective to unit of \c float type
   *
   * Since the storage of computer has limit size, there is a minimal
   * value \a a to realize that \f$ 1+a > 1 \f$. This variable records
   * the corresponding minimal value for \c float type.
   */
  static const float FRelDelta=5.9604644775390625e-8;
  /** @var FSqrtRelDelta
   * @brief the square root of the minimal value respective to unit of \c float type */
  static const float FSqrtRelDelta=0.000244140625;

  static const double DRelDelta=1.1107651257113993e-16;
  static const double DSqrtRelDelta=1.0539284253265965e-8;

  template <typename T>
  const T _RelDelta() {
    fprintf(stderr,"Unknown Type for RelDelta!\n"); return 0;
  }
  template <> const float _RelDelta<float>() { return FRelDelta; }
  template <> const double _RelDelta<double>() { return DRelDelta; }

  static const double Golden=0.618033988749894848205;
  static const double IvGolden=1.618033988749894848205;

  template <typename T>
  const T _Golden() { fprintf(stderr,"Unknown Type for Golden!"); return 0; }

  template <> const double _Golden<double>() { return Golden; }

}

#endif

