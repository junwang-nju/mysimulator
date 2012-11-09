
#ifndef _Array_Expression_Sum_H_
#define _Array_Expression_Sum_H_

#include "basic/expression/base.h"
#include "basic/type/selector.h"
#include "basic/type/sum.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArraySum
      : public _TwoMemberExpression<EA,EB,ExpressionOperationName::Sum> {

    public:

      typedef ArraySum<EA,EB>   Type;
      typedef _TwoMemberExpression<EA,EB,ExpressionOperationName::Sum>
              ParentType;
      typedef unsigned int size_type;
      typedef typename EA::value_type avType;
      typedef typename EB::value_type bvType;
      typedef typename __dual_selector<avType,bvType,__sum>::Type
              value_type;

      ArraySum(EA const& A,EB const& B) : ParentType(A,B) {}
      ArraySum(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size() const {
        return ParentType::first().size() < ParentType::second().size() ?
               ParentType::first().size() :
               ParentType::second().size();
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
  class ArraySum<E,Intrinsic<T>>
      : public _TwoMemberExpression<E,Intrinsic<T>,
                                    ExpressionOperationName::Sum> {

    public:

      typedef Intrinsic<T>  TType;
      typedef ArraySum<E,TType>  Type;
      typedef _TwoMemberExpression<E,TType,ExpressionOperationName::Sum>
              ParentType;
      typedef unsigned int size_type;
      typedef typename E::value_type  vType;
      typedef typename __dual_selector<vType,T,__sum>::Type
              value_type;

      ArraySum(E const& A,TType const& B) : ParentType(A,B) {}
      ArraySum(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::first().size(); }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) +
               (value_type)((T)ParentType::second());
      }

  };

  template <typename T,typename E>
  class ArraySum<Intrinsic<T>,E>
      : public _TwoMemberExpression<Intrinsic<T>,E,
                                    ExpressionOperationName::Sum> {

    public:

      typedef Intrinsic<T>  TType;
      typedef ArraySum<TType,E>   Type;
      typedef _TwoMemberExpression<TType,E,ExpressionOperationName::Sum>
              ParentType;
      typedef unsigned int size_type;
      typedef typename E::value_type  vType;
      typedef typename __dual_selector<T,vType,__sum>::Type
              value_type;

      ArraySum(TType const& A, E const& B) : ParentType(A,B) {}
      ArraySum(const Type& A) : ParentType((ParentType const&)A) {}
      ~ArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::second().size(); }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()) +
               (value_type)(ParentType::second()[i]);
      }

  };

}

#endif

