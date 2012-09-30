
#ifndef _Array_Expression_Substract_H_
#define _Array_Expression_Substract_H_

namespace mysimulator {

  template <typename EA,typename EB>
  class ArraySubstract {};

}

#include "basic/type/substract.h"
#include "basic/type/selector.h"
#include "array/expression.h"

namespace mysimulator {

  enum class ArrayFormat;
  template <typename T,ArrayFormat AF> class Array;

  template <typename T1,ArrayFormat AF1,typename T2,ArrayFormat AF2>
  class ArraySubstract<Array<T1,AF1>,Array<T2,AF2>>
      : public ArrayExpression<
                  ArraySubstract<Array<T1,AF1>,Array<T2,AF2>>,
                  typename __dual_selector<T1,T2,__substract_flag>::Type> {

    public:

      typedef ArraySubstract<Array<T1,AF1>,Array<T2,AF2>>   Type;
      typedef typename __dual_selector<T1,T2,__substract_flag>::Type
              value_type;
      typedef ArrayExpression<Type,value_type>    ParentType;
      typedef unsigned int size_type;
      typedef T1* pointer1;
      typedef T2* pointer2;

    private:

      Array<T1,AF1> const& _A;
      Array<T2,AF2> const& _B;

    public:

      ArraySubstract(Array<T1,AF1> const& A, Array<T2,AF2> const& B)
          : _A(A), _B(B) {}
      operator bool() const { return (bool)_A && (bool)_B; }
      size_type size() const { return _A.size()<_B.size()?_A.size():_B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size());   return _A[i]-_B[i];
      }
      pointer1 first()  const { return _A.head(); }
      pointer2 second() const { return _B.head(); }

  };

  template <typename EA,typename EB>
  ArraySubstract<EA,EB> const operator-(EA const& a, EB const& b) {
    return ArraySubstract<EA,EB>(a,b);
  }

}

#endif

