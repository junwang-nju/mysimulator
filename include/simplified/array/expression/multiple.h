
#ifndef _Array_Expression_Multiple_H_
#define _Array_Expression_Multiple_H_

#include "array/expression/base/multiple.h"

namespace mysimulator {

  template <typename EA,typename EB,
            typename _vType=typename ArrayMulBase<EA,EB>::value_type,
            ArrayKernelName _state=ArrayMulBase<EA,EB>::Kernel>
  class ArrayMul : public ArrayMulBase<EA,EB> {

    public:

      typedef ArrayMulBase<EA,EB>   ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayMul<EA,EB,_vType,_state>   Type;
      typedef unsigned int size_type;

      ArrayMul(EA const& A,EB const& B) : ParentType(A,B) {}
      ArrayMul(const Type& E) : ParentType((ParentType const&)E) {}
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

  };

}

#include "basic/sse/value-type.h"
#include "basic/sse/operation.h"

namespace mysimulator {

  template <typename EA,typename EB,typename vT>
  class ArrayMul<EA,EB,vT,ArrayKernelName::SSE> : public ArrayMulBase<EA,EB> {

    public:

      typedef ArrayMulBase<EA,EB>   ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayMul<EA,EB,vT,ArrayKernelName::SSE>   Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type value128_type;

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

  template <typename E,typename T,typename vT>
  class ArrayMul<E,Intrinsic<T>,vT,ArrayKernelName::SSE>
      : public ArrayMulBase<E,Intrinsic<T>> {

    public:

      typedef ArrayMulBase<E,Intrinsic<T>>    ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayMul<E,Intrinsic<T>,vT,ArrayKernelName::SSE>  Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type value128_type;

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

  template <typename T,typename E,typename vT>
  class ArrayMul<Intrinsic<T>,E,vT,ArrayKernelName::SSE>
      : public ArrayMulBase<Intrinsic<T>,E> {

    public:

      typedef ArrayMulBase<Intrinsic<T>,E>  ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayMul<Intrinsic<T>,E,vT,ArrayKernelName::SSE>  Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type value128_type;

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

}

#endif

