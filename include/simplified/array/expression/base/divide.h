
#ifndef _Array_Expression_Base_Divide_H_
#define _Array_Expression_Base_Divide_H_

#include "basic/expression/base.h"
#include "basic/type/selector.h"
#include "basic/type/divide.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArrayDivBase
      : public __TwoMemberExpression<EA,EB,ExpressionOperationName::Divide> {

    public:

      typedef ArrayDivBase<EA,EB>   Type;
      typedef __TwoMemberExpression<EA,EB,ExpressionOperationName::Divide>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<typename EA::value_type,
                                       typename EB::value_type,__div>::Type
              value_type;

    private:

      size_type _size;

    public:

      ArrayDivBase(EA const& A,EB const& B)
        : ParentType(A,B), _size(A.size()<B.size()?A.size():B.size()) {}
      ArrayDivBase(const Type& E)
        : ParentType((ParentType const&)E), _size(E.size()) {}
      ~ArrayDivBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) /
               (value_type)(ParentType::second()[i]);
      }

  };

}

#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArrayDivBase<E,Intrinsic<T>>
      : public __TwoMemberExpression<E,Intrinsic<T>,
                                     ExpressionOperationName::Divide> {

    public:

      typedef Intrinsic<T>  TType;
      typedef ArrayDivBase<E,TType>    Type;
      typedef __TwoMemberExpression<E,TType,ExpressionOperationName::Divide>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<typename E::value_type,T,__div>::Type
              value_type;

    private:

      size_type _size;

    public:

      ArrayDivBase(E const& A, TType const& B)
        : ParentType(A,B), _size(A.size()) {}
      ArrayDivBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()) {}
      ~ArrayDivBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) /
               (value_type)((T)ParentType::second());
      }

  };

  template <typename T,typename E>
  class ArrayDivBase<Intrinsic<T>,E>
      : public __TwoMemberExpression<Intrinsic<T>,E,
                                     ExpressionOperationName::Divide> {

    public:

      typedef Intrinsic<T>  TType;
      typedef ArrayDivBase<TType,E>   Type;
      typedef __TwoMemberExpression<TType,E,ExpressionOperationName::Divide>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<T,typename E::value_type,__div>::Type
              value_type;

    private:

      size_type _size;

    public:

      ArrayDivBase(TType const& A,E const& B)
        : ParentType(A,B), _size(B.size()) {}
      ArrayDivBase(const Type& A) 
        : ParentType((ParentType const&)A), _size(A.size()) {}
      ~ArrayDivBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)((T)ParentType::first()) /
               (value_type)(ParentType::second()[i]);
      }

  };

}

#endif

