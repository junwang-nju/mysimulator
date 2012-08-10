
/**
 * @file type/is-numeric-object.h
 * @brief the class to check if an object is related to numeric operation
 *
 * In simulations, the numeric operations could only be applied to some certain
 * objects. To avoid incorrect usage of numeric operations, we need a check
 * if an object is compatible to the numeric operations. This file implements
 * the related objects.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsNumericObject_H_
#define _Type_IsNumericObject_H_

#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T>
  class IsNumericObjectFlag { public: static const bool Flag; };

  template <typename T>
  const bool IsNumericObjectFlag<T>::Flag=IsNumericFlag<T>::Flag;

  template <typename T> class ArrayNumeric;
  template <typename T>
  class IsNumericObjectFlag<ArrayNumeric<T> > {
    public: static const bool Flag;
  };

  template <typename T>
  const bool IsNumericObjectFlag<ArrayNumeric<T> >::Flag=
    IsNumericObjectFlag<T>::Flag;

  template <typename T> class Array2DNumeric;
  template <typename T>
  class IsNumericObjectFlag<Array2DNumeric<T> > {
    public: static const bool Flag;
  };

  template <typename T>
  const bool IsNumericObjectFlag<Array2DNumeric<T> >::Flag=
    IsNumericObjectFlag<T>::Flag;

  union Unique64Bit;
  template <> const bool IsNumericObjectFlag<Unique64Bit>::Flag=true;

  union Unique128Bit;
  template <> const bool IsNumericObjectFlag<Unique128Bit>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsNumericObject {
    public:
      typedef typename Check<IsNumericObjectFlag<T>::Flag>::Type Type;
  };

}

#endif

