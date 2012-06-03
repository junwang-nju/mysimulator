
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
   * @brief the square root of the minimal value respective to unit of \c float type
   *
   * This is the square root of the above variable \a FRelDelta
   */
  static const float FSqrtRelDelta=0.000244140625;

  /** @var DRelDelta
   * @brief the minimal value respective to unit of \c double type
   *
   * Since the storage of computer has limit size, there is a minimal
   * value \a a to realize that \f$ 1+a > 1 \f$. This variable records
   * the corresponding minimal value for \c double type.
   */
  static const double DRelDelta=1.1107651257113993e-16;
  /** @var DSqrtRelDelta
   * @brief the square root of the minimal value respective to unit of \c double type
   *
   * This is the square root of the above variable \a DRelDelta
   */
  static const double DSqrtRelDelta=1.0539284253265965e-8;

  /** @fn const T& _RelDelta()
   * @brief extract the relative delta for \c T type
   *
   * This is an interface to get the minimal delta value. For this default
   * case, a warning is given out and a default value (now \c 0) is returned.
   *
   * @tparam T the type of return data
   * @return \c 0 for this default case
   */
  template <typename T>
  const T& _RelDelta() {
    fprintf(stderr,"Unknown Type for RelDelta!\n"); return 0;
  }
  /** @fn const float& _RelDelta<float>()
   * @brief the specialization of _RelDelta related to \c float type
   *
   * it gives out the \c float -type related delta
   *
   * @return the value \a FRelDelta
   */
  template <> const float& _RelDelta<float>() { return FRelDelta; }
  /** @fn const double& _RelDelta<double>()
   * @brief the specialization of _RelDelta related to \c double type
   *
   * it gives out the \c double -type related delta
   *
   * @return the value \a DRelDelta
   */
  template <> const double& _RelDelta<double>() { return DRelDelta; }

  /** @var Golden
   * @brief the value corresponding to golden division
   *
   * The ratio of golden division is frequently used in divide-conquer
   * problems. Here define this constant for easy access. This is
   * \c double version.
   */
  static const double Golden=0.618033988749894848205;
  /** @var IvGolden
   * @brief the value corresponding to inverse of golden division
   *
   * This is the inversion of the value of golden division, namely
   * the inversion of \c Golden (\c double version).
   */
  static const double IvGolden=1.618033988749894848205;

  /** @fn const T& _Golden()
   * @brief the interface to access the ratio of golden division
   *
   * This is an interface to access the ratio of golden division. for default
   * case, a warning is given out, and return a default value (now \c 0).
   *
   * @tparam T the type of the returned data
   * @return \c 0 for default case
   */
  template <typename T>
  const T& _Golden() { fprintf(stderr,"Unknown Type for Golden!"); return 0; }

  /** @fn const double& _Golden<double>()
   * @brief specialization for \c _Golden for \c double type
   *
   * it gives out \c double -type version of the ratio of golden division.
   *
   * @return \c double version of ratio of golden division, namely \c Golden
   */
  template <> const double& _Golden<double>() { return Golden; }

}

#endif

