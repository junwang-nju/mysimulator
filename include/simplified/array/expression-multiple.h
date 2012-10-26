
#ifndef _Array_Expression_Multiple_H_
#define _Array_Expression_Multiple_H_

#include "basic/expression/base.h"
#include "basic/expression/name.h"
#include "basic/type/multiple.h"
#include "basic/type/selector.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArrayMul : public _TwoMemberExpression<EA,EB> {

    public:

      typedef ArrayMul<EA,EB>   Type;
      typedef _TwoMemberExpression<EA,EB> ParentType;
      typedef unsigned int size_type;
      typedef typename EA::value_type avType;
      typedef typename EB::value_type bvType;
      typedef typename __dual_selector<avType,bvType,__mul_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArrayMul(EA const& A,EB const& B) : ParentType(A,B) {}
      ArrayMul(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size() const {
        return ParentType::first().size()<ParentType::second().size()?
               ParentType::first().size():
               ParentType::second().size();
      }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) *
               (value_type)(ParentType::second()[i]);
      }

  };

  template <typename EA,typename EB>
  const __ExpressionOperationName ArrayMul<EA,EB>::OpName=
        __ExpressionOperationName::Multiple;

}

#include "basic/intrinsic.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArrayMul<E,Intrinsic<T>> : public _TwoMemberExpression<E,Intrinsic<T>> {

    public:

      typedef ArrayMul<E,Intrinsic<T>>  Type;
      typedef _TwoMemberExpression<E,Intrinsic<T>>  ParentType;
      typedef unsigned int size_type;
      typedef typename E::value_type  vType;
      typedef typename __dual_selector<vType,T,__mul_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArrayMul(E const& A,Intrinsic<T> const& B) : ParentType(A,B) {}
      ArrayMul(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::first().size(); }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) *
               (value_type)((T)ParentType::second());
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName ArrayMul<E,Intrinsic<T>>::OpName=
        __ExpressionOperationName::Multiple;

  template <typename E,typename T>
  class ArrayMul<Intrinsic<T>,E> : public _TwoMemberExpression<Intrinsic<T>,E> {

    public:

      typedef ArrayMul<Intrinsic<T>,E>  Type;
      typedef _TwoMemberExpression<Intrinsic<T>,E>  ParentType;
      typedef unsigned int size_type;
      typedef typename E::value_type  vType;
      typedef typename __dual_selector<T,vType,__mul_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArrayMul(Intrinsic<T> const& A,E const& B) : ParentType(A,B) {}
      ArrayMul(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::second().size(); }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::second()[i]) +
               (value_type)((T)ParentType::first());
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName ArrayMul<Intrinsic<T>,E>::OpName=
        __ExpressionOperationName::Multiple;

}

#endif

