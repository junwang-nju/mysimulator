
#ifndef _Vector_Array_Expression_Multiple_H_
#define _Vector_Array_Expression_Multiple_H_

#include "array/expression-multiple.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class VecArrayMul : public _TwoMemberExpression<EA,EB> {

    public:

      typedef VecArrayMul<EA,EB>  Type;
      typedef _TwoMemberExpression<EA,EB> ParentType;
      typedef unsigned int size_type;
      typedef typename EA::VecType    avType;
      typedef typename EB::VecType    bvType;
      typedef ArrayMul<avType,bvType>   VecType;

      static const __ExpressionOperationName OpName;

      VecArrayMul(EA const&A,EB const& B) : ParentType(A,B) {}
      VecArrayMul(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size() const {
        return ParentType::first().size()<ParentType::second().size() ?
               ParentType::first().size() :
               ParentType::second().size();
      }
      VecType operator[](size_type i) const {
        return ParentType::first()[i] * ParentType::second()[i];
      }

  };

  template <typename EA,typename EB>
  const __ExpressionOperationName VecArrayMul<EA,EB>::OpName=
        __ExpressionOperationName::Multiple;

  template <typename E,typename T>
  class VecArrayMul<E,Intrinsic<T>>
      : public _TwoMemberExpression<E,Intrinsic<T>> {

    public:

      typedef VecArrayMul<E,Intrinsic<T>>  Type;
      typedef _TwoMemberExpression<E,Intrinsic<T>> ParentType;
      typedef unsigned int size_type;
      typedef typename E::VecType    vType;
      typedef ArrayMul<vType,Intrinsic<T>>  VecType;

      static const __ExpressionOperationName OpName;

      VecArrayMul(E const& A,Intrinsic<T> const& B) : ParentType(A,B) {}
      VecArrayMul(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::first().size(); }
      VecType operator[](size_type i) const {
        return ParentType::first()[i] * ParentType::second();
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName VecArrayMul<E,Intrinsic<T>>::OpName=
        __ExpressionOperationName::Multiple;

  template <typename E,typename T>
  class VecArrayMul<Intrinsic<T>,E>
      : public _TwoMemberExpression<Intrinsic<T>,E> {

    public:

      typedef VecArrayMul<Intrinsic<T>,E>  Type;
      typedef _TwoMemberExpression<Intrinsic<T>,E> ParentType;
      typedef unsigned int size_type;
      typedef typename E::VecType    vType;
      typedef ArrayMul<Intrinsic<T>,vType>  VecType;

      static const __ExpressionOperationName OpName;

      VecArrayMul(Intrinsic<T> const& A,E const& B) : ParentType(A,B) {}
      VecArrayMul(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArrayMul() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::second().size(); }
      VecType operator[](size_type i) const {
        return ParentType::first() * ParentType::second()[i];
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName VecArrayMul<Intrinsic<T>,E>::OpName=
        __ExpressionOperationName::Multiple;

}

#endif

