
/**
 * @file type/check-object.h
 * @brief The framework to carry out check based on boolean flag
 *
 * This file defines a class to generate a check based on boolean flag.
 * when flag is \c true, a trait type is defined, or when flag is \c false,
 * no trait are defined. This could offer a way to check the flag in
 * compiling stage.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_Check_Object_H_
#define _Type_Check_Object_H_

namespace mysimulator {

  /** @class Check
   * @brief the class as the framework for flag checking
   *
   * This is a framework class used for type checking. For default case,
   * this is a blank class with no contents.
   *
   * @tparam Flag the boolean flag to control the class content
   */
  template <bool Flag>
  class Check {};

  /**
   * @brief specialized Check with \c true flag
   *
   * This is the specialization for the class \c Check with the flag as
   * \c true. a type trait is defined. The existence of the trait is
   * the signature of this specialization.
   */
  template <> class Check<true>   {
    public:
      /** @typedef Type
       * @brief the type trait definition (with Check<true> itself)
       */
      typedef Check<true>   Type;
  };
  /**
   * @brief specialized Check with \c false flag
   *
   * This specialization does not have any contents. This is same as
   * the default case. Here it is defined explicitly for clarity.
   */
  template <> class Check<false>  {};

}

#endif

