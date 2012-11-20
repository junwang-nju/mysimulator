
#ifndef _Array_Expression_Divide_H_
#define _Array_Expression_Divide_H_

#include "array/expression/base/divide.h"

namespace mysimulator {

  template <typename EA,typename EB,
            typename _vType=typename ArrayDivBase<EA,EB>::value_type,
            ArrayKernelName _state=ArrayDivBase<EA,EB>::Kernel>
  class ArrayDiv {

    public:

      typedef ArrayDivBase<EA,EB> ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayDiv<EA,EB,_vType,_state>   Type;
      typedef unsigned int size_type;

      ArrayDiv(EA const& A,EB const& B) : ParentType(A,B) {}
      ArrayDiv(const Type& E) : ParentType((ParentType const&)E) {}
      ~ArrayDiv() {}
      Type& operator=(const Type&) = delete;

  };

}

#include "basic/sse/value-type.h"
#include "basic/sse/operation.h"

namespace mysimulator {

  template <typename EA,typename EB,typename vT>
  class ArrayDiv<EA,EB,vT,ArrayKernelName::SSE> : public ArrayDivBase<EA,EB> {

    public:

      typedef ArrayDivBase<EA,EB>   ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayDiv<EA,EB,vT,ArrayKernelName::SSE>   Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

    private:

      size_type _n128;
      size_type _n128_low;

    public:

      ArrayDiv(EA const& A, EB const& B)
        : ParentType(A,B),
          _n128(A.size128()<B.size128()?A.size128():B.size128()),
          _n128_low(A.size128_low()<B.size128_low()?A.size128_low():
                                                    B.size128_low()) {}
      ArrayDiv(const Type& E)
        : ParentType((ParentType const&)E), _n128(E.size128()),
          _n128_low(E.size128_low()) {}
      ~ArrayDiv() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const { return _n128; }
      size_type size128_low() const { return _n128_low; }
      value128_type value128(size_type i) const {
        return Div128<value_type>(ParentType::first().value128(i),
                                  ParentType::second().value128(i));
      }

  };

  template <typename E,typename T,typename vT>
  class ArrayDiv<E,Intrinsic<T>,vT,ArrayKernelName::SSE>
      : public ArrayDivBase<E,Intrinsic<T>> {

    public:

      typedef ArrayDivBase<E,Intrinsic<T>>  ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayDiv<E,Intrinsic<T>,vT,ArrayKernelName::SSE> Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

    private:

      value128_type _T;
      size_type _n128;
      size_type _n128_low;

    public:

      ArrayDiv(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)B))),
          _n128(A.size128()), _n128_low(A.size128_low()) {}
      ArrayDiv(const Type& A)
        : ParentType((ParentType const&)A), _T(A.second128()),
          _n128(A.size128()), _n128_low(A.size128_low()) {}
      ~ArrayDiv() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const { return _n128; }
      size_type size128_low() const { return _n128_low; }
      value128_type second128() const { return _T; }
      value128_type value128(size_type i) const {
        return Div128<value_type>(ParentType::first().value128(i),
                                  second128());
      }

  };

  template <typename T,typename E,typename vT>
  class ArrayDiv<Intrinsic<T>,E,vT,ArrayKernelName::SSE>
      : public ArrayDivBase<Intrinsic<T>,E> {

    public:

      typedef ArrayDivBase<Intrinsic<T>,E>  ParentType;
      typedef typename ParentType::value_type value_type;
      typedef ArrayDiv<Intrinsic<T>,E,vT,ArrayKernelName::SSE>  Type;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

    private:

      value128_type _T;
      size_type _n128;
      size_type _n128_low;

    public:

      ArrayDiv(Intrinsic<T> const& A,E const& B)
        : ParentType(A,B), _T(Set128<value_type>((value_type)((T)A))),
          _n128(B.size128()), _n128_low(B.size128_low()) {}
      ArrayDiv(const Type& A)
        : ParentType((ParentType const&)A), _T(A.first128()),
          _n128(A.size128()), _n128_low(A.size128_low()) {}
      ~ArrayDiv() {}
      Type& operator=(const Type&) = delete;

      size_type size128() const { return _n128; }
      size_type size128_low() const { return _n128_low; }
      value128_type first128() const { return _T; }
      value128_type value128(size_type i) const {
        return Div128<value_type>(first128(),
                                  ParentType::second().value128(i));
      }

  };

}

#endif

