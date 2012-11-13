
#ifndef _Array_Expression_Sum_H_
#define _Array_Expression_Sum_H_

#include "array/expression/sse-valid.h"
#include "array/expression/base/sum.h"

namespace mysimulator {

  template <typename EA,typename EB,
            typename _vType=typename ArraySumBase<EA,EB>::value_type,
            bool _sseFLAG=__array_expression_sse_valid<
                              EA,EB,ExpressionOperationName::Sum>::FLAG>
  class ArraySum {
    public:
      typedef ArraySum<EA,EB,_vType,_sseFLAG>    Type;
      ArraySum() = delete;
      ArraySum(EA const&,EB const&) = delete;
      ArraySum(const Type&) = delete;
      ~ArraySum() {}
      Type& operator=(const Type&) = delete;
  };

  template <typename EA,typename EB>
  class ArraySum<EA,EB,typename ArraySumBase<EA,EB>::value_type,false>
      : public ArraySumBase<EA,EB> {

    public:

      typedef ArraySumBase<EA,EB>     ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArraySum<EA,EB,value_type,false>   Type;
      typedef unsigned int size_type;

      static const bool _is_SSE_valid;

      ArraySum(EA const& A,EB const& B) : ParentType(A,B) {}
      ArraySum(const Type& E) : ParentType((ParentType const&)E) {}
      ~ArraySum() {}
      Type& operator=(const Type&) = delete;

  };

  template <typename EA,typename EB>
  const bool
  ArraySum<EA,EB,typename ArraySumBase<EA,EB>::value_type,false>::_is_SSE_valid
      = false;

}

#include "basic/sse/value-type.h"
#include "basic/memory/aligned.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArraySum<EA,EB,typename ArraySumBase<EA,EB>::value_type,true>
      : public ArraySumBase<EA,EB> {

    public:

      typedef ArraySumBase<EA,EB>     ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArraySum<EA,EB,value_type,true>    Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const bool _is_SSE_valid;

      ArraySum(EA const& A,EB const& B) : ParentType(A,B) {}
      ArraySum(const Type& E) : ParentType((ParentType const&)E) {}
      ~ArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }

  };

  template <typename EA,typename EB>
  const bool
  ArraySum<EA,EB,typename ArraySumBase<EA,EB>::value_type,true>::_is_SSE_valid
      = true;

}

#include "basic/sse/operation.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArraySum<E,Intrinsic<T>,
                 typename ArraySumBase<E,Intrinsic<T>>::value_type,true>
      : public ArraySumBase<E,Intrinsic<T>> {

    public:

      typedef ArraySumBase<E,Intrinsic<T>>    ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArraySum<E,Intrinsic<T>,value_type,true>   Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const bool _is_SSE_valid;

    private:

      value128_type _T;

    public:

      ArraySum(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)B))) {}
      ArraySum(const Type& A)
        : ParentType((ParentType const&)A),
          _T(Set128<value_type>((value_type)((T)A.second()))) {}
      ~ArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }
      value128_type second128() const { return _T; }

  };

  template <typename E,typename T>
  const bool
  ArraySum<E,Intrinsic<T>,
           typename ArraySumBase<E,Intrinsic<T>>::value_type,
           true>::_is_SSE_valid = true;

  template <typename T,typename E>
  class ArraySum<Intrinsic<T>,E,
                 typename ArraySumBase<Intrinsic<T>,E>::value_type,true>
      : public ArraySumBase<Intrinsic<T>,E> {

    public:

      typedef ArraySumBase<Intrinsic<T>,E>    ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArraySum<Intrinsic<T>,E,value_type,true>   Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const bool _is_SSE_valid;

    private:

      value128_type _T;

    public:

      ArraySum(Intrinsic<T> const& A,E const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)A))) {}
      ArraySum(const Type& A)
        : ParentType((ParentType const&)A),
          _T(Set128<value_type>((value_type)((T)A.first()))) {}
      ~ArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }
      value128_type first128() const { return _T; }

  };

  template <typename T,typename E>
  const bool
  ArraySum<Intrinsic<T>,E,
           typename ArraySumBase<Intrinsic<T>,E>::value_type,
           true>::_is_SSE_valid = true;

  template <typename EA,typename EB>
  typename
  ArraySum<EA,EB,typename ArraySumBase<EA,EB>::value_type,true>::value128_type
  value128(
      ArraySum<EA,EB,typename ArraySumBase<EA,EB>::value_type,true> const& E,
      unsigned int i) {
    return
    Sum128<typename ArraySumBase<EA,EB>::value_type>(
                value128(E.first(),i),
                value128(E.second(),i));
  }

  template <typename E,typename T>
  typename ArraySum<E,Intrinsic<T>,
                    typename ArraySumBase<E,Intrinsic<T>>::value_type,
                    true>::value128_type
  value128(ArraySum<E,Intrinsic<T>,
                    typename ArraySumBase<E,Intrinsic<T>>::value_type,
                    true> const& A,
           unsigned int i) {
    return Sum128<typename ArraySumBase<E,Intrinsic<T>>::value_type>(
                value128(A.first()),
                A.second128());
  }

  template <typename T,typename E>
  typename ArraySum<Intrinsic<T>,E,
                    typename ArraySumBase<Intrinsic<T>,E>::value_type,
                    true>::value128_type
  value128(ArraySum<Intrinsic<T>,E,
                    typename ArraySumBase<Intrinsic<T>,E>::value_type,
                    true> const& A,
           unsigned int i) {
    return Sum128<typename ArraySumBase<Intrinsic<T>,E>::value_type>(
                A.first128(),
                value128(A.second()));
  }

}

#endif

