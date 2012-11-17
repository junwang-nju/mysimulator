
#ifndef _Array_Expression_Multiple_H_
#define _Array_Expression_Multiple_H_

#include "array/expression/base/multiple.h"
#include "array/expression/sse-valid.h"

namespace mysimulator {

  template <typename EA,typename EB,
            typename _vType=typename ArrayMulBase<EA,EB>::value_type,
            bool _sseFLAG=__array_expression_sse_valid<
                              EA,EB,ExpressionOperationName::Multiple>::FLAG>
  class ArrayMul {

    public:

      typedef ArrayMul<EA,EB,_vType,_sseFLAG>   Type;
      ArrayMul() = delete;
      ArrayMul(EA const&,EB const&) = delete;
      ArrayMul(const Type&) = delete;
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

  };

  template <typename EA,typename EB>
  class ArrayMul<EA,EB,typename ArrayMulBase<EA,EB>::value_type,false>
      : public ArrayMulBase<EA,EB> {

    public:

      typedef ArrayMulBase<EA,EB>   ParentType;
      typedef typename ParentType::value_type value_type;
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
#include "basic/sse/operation.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArrayMul<EA,EB,typename ArrayMulBase<EA,EB>::value_type,true>
      : public ArrayMulBase<EA,EB> {

    public:

      typedef ArrayMulBase<EA,EB>   ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayMul<EA,EB,value_type,true>   Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type value128_type;

      static const bool _is_SSE_valid;

    private:

      size_type _n128;
      size_type _n128_low;

    public:

      ArrayMul(EA const& A,EB const& B)
        : ParentType(A,B),
          _n128(A.size128()<B.size128()?A.size128():B.size128()),
          _n128_low(A.size128_low()<B.size128_low()?A.size128_low():
                                                    B.size128_low()) {}
      ArrayMul(const Type& E)
        : ParentType((ParentType const&)E), _n128(E.size128()),
          _n128_low(E.size128_low()) {}
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const { return _n128; }
      size_type size128_low() const { return _n128_low; }
      value128_type value128(size_type i) const {
        return Mul128<value_type>(ParentType::first().value128(i),
                                  ParentType::second().value128(i));
      }

  };

  template <typename EA,typename EB>
  const bool
  ArrayMul<EA,EB,typename ArrayMulBase<EA,EB>::value_type,true>::_is_SSE_valid
      = true;

  template <typename E,typename T>
  class ArrayMul<E,Intrinsic<T>,
                 typename ArrayMulBase<E,Intrinsic<T>>::value_type,true>
      : public ArrayMulBase<E,Intrinsic<T>> {

    public:

      typedef ArrayMulBase<E,Intrinsic<T>>    ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayMul<E,Intrinsic<T>,value_type,true>  Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type value128_type;

      static const bool _is_SSE_valid;

    private:

      value128_type _T;
      size_type _n128;
      size_type _n128_low;

    public:

      ArrayMul(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)B))),
          _n128(A.size128()), _n128_low(A.size128_low()) {}
      ArrayMul(const Type& A)
        : ParentType((ParentType const&)A), _T(A.second128()),
          _n128(A.size128()), _n128_low(A.size128_low()) {}
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const { return _n128; }
      size_type size128_low() const { return _n128_low; }
      value128_type second128() const { return _T; }
      value128_type value128(size_type i) const {
        return Mul128<value_type>(ParentType::first().value128(i),
                                  second128());
      }

  };

  template <typename E,typename T>
  const bool
  ArrayMul<E,Intrinsic<T>,typename ArrayMulBase<E,Intrinsic<T>>::value_type,
           true>::_is_SSE_valid = true;

  template <typename T,typename E>
  class ArrayMul<Intrinsic<T>,E,
                 typename ArrayMulBase<Intrinsic<T>,E>::value_type,true>
      : public ArrayMulBase<Intrinsic<T>,E> {

    public:

      typedef ArrayMulBase<Intrinsic<T>,E>  ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayMul<Intrinsic<T>,E,value_type,true>  Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type value128_type;

      static const bool _is_SSE_valid;

    private:

      value128_type _T;
      size_type _n128;
      size_type _n128_low;

    public:

      ArrayMul(Intrinsic<T> const& A,E const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)A))),
          _n128(B.size128()), _n128_low(B.size128_low()) {}
      ArrayMul(const Type& A)
        : ParentType((ParentType const&)A), _T(A.first128()),
          _n128(A.size128()), _n128_low(A.size128_low()) {}
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const { return _n128; }
      size_type size128_low() const { return _n128_low; }
      value128_type first128() const { return _T; }
      value128_type value128(size_type i) const {
        return Mul128<value_type>(first128(),
                                  ParentType::second().value128(i));
      }

  };

  template <typename T,typename E>
  const bool
  ArrayMul<Intrinsic<T>,E,typename ArrayMulBase<Intrinsic<T>,E>::value_type,
           true>::_is_SSE_valid = true;

}

#endif

