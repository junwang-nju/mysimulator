
#ifndef _Array_Expression_Multiple_H_
#define _Array_Expression_Multiple_H_

#include "array/expression/sse-valid.h"
#include "array/expression/base/multiple.h"

namespace mysimulator {

  template <typename EA,typename EB,
            typename _vType=typename ArrayMulBase<EA,EB>::value_type,
            bool _sseFLAG=__array_expression_sse_valid<
                              EA,EB,ExpressionOperationName::Multiple>::FLAG>
  class ArrayMul {
    public:
      typedef ArrayMul<EA,EB,_vType,_sseFLAG>   Type;
      ArrayMul() = delete;
      ArrayMul(EA const&, EB const&) = delete;
      ArrayMul(const Type&) = delete;
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;
  };

  template <typename EA,typename EB>
  class ArrayMul<EA,EB,typename ArrayMulBase<EA,EB>::value_type,false>
      : public ArrayMulBase<EA,EB> {

    public:

      typedef ArrayMulBase<EA,EB>   ParentType;
      typedef typename ParentType::value_type   value_type;
      typedef ArrayMul<EA,EB,value_type,false>  Type;
      typedef unsigned int size_type;

      static const bool _is_SSE_valid;

      ArrayMul(EA const& A,EB const& B) : ParentType(A,B) {}
      ArrayMul(const Type& E) : ParentType((ParentType const&)E) {}
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

  };

  template <typename EA,typename EB>
  const bool
  ArrayMul<EA,EB,typename ArrayMulBase<EA,EB>::value_type,false>::_is_SSE_valid
      = false;

}

#include "basic/sse/value-type.h"
#include "basic/memory/aligned.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArrayMul<EA,EB,typename ArrayMulBase<EA,EB>::value_type,true>
      : public ArrayMulBase<EA,EB> {

    public:

      typedef ArrayMulBase<EA,EB>   ParentType;
      typedef typename ParentType::value_type   value_type;
      typedef ArrayMul<EA,EB,value_type,true>   Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const bool _is_SSE_valid;

      ArrayMul(EA const& A, EB const& B) : ParentType(A,B) {}
      ArrayMul(const Type& E) : ParentType((ParentType const&)E) {}
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }

  };

  template <typename EA,typename EB>
  const bool
  ArrayMul<EA,EB,typename ArrayMulBase<EA,EB>::value_type,true>::_is_SSE_valid
      = true;

}

#include "basic/sse/operation.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArrayMul<E,Intrinsic<T>,
                 typename ArrayMulBase<E,Intrinsic<T>>::value_type,true>
      : public ArrayMulBase<E,Intrinsic<T>> {

    public:

      typedef ArrayMulBase<E,Intrinsic<T>>   ParentType;
      typedef typename ParentType::value_type   value_type;
      typedef ArrayMul<E,Intrinsic<T>,value_type,true>  Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type value128_type;

      static const bool _is_SSE_valid;

    private:

      value128_type _T;

    public:

      ArrayMul(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)B))) {}
      ArrayMul(const Type& A)
        : ParentType((ParentType const&)A),
          _T(Set128<value_type>((value_type)((T)A.second()))) {}
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }
      value128_type second128() const { _T; }

  };

  template <typename E,typename T>
  const bool
  ArrayMul<E,Intrinsic<T>,
           typename ArrayMulBase<E,Intrinsic<T>>::value_type,
           true>::_is_SSE_valid = true;

  template <typename T,typename E>
  class ArrayMul<Intrinsic<T>,E,
                 typename ArrayMulBase<Intrinsic<T>,E>::value_type,true>
      : public ArrayMulBase<Intrinsic<T>,E> {

    public:

      typedef ArrayMulBase<Intrinsic<T>,E>    ParentType;
      typedef typename ParentType::value_type   value_type;
      typedef ArrayMul<Intrinsic<T>,E,value_type,true>  Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const bool _is_SSE_valid;

    private:

      value128_type _T;

    public:

      ArrayMul(Intrinsic<T> const& A,E const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)A))) {}
      ArrayMul(const Type& A)
        : ParentType((ParentType const&)A),
          _T(Set128<value_type>((value_type)((T)A.first()))) {}
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }
      value128_type first128() const { return _T; }

  };

  template <typename T,typename E>
  const bool
  ArrayMul<Intrinsic<T>,E,
           typename ArrayMulBase<Intrinsic<T>,E>::value_type,
           true>::_is_SSE_valid = true;

  template <typename EA,typename EB>
  typename
  ArrayMul<EA,EB,typename ArrayMulBase<EA,EB>::value_type,true>::value128_type
  value128(
      ArrayMul<EA,EB,typename ArrayMulBase<EA,EB>::value_type,true> const& E,
      unsigned int i) {
    return
    Mul128<typename ArrayMulBase<EA,EB>::value_type>(
                value128(E.first(),i),
                value128(E.second(),i));
  }

  template <typename E,typename T>
  typename ArrayMul<E,Intrinsic<T>,
                    typename ArrayMulBase<E,Intrinsic<T>>::value_type,
                    true>::value128_type
  value128(ArrayMul<E,Intrinsic<T>,
                    typename ArrayMulBase<E,Intrinsic<T>>::value_type,
                    true> const& A,
           unsigned int i) {
    return Mul128<typename ArrayMulBase<E,Intrinsic<T>>::value_type>(
                value128(A.first(),i),
                A.second128());
  }

  template <typename T,typename E>
  typename ArrayMul<Intrinsic<T>,E,
                    typename ArrayMulBase<Intrinsic<T>,E>::value_type,
                    true>::value128_type
  value128(ArrayMul<Intrinsic<T>,E,
                    typename ArrayMulBase<Intrinsic<T>,E>::value_type,
                    true> const& A,
           unsigned int i) {
    return Mul128<typename ArrayMulBase<Intrinsic<T>,E>::value_type>(
                A.first128(),
                value128(A.second(),i));
  }

}

#endif

