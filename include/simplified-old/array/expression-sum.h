
#ifndef _Array_Expression_Sum_H_
#define _Array_Expression_Sum_H_

#include "basic/expression/base.h"
#include "basic/expression/name.h"
#include "basic/type/sum.h"
#include "basic/type/selector.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArraySum : public _TwoMemberExpression<EA,EB> {

    public:

      typedef ArraySum<EA,EB>   Type;
      typedef _TwoMemberExpression<EA,EB> ParentType;
      typedef unsigned int size_type;
      typedef typename EA::value_type avType;
      typedef typename EB::value_type bvType;
      typedef typename __dual_selector<avType,bvType,__sum_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArraySum(EA const& A,EB const& B) : ParentType(A,B) {}
      ArraySum(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size() const {
        return ParentType::first().size()<ParentType::second().size()?
               ParentType::first().size():
               ParentType::second().size();
      }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) +
               (value_type)(ParentType::second()[i]);
      }

  };

  template <typename EA,typename EB>
  const __ExpressionOperationName ArraySum<EA,EB>::OpName=
        __ExpressionOperationName::Add;

}

#include "basic/intrinsic.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArraySum<E,Intrinsic<T>> : public _TwoMemberExpression<E,Intrinsic<T>> {

    public:

      typedef ArraySum<E,Intrinsic<T>>  Type;
      typedef _TwoMemberExpression<E,Intrinsic<T>>  ParentType;
      typedef unsigned int size_type;
      typedef typename E::value_type  vType;
      typedef typename __dual_selector<vType,T,__sum_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArraySum(E const& A,Intrinsic<T> const& B) : ParentType(A,B) {}
      ArraySum(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::first().size(); }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) +
               (value_type)((T)ParentType::second());
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName ArraySum<E,Intrinsic<T>>::OpName=
        __ExpressionOperationName::Add;

  template <typename E,typename T>
  class ArraySum<Intrinsic<T>,E> : public _TwoMemberExpression<Intrinsic<T>,E> {

    public:

      typedef ArraySum<Intrinsic<T>,E>  Type;
      typedef _TwoMemberExpression<Intrinsic<T>,E>  ParentType;
      typedef unsigned int size_type;
      typedef typename E::value_type  vType;
      typedef typename __dual_selector<T,vType,__sum_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArraySum(Intrinsic<T> const& A,E const& B) : ParentType(A,B) {}
      ArraySum(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::second().size(); }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::second()[i]) +
               (value_type)((T)ParentType::first());
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName ArraySum<Intrinsic<T>,E>::OpName=
        __ExpressionOperationName::Add;

}

#endif

