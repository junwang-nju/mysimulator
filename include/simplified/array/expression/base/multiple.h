
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

      typedef ArrayMulBase<EA,EB>   Type;
      typedef __TwoMemberExpression<EA,EB,ExpressionOperationName::Multiple>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<typename EA::value_type,
                                       typename EB::value_type,__mul>::Type
              value_type;

    private:

      ArrayKernelName _tag;
      ArrayKernelName _combine(EA const&A, EB const& B) {
        ArrayKernelName N1=A.KernelName();
        ArrayKernelName N2=B.KernelName();
        if((N1==ArrayKernelName::SSE)&&(N2==ArrayKernelName::SSE))
          return ArrayKernelName::SSE;
        else
          return ArrayKernelName::Simple;
      }

    public:

      ArrayMulBase(EA const& A, EB const& B)
        : ParentType(A,B), _tag(_combine(A,B)) {}
      ArrayMulBase(const Type& E)
        : ParentType((ParentType const&)E),
          _tag(_combine(ParentType::first(),ParentType::second())) {}
      ~ArrayMulBase() {}
      Type& operator=(const Type&) = delete;

      ArrayKernelName KernelName() const { return _tag; }
      size_type size() const {
        return ParentType::first().size() < ParentType::second().size() ?
               ParentType::first().size() : ParentType::second().size;
      }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) +
               (value_type)(ParentType::second()[i]);
      }

  };

}

#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArrayMulBase<E,Intrinsic<T>>
      : public __TwoMemberExpression<E,Intrinsic<T>,
                                     ExpressionOperationName::Multiple> {

    public:

      typedef Intrinsic<T>  TType;
      typedef ArrayMulBase<E,TType>   Type;
      typedef __TwoMemberExpression<E,TType,ExpressionOperationName::Multiple>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<typename E::value_type,TType,__mul>::Type
              value_type;

    private:

      ArrayKernelName _tag;

    public:

      ArrayMulBase(E const& A, TType const& B)
        : ParentType(A,B), _tag(A.KernelName()) {}
      ArrayMulBase(const Type& A)
        : ParentType((ParentType const&)A),
          _tag(ParentType::first().KernelName()) {}
      ~ArrayMulBase() {}
      Type& operator=(const Type&) = delete;

      ArrayKernelName KernelName() const { return _tag; }
      size_type size() const { return ParentType::first().size(); }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) +
               (value_type)((T)ParentType::second());
      }

  };

  template <typename T,typename E>
  class ArrayMulBase<Intrinsic<T>,E>
      : public __TwoMemberExpression<Intrinsic<T>,E,
                                     ExpressionOperationName::Multiple> {

    public:

      typedef Intrinsic<T>  TType;
      typedef ArrayMulBase<TType,E>   Type;
      typedef __TwoMemberExpression<TType,E,ExpressionOperationName::Multiple>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<T,typename E::value_type,__mul>::Type
              value_type;

    private:

      ArrayKernelName _tag;

    public:

      ArrayMulBase(TType const& A, E const& B)
        : ParentType(A,B), _tag(B.KernelName()) {}
      ArrayMulBase(const Type& A)
        : ParentType((ParentType const&)A),
          _tag(ParentType::second().KernelName()) {}
      ~ArrayMulBase() {}
      Type& operator=(const Type&) = delete;

      ArrayKernelName KernelName() const { return _tag; }
      size_type size() const { return ParentType::second().size(); }
      value_type operator[](size_type i) const {
        return (value_type)((T)ParentType::first()) +
               (value_type)(ParentType::second()[i]);
      }

  };


}

#endif

