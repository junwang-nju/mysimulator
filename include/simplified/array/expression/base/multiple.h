
#ifndef _Array_Expression_Base_Multiple_H_
#define _Array_Expression_Base_Multiple_H_

#include "basic/expression/base.h"
#include "basic/type/selector.h"
#include "basic/type/multiple.h"
#include "array/kernel/name.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArrayMulBase
    : public __TwoMemberExpression<EA,EB,ExpressionOperationName::Multiple> {

    public:

      typedef ArrayMulBase<EA,EB> Type;
      typedef __TwoMemberExpression<EA,EB,ExpressionOperationName::Multiple>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<typename EA::value_type,
                                       typename EB::value_type,__mul>::Type
              value_type;

      static const ArrayKernelName State;

    private:

      size_type _size;

    public:

      ArrayMulBase(EA const& A,EB const& B)
        : ParentType(A,B), _size(A.size()<B.size()?A.size():B.size()) {}
      ArrayMulBase(const Type& E)
        : ParentType((ParentType const&)E), _size(E.size()) {}
      ~ArrayMulBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) *
               (value_type)(ParentType::second()[i]);
      }

  };

}

#include "basic/type/same-check.h"
#include "basic/sse/valid.h"

namespace mysimulator {

  template <typename EA,typename EB>
  const ArrayKernelName ArrayMulBase<EA,EB>::State =
      EA::State == ArrayKernelName::Direct3D ||
      EB::State == ArrayKernelName::Direct3D ?  ArrayKernelName::Direct3D :
      EA::State == ArrayKernelName::SSE && EB::State == ArrayKernelName::SSE &&
      __same_type<typename EA::value_type,typename EB::value_type>::FLAG &&
      __mono_sse_valid<typename EA::value_type>::FLAG ? ArrayKernelName::SSE :
      ArrayKernelName::Simple;

}

#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArrayMulBase<E,Intrinsic<T>>
      : public __TwoMemberExpression<E,Intrinsic<T>,
                                     ExpressionOperationName::Multiple> {

    public:

      typedef Intrinsic<T>    TType;
      typedef ArrayMulBase<E,TType>   Type;
      typedef __TwoMemberExpression<E,TType,ExpressionOperationName::Multiple>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<typename E::value_type,T,__mul>::Type
              value_type;

      static const ArrayKernelName State;

    private:

      size_type _size;

    public:

      ArrayMulBase(E const& A, TType const& B)
        : ParentType(A,B), _size(A.size()) {}
      ArrayMulBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()) {}
      ~ArrayMulBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) *
               (value_type)((T)ParentType::second());
      }

  };

  template <typename E,typename T>
  const ArrayKernelName ArrayMulBase<E,Intrinsic<T>>::State =
      E::State == ArrayKernelName::Direct3D ? ArrayKernelName::Direct3D :
      E::State == ArrayKernelName::SSE &&
      __mono_sse_valid<typename E::value_type>::FLAG &&
      __same_type<typename ArrayMulBase<E,Intrinsic<T>>::value_type,
                  typename E::value_type>::FLAG ? ArrayKernelName::SSE :
      ArrayKernelName::Simple;

  template <typename T,typename E>
  class ArrayMulBase<Intrinsic<T>,E>
      : public __TwoMemberExpression<Intrinsic<T>,E,
                                     ExpressionOperationName::Multiple> {

    public:

      typedef Intrinsic<T>    TType;
      typedef ArrayMulBase<TType,E>   Type;
      typedef __TwoMemberExpression<TType,E,ExpressionOperationName::Multiple>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<T,typename E::value_type,__mul>::Type
              value_type;

      static const ArrayKernelName State;

    private:

      size_type _size;

    public:

      ArrayMulBase(Intrinsic<T> const& A,E const& B)
        : ParentType(A,B), _size(B.size()) {}
      ArrayMulBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()) {}
      ~ArrayMulBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)((T)ParentType::first()) *
               (value_type)(ParentType::second()[i]);
      }

  };

  template <typename T,typename E>
  const ArrayKernelName ArrayMulBase<Intrinsic<T>,E>::State =
      E::State == ArrayKernelName::Direct3D ? ArrayKernelName::Direct3D :
      E::State == ArrayKernelName::SSE &&
      __mono_sse_valid<typename E::value_type>::FLAG &&
      __same_type<typename ArrayMulBase<Intrinsic<T>,E>::value_type,
                  typename E::value_type>::FLAG ? ArrayKernelName::SSE :
      ArrayKernelName::Simple;

}

#endif

