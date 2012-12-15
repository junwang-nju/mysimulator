
#ifndef _Array_Expression_Divide_H_
#define _Array_Expression_Divide_H_

#include "basic/expression/base.h"
#include "basic/expression/name.h"
#include "basic/type/divide.h"
#include "basic/type/selector.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArrayDiv: public _TwoMemberExpression<EA,EB> {

    public:

      typedef ArrayDiv<EA,EB>   Type;
      typedef _TwoMemberExpression<EA,EB> ParentType;
      typedef unsigned int size_type;
      typedef typename EA::value_type avType;
      typedef typename EB::value_type bvType;
      typedef typename __dual_selector<avType,bvType,__div_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArrayDiv(EA const& A,EB const& B) : ParentType(A,B) {}
      ArrayDiv(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArrayDiv() {}
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
  const __ExpressionOperationName ArrayDiv<EA,EB>::OpName=
        __ExpressionOperationName::Divide;

}

#include "basic/intrinsic.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArrayDiv<E,Intrinsic<T>> : public _TwoMemberExpression<E,Intrinsic<T>> {

    public:

      typedef ArrayDiv<E,Intrinsic<T>>  Type;
      typedef _TwoMemberExpression<E,Intrinsic<T>>  ParentType;
      typedef unsigned int size_type;
      typedef typename E::value_type  vType;
      typedef typename __dual_selector<vType,T,__div_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArrayDiv(E const& A,Intrinsic<T> const& B) : ParentType(A,B) {}
      ArrayDiv(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArrayDiv() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::first().size(); }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) -
               (value_type)((T)ParentType::second());
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName ArrayDiv<E,Intrinsic<T>>::OpName=
        __ExpressionOperationName::Divide;

  template <typename E,typename T>
  class ArrayDiv<Intrinsic<T>,E> : public _TwoMemberExpression<Intrinsic<T>,E> {

    public:

      typedef ArrayDiv<Intrinsic<T>,E>  Type;
      typedef _TwoMemberExpression<Intrinsic<T>,E>  ParentType;
      typedef unsigned int size_type;
      typedef typename E::value_type  vType;
      typedef typename __dual_selector<T,vType,__div_flag>::Type
              value_type;

      static const __ExpressionOperationName OpName;

      ArrayDiv(Intrinsic<T> const& A,E const& B) : ParentType(A,B) {}
      ArrayDiv(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArrayDiv() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::second().size(); }
      value_type operator[](size_type i) const {
        return (value_type)((T)ParentType::first()) -
               (value_type)(ParentType::second()[i]);
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName ArrayDiv<Intrinsic<T>,E>::OpName=
        __ExpressionOperationName::Divide;

}

#endif

