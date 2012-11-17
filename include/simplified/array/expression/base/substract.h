
#ifndef _Array_Expression_Base_Substract_H_
#define _Array_Expression_Base_Substract_H_

#include "basic/expression/base.h"
#include "basic/type/selector.h"
#include "basic/type/substract.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class ArraySubBase
      : public __TwoMemberExpression<EA,EB,ExpressionOperationName::Substract> {

    public:

      typedef ArraySubBase<EA,EB>   Type;
      typedef __TwoMemberExpression<EA,EB,ExpressionOperationName::Substract>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<typename EA::value_type,
                                       typename EB::value_type,__sub>::Type
              value_type;

    private:

      size_type _size;

    public:

      ArraySubBase(EA const& A,EB const& B)
        : ParentType(A,B), _size(A.size()<B.size()?A.size():B.size()) {}
      ArraySubBase(const Type& E)
        : ParentType((ParentType const&)E), _size(E.size()) {}
      ~ArraySubBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) -
               (value_type)(ParentType::second()[i]);
      }

  };

}

#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename E,typename T>
  class ArraySubBase<E,Intrinsic<T>>
      : public __TwoMemberExpression<E,Intrinsic<T>,
                                     ExpressionOperationName::Substract> {

    public:

      typedef Intrinsic<T>  TType;
      typedef ArraySubBase<E,TType>   Type;
      typedef __TwoMemberExpression<E,TType,ExpressionOperationName::Substract>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<typename E::value_type,T,__sub>::Type
              value_type;

    private:

      size_type _size;

    public:

      ArraySubBase(E const& A, TType const& B)
        : ParentType(A,B), _size(A.size()) {}
      ArraySubBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()) {}
      ~ArraySubBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)(ParentType::first()[i]) -
               (value_type)((T)ParentType::second());
      }

  };

  template <typename T,typename E>
  class ArraySubBase<Intrinsic<T>,E>
      : public __TwoMemberExpression<Intrinsic<T>,E,
                                     ExpressionOperationName::Substract> {

    public:

      typedef Intrinsic<T>  TType;
      typedef ArraySubBase<TType,E>   Type;
      typedef __TwoMemberExpression<TType,E,ExpressionOperationName::Substract>
              ParentType;
      typedef unsigned int size_type;
      typedef typename __dual_selector<T,typename E::value_type,__sub>::Type
              value_type;

    private:

      size_type _size;

    public:

      ArraySubBase(TType const& A,E const& B)
        : ParentType(A,B), _size(B.size()) {}
      ArraySubBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()) {}
      ~ArraySubBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      value_type operator[](size_type i) const {
        return (value_type)((T)ParentType::first()) -
               (value_type)(ParentType::second()[i]);
      }

  };

}

#endif

