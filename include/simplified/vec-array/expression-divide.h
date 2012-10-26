
#ifndef _Vector_Array_Expression_Divide_H_
#define _Vector_Array_Expression_Divide_H_

#include "array/expression-divide.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class VecArrayDiv : public _TwoMemberExpression<EA,EB> {

    public:

      typedef VecArrayDiv<EA,EB>  Type;
      typedef _TwoMemberExpression<EA,EB> ParentType;
      typedef unsigned int size_type;
      typedef typename EA::VecType    avType;
      typedef typename EB::VecType    bvType;
      typedef ArrayDiv<avType,bvType>   VecType;

      static const __ExpressionOperationName OpName;

      VecArrayDiv(EA const&A,EB const& B) : ParentType(A,B) {}
      VecArrayDiv(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArrayDiv() {}
      Type& operator=(const Type&) = delete;

      size_type size() const {
        return ParentType::first().size()<ParentType::second().size() ?
               ParentType::first().size() :
               ParentType::second().size();
      }
      VecType operator[](size_type i) const {
        return ParentType::first()[i] / ParentType::second()[i];
      }

  };

  template <typename EA,typename EB>
  const __ExpressionOperationName VecArrayDiv<EA,EB>::OpName=
        __ExpressionOperationName::Divide;

  template <typename E,typename T>
  class VecArrayDiv<E,Intrinsic<T>>
      : public _TwoMemberExpression<E,Intrinsic<T>> {

    public:

      typedef VecArrayDiv<E,Intrinsic<T>>  Type;
      typedef _TwoMemberExpression<E,Intrinsic<T>> ParentType;
      typedef unsigned int size_type;
      typedef typename E::VecType    vType;
      typedef ArrayDiv<vType,Intrinsic<T>>  VecType;

      static const __ExpressionOperationName OpName;

      VecArrayDiv(E const& A,Intrinsic<T> const& B) : ParentType(A,B) {}
      VecArrayDiv(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArrayDiv() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::first().size(); }
      VecType operator[](size_type i) const {
        return ParentType::first()[i] / ParentType::second();
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName VecArrayDiv<E,Intrinsic<T>>::OpName=
        __ExpressionOperationName::Divide;

  template <typename E,typename T>
  class VecArrayDiv<Intrinsic<T>,E>
      : public _TwoMemberExpression<Intrinsic<T>,E> {

    public:

      typedef VecArrayDiv<Intrinsic<T>,E>  Type;
      typedef _TwoMemberExpression<Intrinsic<T>,E> ParentType;
      typedef unsigned int size_type;
      typedef typename E::VecType    vType;
      typedef ArrayDiv<Intrinsic<T>,vType>  VecType;

      static const __ExpressionOperationName OpName;

      VecArrayDiv(Intrinsic<T> const& A,E const& B) : ParentType(A,B) {}
      VecArrayDiv(const Type& A) : ParentType((ParentType const&)A) {}
      ~VecArrayDiv() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return ParentType::second().size(); }
      VecType operator[](size_type i) const {
        return ParentType::first() / ParentType::second()[i];
      }

  };

  template <typename E,typename T>
  const __ExpressionOperationName VecArrayDiv<Intrinsic<T>,E>::OpName=
        __ExpressionOperationName::Divide;

}

#endif

