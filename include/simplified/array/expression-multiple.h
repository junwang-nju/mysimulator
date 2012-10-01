
#ifndef _Array_Expression_Multiple_H_
#define _Array_Expression_Multiple_H_

namespace mysimulator {

  template <typename EA,typename EB>
  class ArrayMul {};

}

#include "array/expression.h"
#include "basic/type/multiple.h"
#include "basic/type/selector.h"

namespace mysimulator {

  enum class ArrayFormat;
  template <typename T,ArrayFormat AF> class Array;

  template <typename T1,ArrayFormat AF1,typename T2,ArrayFormat AF2>
  class ArrayMul<Array<T1,AF1>,Array<T2,AF2>>
    : public ArrayExpression<ArrayMul<Array<T1,AF1>,Array<T2,AF2>>,
                             typename __dual_selector<T1,T2,__mul_flag>::Type> {

    public:

      typedef ArrayMul<Array<T1,AF1>,Array<T2,AF2>>   Type;
      typedef typename __dual_selector<T1,T2,__mul_flag>::Type  value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef T1* pointer1;
      typedef T2* pointer2;

    private:

      Array<T1,AF1> const& _A;
      Array<T2,AF2> const& _B;

    public:

      ArrayMul(Array<T1,AF1> const& A,Array<T2,AF2> const& B) : _A(A),_B(B) {}
      operator bool() const { return (bool)_A && (bool)_B; }
      size_type size() const { return _A.size()<_B.size()?_A>size():_B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A[i] * value_type(_B[i]);
      }
      pointer1 first() const { return _A.head(); }
      pointer2 second() const { return _B.head(); }

  };

  template <typename EA,typename EB>
  ArrayMul<EA,EB> const operator*(const EA& a, const EB& b) {
    return ArrayMul<EA,EB>(a,b);
  }

}

#endif

