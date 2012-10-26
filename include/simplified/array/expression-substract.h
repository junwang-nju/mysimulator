
#ifndef _Array_Expression_Substract_H_
#define _Array_Expression_Substract_H_

#include "basic/expression/base.h"
#include "basic/expression/name.h"
#include "basic/type/substract.h"
#include "basic/type/selector.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArraySub : public _TwoMemberExpression<EA,EB> {

    public:

      typedef ArraySub<EA,EB>   Type;
      typedef _TwoMemberExpression<EA,EB> ParentType;
      typedef unsigned int size_type;
      typedef typename EA::value_type avType;
      typedef typename EB::value_type bvType;
      typedef typename __dual_selector<avType,bvType,__sub_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArraySub(EA const& A,EB const& B) : ParentType(A,B) {}
      ArraySub(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArraySub() {}
      Type& operator=(const Type&) = delete;

      size_type size() const {
        return ParentType::first().size()<ParentType::second().size()?
               ParentType::first().size():
               ParentType::second().size();
      }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) -
               (value_type)(ParentType::second()[i]);
      }

  };

  template <typename EA,typename EB>
  const __ExpressionOperationName ArraySub<EA,EB>::OpName=
        __ExpressionOperationName::Substract;

}

#include "basic/intrinsic.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArraySub<E,Intrinsic<T>> : public _TwoMemberExpression<E,Intrinsic<T>> {

    public:

      typedef ArraySub<E,Intrinsic<T>>  Type;
      typedef _TwoMemberExpression<E,Intrinsic<T>>  ParentType;
      typedef unsigned int size_type;
      typedef typename E::value_type  vType;
      typedef typename __dual_selector<vType,T,__sub_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArraySub(E const& A,Intrinsic<T> const& B) : ParentType(A,B) {}
      ArraySub(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArraySub() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::first().size(); }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) -
               (value_type)((T)ParentType::second());
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName ArraySub<E,Intrinsic<T>>::OpName=
        __ExpressionOperationName::Substract;

  template <typename E,typename T>
  class ArraySub<Intrinsic<T>,E> : public _TwoMemberExpression<Intrinsic<T>,E> {

    public:

      typedef ArraySub<Intrinsic<T>,E>  Type;
      typedef _TwoMemberExpression<Intrinsic<T>,E>  ParentType;
      typedef unsigned int size_type;
      typedef typename E::value_type  vType;
      typedef typename __dual_selector<T,vType,__sub_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArraySub(Intrinsic<T> const& A,E const& B) : ParentType(A,B) {}
      ArraySub(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArraySub() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::second().size(); }
      value_type operator[](size_type i) const {
        return (value_type)((T)ParentType::first()) -
               (value_type)(ParentType::second()[i]);
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName ArraySub<Intrinsic<T>,E>::OpName=
        __ExpressionOperationName::Substract;

}

#endif

