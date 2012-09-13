
#ifndef _Array_Expression_H_
#define _Array_Expression_H_

#include "array/container.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArrayExpression {

    public:

      typedef unsigned int size_type;
      typedef T value_type;

      size_type size() const { return static_cast<E const&>(*this).size(); }
      value_type operator[](size_type i) const {
        return static_cast<E const&>(*this)[i];
      }

      operator E&() { return static_cast<E&>(*this); }
      operator E const&() { return static_cast<const E&>(*this); }

  };

}

#endif

