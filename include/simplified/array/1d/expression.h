
#ifndef _Array_1D_Expression_H_
#define _Array_1D_Expression_H_

namespace mysimulator {

  template <typename E, typename ET>
  class ArrayExpression {
    public:
      typedef unsigned int size_type;

      operator bool() const { return (bool)((E const&)(*this)); }
      size_type size() const { return static_cast<E const&>(*this).size(); }
      ET operator[](size_type i) const {
        return static_cast<E const&>(*this)[i];
      }
      operator E&() { return static_cast<E&>(*this); }
      operator E const&() const { return static_cast<const E&>(*this); }
  };

  enum class __ArrayOperationName { Add, Substract, Multiple, Divide };

}

#endif

