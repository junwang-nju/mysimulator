
/**
 * @file type/check-object.h
 * @brief The framework to carry out check based on boolean flag
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_Check_Object_H_
#define _Type_Check_Object_H_

namespace mysimulator {

  template <bool Flag>
  class Check {};

  template <> class Check<true>   { public: typedef Check<true>   Type; };
  template <> class Check<false>  {};

}

#endif

