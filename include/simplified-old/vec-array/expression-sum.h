
#ifndef _Vector_Array_Expression_Sum_H_
#define _Vector_Array_Expression_Sum_H_

#include "array/expression-sum.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class VecArraySum : public _TwoMemberExpression<EA,EB> {

    public:

      typedef VecArraySum<EA,EB>  Type;
      typedef _TwoMemberExpression<EA,EB> ParentType;
      typedef unsigned int size_type;
      typedef typename EA::VecType    avType;
      typedef typename EB::VecType    bvType;
      typedef ArraySum<avType,bvType>   VecType;

      static const __ExpressionOperationName OpName;

      VecArraySum(EA const&A,EB const& B) : ParentType(A,B) {}
      VecArraySum(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size() const {
        return ParentType::first().size()<ParentType::second().size() ?
               ParentType::first().size() :
               ParentType::second().size();
      }
      VecType operator[](size_type i) const {
        return ParentType::first()[i] + ParentType::second()[i];
      }

  };

  template <typename EA,typename EB>
  const __ExpressionOperationName VecArraySum<EA,EB>::OpName=
        __ExpressionOperationName::Add;

  template <typename E,typename T>
  class VecArraySum<E,Intrinsic<T>>
      : public _TwoMemberExpression<E,Intrinsic<T>> {

    public:

      typedef VecArraySum<E,Intrinsic<T>>  Type;
      typedef _TwoMemberExpression<E,Intrinsic<T>> ParentType;
      typedef unsigned int size_type;
      typedef typename E::VecType    vType;
      typedef ArraySum<vType,Intrinsic<T>>  VecType;

      static const __ExpressionOperationName OpName;

      VecArraySum(E const& A,Intrinsic<T> const& B) : ParentType(A,B) {}
      VecArraySum(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::first().size(); }
      VecType operator[](size_type i) const {
        return ParentType::first()[i] + ParentType::second();
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName VecArraySum<E,Intrinsic<T>>::OpName=
        __ExpressionOperationName::Add;

  template <typename E,typename T>
  class VecArraySum<Intrinsic<T>,E>
      : public _TwoMemberExpression<Intrinsic<T>,E> {

    public:

      typedef VecArraySum<Intrinsic<T>,E>  Type;
      typedef _TwoMemberExpression<Intrinsic<T>,E> ParentType;
      typedef unsigned int size_type;
      typedef typename E::VecType    vType;
      typedef ArraySum<Intrinsic<T>,vType>  VecType;

      static const __ExpressionOperationName OpName;

      VecArraySum(Intrinsic<T> const& A,E const& B) : ParentType(A,B) {}
      VecArraySum(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArraySum() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::second().size(); }
      VecType operator[](size_type i) const {
        return ParentType::first() + ParentType::second()[i];
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName VecArraySum<Intrinsic<T>,E>::OpName=
        __ExpressionOperationName::Add;

}

#endif

