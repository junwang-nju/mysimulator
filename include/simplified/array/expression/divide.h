
#ifndef _Array_Expression_Divide_H_
#define _Array_Expression_Divide_H_

#include "array/expression/sse-valid.h"
#include "array/expression/base/divide.h"

namespace mysimulator {

  template <typename EA,typename EB,
            typename _vType=typename ArrayDivBase<EA,EB>::value_type,
            bool _sseFLAG=__array_expression_sse_valid<
                              EA,EB,ExpressionOperationName::Divide>::FLAG>
  class ArrayDiv {

    public:

      typedef ArrayDiv<EA,EB,_vType,_sseFLAG> Type;

      ArrayDiv() = delete;
      ArrayDiv(EA const&, EB const&) = delete;
      ArrayDiv(const Type&) = delete;
      ~ArrayDiv() {}
      Type& operator=(const Type&) = delete;

  };

  template <typename EA,typename EB>
  class ArrayDiv<EA,EB,typename ArrayDivBase<EA,EB>::value_type,false>
      : public ArrayDivBase<EA,EB> {

    public:

      typedef ArrayDivBase<EA,EB>   ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayDiv<EA,EB,value_type,false>  Type;
      typedef unsigned int size_type;

      static const bool _is_SSE_valid;

      ArrayDiv(EA const& A, EB const& B) : ParentType(A,B) {}
      ArrayDiv(const Type& E) : ParentType((ParentType const&)E) {}
      ~ArrayDiv() {}
      Type& operator=(const Type&) = delete;

  };

  template <typename EA,typename EB>
  const bool
  ArrayDiv<EA,EB,typename ArrayDivBase<EA,EB>::value_type,false>::_is_SSE_valid
      = false;

}

#include "basic/sse/value-type.h"
#include "basic/memory/aligned.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArrayDiv<EA,EB,typename ArrayDivBase<EA,EB>::value_type,true>
      : public ArrayDivBase<EA,EB> {

    public:

      typedef ArrayDivBase<EA,EB>   ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayDiv<EA,EB,value_type,true>  Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const bool _is_SSE_valid;

      ArrayDiv(EA const& A, EB const& B) : ParentType(A,B) {}
      ArrayDiv(const Type& E) : ParentType((ParentType const&)E) {}
      ~ArrayDiv() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }

  };

  template <typename EA,typename EB>
  const bool
  ArrayDiv<EA,EB,typename ArrayDivBase<EA,EB>::value_type,true>::_is_SSE_valid
      = true;

}

#include "basic/sse/operation.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArrayDiv<E,Intrinsic<T>,
                 typename ArrayDivBase<E,Intrinsic<T>>::value_type,true>
      : public ArrayDivBase<E,Intrinsic<T>> {

    public:

      typedef ArrayDivBase<E,Intrinsic<T>>  ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayDiv<E,Intrinsic<T>,value_type,true>  Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const bool _is_SSE_valid;

    private:

      value128_type _T;

    public:

      ArrayDiv(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)B))) {}
      ArrayDiv(const Type& A)
        : ParentType((ParentType const&)A),
          _T(Set128<value_type>((value_type)((T)A.second()))) {}
      ~ArrayDiv() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }
      value128_type second128() const { return _T; }

  };

  template <typename E,typename T>
  const bool
  ArrayDiv<E,Intrinsic<T>,
           typename ArrayDivBase<E,Intrinsic<T>>::value_type,
           true>::_is_SSE_valid = true;

  template <typename T,typename E>
  class ArrayDiv<Intrinsic<T>,E,
                 typename ArrayDivBase<Intrinsic<T>,E>::value_type,true>
      : public ArrayDivBase<Intrinsic<T>,E> {

    public:

      typedef ArrayDivBase<Intrinsic<T>,E>  ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayDiv<Intrinsic<T>,E,value_type,true>  Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const bool _is_SSE_valid;

    private:

      value128_type _T;

    public:

      ArrayDiv(Intrinsic<T> const& A, E const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)A))) {}
      ArrayDiv(const Type& A)
        : ParentType((ParentType const&)A),
          _T(Set128<value_type>((value_type)((T)A.first()))) {}
      ~ArrayDiv() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const {
        return __span16<value_type>(ParentType::size());
      }
      value128_type first128() const { return _T; }

  };

  template <typename T,typename E>
  const bool
  ArrayDiv<Intrinsic<T>,E,
           typename ArrayDivBase<Intrinsic<T>,E>::value_type,
           true>::_is_SSE_valid = true;

  template <typename EA,typename EB>
  typename
  ArrayDiv<EA,EB,typename ArrayDivBase<EA,EB>::value_type,true>::value128_type
  value128(
      ArrayDiv<EA,EB,typename ArrayDivBase<EA,EB>::value_type,true> const& E,
      unsigned int i) {
    return
    Div128<typename ArrayDivBase<EA,EB>::value_type>(
                value128(E.first(),i),
                value128(E.second(),i));
  }

  template <typename E,typename T>
  typename ArrayDiv<E,Intrinsic<T>,
                    typename ArrayDivBase<E,Intrinsic<T>>::value_type,
                    true>::value128_type
  value128(
      ArrayDiv<E,Intrinsic<T>,
               typename ArrayDivBase<E,Intrinsic<T>>::value_type,true> const& A,
      unsigned int i) {
    return Div128<typename ArrayDivBase<E,Intrinsic<T>>::value_type>(
                value128(A.first(),i),
                A.second128());
  }

  template <typename T,typename E>
  typename ArrayDiv<Intrinsic<T>,E,
                    typename ArrayDivBase<Intrinsic<T>,E>::value_type,
                    true>::value128_type
  value128(
      ArrayDiv<Intrinsic<T>,E,
               typename ArrayDivBase<Intrinsic<T>,E>::value_type,true> const& A,
      unsigned int i) {
    return Div128<typename ArrayDivBase<Intrinsic<T>,E>::value_type>(
                A.first128(),
                value128(A.second(),i));
  }

}

#endif

