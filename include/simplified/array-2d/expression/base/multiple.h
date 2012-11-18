
#ifndef _Array_2D_Expression_Base_Multiple_H_
#define _Array_2D_Expression_Base_Multiple_H_

#include "array/expression/multiple.h"
#include "array-2d/expression/sse-state.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class Array2DMulBase
      : public __TwoMemberExpression<EA,EB,ExpressionOperationName::Multiple>{

    public:

      typedef Array2DMulBase<EA,EB>   Type;
      typedef __TwoMemberExpression<EA,EB,ExpressionOperationName::Multiple>
              ParentType;
      typedef unsigned int size_type;

      typedef ArrayMul<typename EA::DataType,typename EB::DataType>
              DataType;
      typedef ArrayMul<typename EA::LineType,typename EB::LineType>
              LineType;

      static const Array2DExpressionSSEState State;

    private:

      size_type _size;

    public:

      Array2DMulBase(EA const& A,EB const& B)
        : ParentType(A,B), _size(A.size()<B.size()?A.size():B.size()) {}
      Array2DMulBase(const Type& E)
        : ParentType((ParentType const&)E), _size(E.size()) {}
      ~Array2DMulBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      LineType operator[](size_type i) const {
        return LineType(ParentType::first()[i],ParentType::second()[i]);
      }

  };

  template <typename EA,typename EB>
  const Array2DExpressionSSEState Array2DMulBase<EA,EB>::State =
      EA::State == EB::State ? EA::State : Array2DExpressionSSEState::Mixed;

  template <typename E,typename T>
  class Array2DMulBase<E,Intrinsic<T>>
      : public __TwoMemberExpression<E,Intrinsic<T>,
                                     ExpressionOperationName::Multiple> {

    public:

      typedef Array2DMulBase<E,Intrinsic<T>>  Type;
      typedef __TwoMemberExpression<E,Intrinsic<T>,
                                    ExpressionOperationName::Multiple>
              ParentType;
      typedef unsigned int size_type;

      typedef ArrayMul<typename E::DataType,Intrinsic<T>>
              DataType;
      typedef ArrayMul<typename E::LineType,Intrinsic<T>>
              LineType;

      static const Array2DExpressionSSEState State;

    private:

      size_type _size;

    public:

      Array2DMulBase(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B), _size(A.size()) {}
      Array2DMulBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()) {}
      ~Array2DMulBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      LineType operator[](size_type i) const {
        return LineType(ParentType::first()[i],ParentType::second());
      }

  };

  template <typename E,typename T>
  const Array2DExpressionSSEState Array2DMulBase<E,Intrinsic<T>>::State =
      E::State;

  template <typename T,typename E>
  class Array2DMulBase<Intrinsic<T>,E>
      : public __TwoMemberExpression<Intrinsic<T>,E,
                                     ExpressionOperationName::Multiple> {

    public:

      typedef Array2DMulBase<Intrinsic<T>,E>    Type;
      typedef __TwoMemberExpression<Intrinsic<T>,E,
                                    ExpressionOperationName::Multiple>
              ParentType;
      typedef unsigned int size_type;

      typedef ArrayMul<Intrinsic<T>,typename E::DataType>
              DataType;
      typedef ArrayMul<Intrinsic<T>,typename E::LineType>
              LineType;

      static const Array2DExpressionSSEState State;

    private:

      size_type _size;

    public:

      Array2DMulBase(Intrinsic<T> const& A, E const& B)
        : ParentType(A,B), _size(B.size()) {}
      Array2DMulBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()) {}
      ~Array2DMulBase() {}
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      LineType operator[](size_type i) const {
        return LineType(ParentType::first(),ParentType::second()[i]);
      }

  };

  template <typename T,typename E>
  const Array2DExpressionSSEState Array2DMulBase<Intrinsic<T>,E>::State =
      E::State;

}

#endif

