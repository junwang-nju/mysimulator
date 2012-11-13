
#ifndef _Array_Expression_Substract_H_
#define _Array_Expression_Substract_H_

#include "array/expression/sse-valid.h"
#include "array/expression/base/substract.h"

namespace mysimulator {

  template <typename EA,typename EB,
            typename _vType=typename ArraySubBase<EA,EB>::value_type,
            bool _sseFLAG=__array_expression_sse_valid<
                              EA,EB,ExpressionOperationName::Substract>::FLAG>
  class ArraySub {

    public:

      typedef ArraySub<EA,EB,_vType,_sseFLAG>   Type;

      ArraySub() = delete;
      ArraySub(EA const&, EB const&) = delete;
      ArraySub(const Type&) = delete;
      ~ArraySub() {}
      Type& operator=(const Type&) = delete;

  };

  template <typename EA,typename EB>
  class ArraySub<EA,EB,typename ArraySubBase<EA,EB>::value_type,false>
      : public ArraySubBase<EA,EB> {

    public:

      typedef ArraySubBase<EA,EB>   ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArraySub<EA,EB,value_type,false>  Type;
      typedef unsigned int size_type;

      static const bool _is_SSE_valid;

      ArraySub(EA const& A, EB const& B) : ParentType(A,B) {}
      ArraySub(const Type& E) : ParentType((ParentType const&)E) {}
      ~ArraySub() {}
      Type& operator=(const Type&) = delete;

  };

  template <typename EA,typename EB>
  const bool
  ArraySub<EA,EB,typename ArraySubBase<EA,EB>::value_type,false>::_is_SSE_valid
      = false;

}

#include "basic/sse/value-type.h"
#include "basic/memory/aligned.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArraySub<EA,EB,typename ArraySubBase<EA,EB>::value_type,true>
      : public ArraySubBase<EA,EB> {

    public:

      typedef ArraySubBase<EA,EB>   ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArraySub<EA,EB,value_type,true>   Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const bool _is_SSE_valid;

      ArraySub(EA const& A,EB const& B) : ParentType(A,B) {}
      ArraySub(const Type& E) : ParentType((ParentType const&)E) {}
      ~ArraySub() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }

  };

  template <typename EA,typename EB>
  const bool
  ArraySub<EA,EB,typename ArraySubBase<EA,EB>::value_type,true>::_is_SSE_valid
      = true;

}

#include "basic/sse/operation.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArraySub<E,Intrinsic<T>,
                 typename ArraySubBase<E,Intrinsic<T>>::value_type,true>
      : public ArraySubBase<E,Intrinsic<T>> {

    public:

      typedef ArraySubBase<E,Intrinsic<T>>    ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArraySub<E,Intrinsic<T>,value_type,true>    Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const bool _is_SSE_valid;

    private:

      value128_type _T;

    public:

      ArraySub(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)B))) {}
      ArraySub(const Type& A)
        : ParentType((ParentType const&)A),
          _T(Set128<value_type>((value_type)((T)A.second()))) {}
      ~ArraySub() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }
      value128_type second128() const { return _T; }

  };

  template <typename E,typename T>
  const bool
  ArraySub<E,Intrinsic<T>,
           typename ArraySubBase<E,Intrinsic<T>>::value_type,
           true>::_is_SSE_valid = true;

  template <typename T,typename E>
  class ArraySub<Intrinsic<T>,E,
                 typename ArraySubBase<Intrinsic<T>,E>::value_type,true>
      : public ArraySubBase<Intrinsic<T>,E> {

    public:

      typedef ArraySubBase<Intrinsic<T>,E>    ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArraySub<Intrinsic<T>,E,value_type,true>    Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const bool _is_SSE_valid;

    private:

      value128_type _T;

    public:

      ArraySub(Intrinsic<T> const& A, E const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)A))) {}
      ArraySub(const Type& A)
        : ParentType((ParentType const&)A),
          _T(Set128<value_type>((value_type)((T)A.first()))) {}
      ~ArraySub() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }
      value128_type first128() const { return _T; }

  };

  template <typename T,typename E>
  const bool
  ArraySub<Intrinsic<T>,E,
           typename ArraySubBase<Intrinsic<T>,E>::value_type,
           true>::_is_SSE_valid = true;

  template <typename EA,typename EB>
  typename
  ArraySub<EA,EB,typename ArraySubBase<EA,EB>::value_type,true>::value128_type
  value128(
      ArraySub<EA,EB,typename ArraySubBase<EA,EB>::value_type,true> const& E,
      unsigned int i) {
    return
    Sub128<typename ArraySubBase<EA,EB>::value_type>(
                value128(E.first(),i),
                value128(E.second(),i));
  }

  template <typename E,typename T>
  typename ArraySub<E,Intrinsic<T>,
                    typename ArraySubBase<E,Intrinsic<T>>::value_type,
                    true>::value128_type
  value128(ArraySub<E,Intrinsic<T>,
                    typename ArraySubBase<E,Intrinsic<T>>::value_type,
                    true> const& A,
           unsigned int i) {
    return Sub128<typename ArraySubBase<E,Intrinsic<T>>::value_type>(
                value128(A.first()),
                A.second128());
  }

  template <typename T,typename E>
  typename ArraySub<Intrinsic<T>,E,
                    typename ArraySubBase<Intrinsic<T>,E>::value_type,
                    true>::value128_type
  value128(ArraySub<Intrinsic<T>,E,
                    typename ArraySubBase<Intrinsic<T>,E>::value_type,
                    true> const& A,
           unsigned int i) {
    return Sub128<typename ArraySubBase<Intrinsic<T>,E>::value_type>(
                A.first128(),
                value128(A.second()));
  }

}

#endif

