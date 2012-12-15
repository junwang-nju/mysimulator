
#ifndef _Array_2D_Expression_Base_Divide_H_
#define _Array_2D_Expression_Base_Divide_H_

#include "array/expression/divide.h"
#include "array-2d/expression/sse-state.h"
#include "basic/memory/deleter.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class Array2DDivBase
      : public __TwoMemberExpression<EA,EB,ExpressionOperationName::Divide>{

    public:

      typedef Array2DDivBase<EA,EB>   Type;
      typedef __TwoMemberExpression<EA,EB,ExpressionOperationName::Divide>
              ParentType;
      typedef unsigned int size_type;

      typedef ArrayDiv<typename EA::DataType,typename EB::DataType>
              DataType;
      typedef ArrayDiv<typename EA::LineType,typename EB::LineType>
              LineType;

      static const Array2DExpressionSSEState State;

    private:

      size_type _size;
      LineType *_line;

    public:

      Array2DDivBase(EA const& A,EB const& B)
        : ParentType(A,B), _size(A.size()<B.size()?A.size():B.size()),
          _line(nullptr) {}
      Array2DDivBase(const Type& E)
        : ParentType((ParentType const&)E), _size(E.size()), _line(nullptr) {}
      ~Array2DDivBase() { __delete_unit<LineType>(_line); }
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      LineType const& operator[](size_type i) const {
        __delete_unit<LineType>(const_cast<LineType*&>(_line));
        const_cast<LineType*&>(_line)=
          new LineType(ParentType::first()[i],ParentType::second()[i]);
        return *_line;
      }

  };

  template <typename EA,typename EB>
  const Array2DExpressionSSEState Array2DDivBase<EA,EB>::State =
      EA::State == EB::State ? EA::State : Array2DExpressionSSEState::Mixed;

  template <typename E,typename T>
  class Array2DDivBase<E,Intrinsic<T>>
      : public __TwoMemberExpression<E,Intrinsic<T>,
                                     ExpressionOperationName::Divide> {

    public:

      typedef Array2DDivBase<E,Intrinsic<T>>  Type;
      typedef __TwoMemberExpression<E,Intrinsic<T>,
                                    ExpressionOperationName::Divide>
              ParentType;
      typedef unsigned int size_type;

      typedef ArrayDiv<typename E::DataType,Intrinsic<T>>
              DataType;
      typedef ArrayDiv<typename E::LineType,Intrinsic<T>>
              LineType;

      static const Array2DExpressionSSEState State;

    private:

      size_type _size;
      LineType *_line;

    public:

      Array2DDivBase(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B), _size(A.size()), _line(nullptr) {}
      Array2DDivBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()), _line(nullptr) {}
      ~Array2DDivBase() { __delete_unit<LineType>(_line); }
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      LineType const& operator[](size_type i) const {
        __delete_unit<LineType>(const_cast<LineType*&>(_line));
        const_cast<LineType*&>(_line)=
          new LineType(ParentType::first()[i],ParentType::second());
        return *_line;
      }

  };

  template <typename E,typename T>
  const Array2DExpressionSSEState Array2DDivBase<E,Intrinsic<T>>::State =
      E::State;

  template <typename T,typename E>
  class Array2DDivBase<Intrinsic<T>,E>
      : public __TwoMemberExpression<Intrinsic<T>,E,
                                     ExpressionOperationName::Divide> {

    public:

      typedef Array2DDivBase<Intrinsic<T>,E>    Type;
      typedef __TwoMemberExpression<Intrinsic<T>,E,
                                    ExpressionOperationName::Divide>
              ParentType;
      typedef unsigned int size_type;

      typedef ArrayDiv<Intrinsic<T>,typename E::DataType>
              DataType;
      typedef ArrayDiv<Intrinsic<T>,typename E::LineType>
              LineType;

      static const Array2DExpressionSSEState State;

    private:

      size_type _size;
      LineType *_line;

    public:

      Array2DDivBase(Intrinsic<T> const& A, E const& B)
        : ParentType(A,B), _size(B.size()), _line(nullptr) {}
      Array2DDivBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()), _line(nullptr) {}
      ~Array2DDivBase() { __delete_unit<LineType>(_line); }
      Type& operator=(const Type&) = delete;

      size_type size() const { return _size; }
      LineType const& operator[](size_type i) const {
        __delete_unit<LineType>(const_cast<LineType*&>(_line));
        const_cast<LineType*&>(_line)=
          new LineType(ParentType::first(),ParentType::second()[i]);
        return *_line;
      }

  };

  template <typename T,typename E>
  const Array2DExpressionSSEState Array2DDivBase<Intrinsic<T>,E>::State =
      E::State;

}

#endif

