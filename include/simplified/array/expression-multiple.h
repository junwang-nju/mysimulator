
#ifndef _Array_Expression_Multiple_H_
#define _Array_Expression_Multiple_H_

#include "array/expression.h"
#include "basic/type/multiple.h"
#include "basic/type/selector.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArrayMul
    : public ArrayExpression<
                ArrayMul<EA,EB>,
                typename __dual_selector<typename EA::value_type,
                                         typename EB::value_type,
                                         __mul_flag>::Type> {

    public:

      static_assert(!__intrinsic_flag<EA>::FG && !__intrinsic_flag<EB>::FG,
                    "For intrinsic type, please use Intrinsic<T>!\n");

      typedef ArrayMul<EA,EB>   Type;
      typedef
        typename __dual_selector<typename EA::value_type,
                                 typename EB::value_type,__mul_flag>::Type
        value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef EA const& const_referenceA;
      typedef EB const& const_referenceB;

      static const __ArrayOperationName OpName;

    private:

      const_referenceA _A;
      const_referenceB _B;

    public:

      ArrayMul(const_referenceA A,const_referenceB B) : _A(A),_B(B) {}
      ~ArrayMul() {}

      operator bool() const { return (bool)_A && (bool)_B; }
      size_type size() const { return _A.size()<_B.size()?_A.size():_B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)_A[i] * (value_type)_B[i];
      }
      const_referenceA first()  const { return _A; }
      const_referenceB second() const { return _B; }

  };

  template <typename EA,typename EB>
  const __ArrayOperationName ArrayMul<EA,EB>::OpName=
        __ArrayOperationName::Multiple;

  template <typename EA,typename EB>
  ArrayMul<EA,EB> const operator*(const EA& a, const EB& b) {
    return ArrayMul<EA,EB>(a,b);
  }

  /// the specialization for intrinsic data in multiple are not implemented.

}

#include "basic/intrinsic.h"

namespace mysimulator {

  template <typename T,typename E>
  class ArrayMul<Intrinsic<T>,E>
    : public ArrayExpression<
                ArrayMul<Intrinsic<T>,E>,
                typename __dual_selector<T,typename E::value_type,
                                         __mul_flag>::Type> {

    public:

      typedef ArrayMul<Intrinsic<T>,E>  Type;
      typedef
        typename __dual_selector<T,typename E::value_type,__mul_flag>::Type
        value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef Intrinsic<T> const& const_referenceA;
      typedef E const&            const_referenceB;

      static const __ArrayOperationName OpName;

    private:

      const_referenceA _A;
      const_referenceB _B;

    public:

      ArrayMul(const_referenceA A,const_referenceB B) : _A(A),_B(B) {}
      ~ArrayMul() {}

      operator bool() const { return (bool)_B; }
      size_type size() const { return _B.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)((T)_A) * (value_type)_B[i];
      }
      const_referenceA first()  const { return _A; }
      const_referenceB second() const { return _B; }

  };

  template <typename T,typename E>
  const __ArrayOperationName ArrayMul<Intrinsic<T>,E>::OpName=
        __ArrayOperationName::Multiple;

  template <typename E,typename T>
  class ArrayMul<E,Intrinsic<T>>
    : public ArrayExpression<
                ArrayMul<E,Intrinsic<T>>,
                typename __dual_selector<typename E::value_type,T,
                                         __mul_flag>::Type> {

    public:

      typedef ArrayMul<E,Intrinsic<T>>  Type;
      typedef
        typename __dual_selector<typename E::value_type,T,__mul_flag>::Type
        value_type;
      typedef ArrayExpression<Type,value_type>  ParentType;
      typedef unsigned int size_type;
      typedef E const&            const_referenceA;
      typedef Intrinsic<T> const& const_referenceB;

      static const __ArrayOperationName OpName;

    private:

      const_referenceA _A;
      const_referenceB _B;

    public:

      ArrayMul(const_referenceA A,const_referenceB B) : _A(A),_B(B) {}
      ~ArrayMul() {}

      operator bool() const { return (bool)_A; }
      size_type size() const { return _A.size(); }
      value_type operator[](size_type i) const {
        assert(i<size()); return (value_type)((T)_B) * (value_type)_A[i];
      }
      const_referenceA first()  const { return _A; }
      const_referenceB second() const { return _B; }

  };

  template <typename E,typename T>
  const __ArrayOperationName ArrayMul<E,Intrinsic<T>>::OpName=
        __ArrayOperationName::Multiple;

}

#endif

