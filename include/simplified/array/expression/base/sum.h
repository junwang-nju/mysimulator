
#ifndef _Array_Expression_Base_Sum_H_
#define _Array_Expression_Base_Sum_H_

#include "basic/expression/base.h"
#include "basic/type/selector.h"
#include "basic/type/sum.h"
#include "array/kernel/name.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArraySumBase
      : public __TwoMemberExpression<EA,EB,ExpressionOperationName::Sum> {

    public:

      typedef ArraySumBase<EA,EB>   Type;
      typedef __TwoMemberExpression<EA,EB,ExpressionOperationName::Sum>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<typename EA::value_type,
                                       typename EB::value_type,__sum>::Type
              value_type;

      static const ArrayKernelName State;

    private:

      size_type _size;

    public:

      ArraySumBase(EA const& A,EB const& B)
        : ParentType(A,B),
          _size(A.size()<B.size()?A.size():B.size()) {}
      ArraySumBase(const Type& E)
        : ParentType((ParentType const&)E),_size(E.size()) {}
      ~ArraySumBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) +
               (value_type)(ParentType::second()[i]);
      }

  };

}

#include "basic/type/same-check.h"
#include "basic/sse/valid.h"

namespace mysimulator {

  template <typename EA,typename EB>
  const ArrayKernelName ArraySumBase<EA,EB>::State =
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
  class ArraySumBase<E,Intrinsic<T>>
      : public __TwoMemberExpression<E,Intrinsic<T>,
                                     ExpressionOperationName::Sum> {

    public:

      typedef Intrinsic<T>  TType;
      typedef ArraySumBase<E,TType>   Type;
      typedef __TwoMemberExpression<E,TType,ExpressionOperationName::Sum>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<typename E::value_type,T,__sum>::Type
              value_type;

      static const ArrayKernelName State;

    private:

      size_type _size;

    public:

      ArraySumBase(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B), _size(A.size()) {}
      ArraySumBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()) {}
      ~ArraySumBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) +
               (value_type)((T)ParentType::second());
      }

  };

  template <typename E,typename T>
  const ArrayKernelName ArraySumBase<E,Intrinsic<T>>::State =
      E::State == ArrayKernelName::Direct3D ? ArrayKernelName::Direct3D :
      E::State == ArrayKernelName::SSE &&
      __mono_sse_valid<typename E::value_type>::FLAG &&
      __same_type<typename ArraySumBase<E,Intrinsic<T>>::value_type,
                  typename E::value_type>::FLAG ? ArrayKernelName::SSE :
      ArrayKernelName::Simple;

  template <typename T,typename E>
  class ArraySumBase<Intrinsic<T>,E>
      : public __TwoMemberExpression<Intrinsic<T>,E,
                                     ExpressionOperationName::Sum> {

    public:

      typedef Intrinsic<T>  TType;
      typedef ArraySumBase<TType,T>   Type;
      typedef __TwoMemberExpression<TType,E,ExpressionOperationName::Sum>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<T,typename E::value_type,__sum>::Type
              value_type;

      static const ArrayKernelName State;

    private:

      size_type _size;

    public:

      ArraySumBase(TType const& A,E const& B)
        : ParentType(A,B), _size(B.size()) {}
      ArraySumBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()) {}
      ~ArraySumBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)((T)ParentType::first()) +
               (value_type)(ParentType::second()[i]);
      }

  };

  template <typename T,typename E>
  const ArrayKernelName ArraySumBase<Intrinsic<T>,E>::State =
      E::State == ArrayKernelName::Direct3D ? ArrayKernelName::Direct3D :
      E::State == ArrayKernelName::SSE &&
      __mono_sse_valid<typename E::value_type>::FLAG &&
      __same_type<typename ArraySumBase<Intrinsic<T>,E>::value_type,
                  typename E::value_type>::FLAG ? ArrayKernelName::SSE :
      ArrayKernelName::Simple;

}

#endif

