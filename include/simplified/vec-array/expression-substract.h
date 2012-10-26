
#ifndef _Vector_Array_Expression_Substract_H_
#define _Vector_Array_Expression_Substract_H_

#include "array/expression-substract.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class VecArraySub : public _TwoMemberExpression<EA,EB> {

    public:

      typedef VecArraySub<EA,EB>  Type;
      typedef _TwoMemberExpression<EA,EB> ParentType;
      typedef unsigned int size_type;
      typedef typename EA::VecType    avType;
      typedef typename EB::VecType    bvType;
      typedef ArraySub<avType,bvType>   VecType;

      static const __ExpressionOperationName OpName;

      VecArraySub(EA const&A,EB const& B) : ParentType(A,B) {}
      VecArraySub(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArraySub() {}
      Type& operator=(const Type&) = delete;

      size_type size() const {
        return ParentType::first().size()<ParentType::second().size() ?
               ParentType::first().size() :
               ParentType::second().size();
      }
      VecType operator[](size_type i) const {
        return ParentType::first()[i] - ParentType::second()[i];
      }

  };

  template <typename EA,typename EB>
  const __ExpressionOperationName VecArraySub<EA,EB>::OpName=
        __ExpressionOperationName::Substract;

  template <typename E,typename T>
  class VecArraySub<E,Intrinsic<T>>
      : public _TwoMemberExpression<E,Intrinsic<T>> {

    public:

      typedef VecArraySub<E,Intrinsic<T>>  Type;
      typedef _TwoMemberExpression<E,Intrinsic<T>> ParentType;
      typedef unsigned int size_type;
      typedef typename E::VecType    vType;
      typedef ArraySub<vType,Intrinsic<T>>  VecType;

      static const __ExpressionOperationName OpName;

      VecArraySub(E const& A,Intrinsic<T> const& B) : ParentType(A,B) {}
      VecArraySub(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArraySub() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::first().size(); }
      VecType operator[](size_type i) const {
        return ParentType::first()[i] - ParentType::second();
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName VecArraySub<E,Intrinsic<T>>::OpName=
        __ExpressionOperationName::Substract;

  template <typename E,typename T>
  class VecArraySub<Intrinsic<T>,E>
      : public _TwoMemberExpression<Intrinsic<T>,E> {

    public:

      typedef VecArraySub<Intrinsic<T>,E>  Type;
      typedef _TwoMemberExpression<Intrinsic<T>,E> ParentType;
      typedef unsigned int size_type;
      typedef typename E::VecType    vType;
      typedef ArraySub<Intrinsic<T>,vType>  VecType;

      static const __ExpressionOperationName OpName;

      VecArraySub(Intrinsic<T> const& A,E const& B) : ParentType(A,B) {}
      VecArraySub(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArraySub() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::second().size(); }
      VecType operator[](size_type i) const {
        return ParentType::first() - ParentType::second()[i];
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName VecArraySub<Intrinsic<T>,E>::OpName=
        __ExpressionOperationName::Substract;

}

#endif

