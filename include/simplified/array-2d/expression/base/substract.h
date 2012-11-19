
#ifndef _Array_2D_Expression_Base_Substract_H_
#define _Array_2D_Expression_Base_Substract_H_

#include "array/expression/substract.h"
#include "array-2d/expression/sse-state.h"
#include "basic/memory/deleter.h"

namespace mysimulator {

  template <typename EA,typename EB>
  class Array2DSubBase
      : public __TwoMemberExpression<EA,EB,ExpressionOperationName::Substract>{

    public:

      typedef Array2DSubBase<EA,EB>   Type;
      typedef __TwoMemberExpression<EA,EB,ExpressionOperationName::Substract>
              ParentType;
      typedef unsigned int size_type;

      typedef ArraySub<typename EA::DataType,typename EB::DataType>
              DataType;
      typedef ArraySub<typename EA::LineType,typename EB::LineType>
              LineType;

      static const Array2DExpressionSSEState  State;

    private:

      size_type _size;
      LineType *_line;

    public:

      Array2DSubBase(EA const& A,EB const& B)
        : ParentType(A,B), _size(A.size()<B.size()?A.size():B.size()),
          _line(nullptr) {}
      Array2DSubBase(const Type& E)
        : ParentType((ParentType const&)E), _size(E.size()), _line(nullptr) {}
      ~Array2DSubBase() { __delete_unit<LineType>(_line); }
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
  const Array2DExpressionSSEState Array2DSubBase<EA,EB>::State =
      EA::State == EB::State ? EA::State : Array2DExpressionSSEState::Mixed;

  template <typename E,typename T>
  class Array2DSubBase<E,Intrinsic<T>>
      : public __TwoMemberExpression<E,Intrinsic<T>,
                                     ExpressionOperationName::Substract> {

    public:

      typedef Array2DSubBase<E,Intrinsic<T>>  Type;
      typedef __TwoMemberExpression<E,Intrinsic<T>,
                                    ExpressionOperationName::Substract>
              ParentType;
      typedef unsigned int size_type;

      typedef ArraySub<typename E::DataType,Intrinsic<T>>
              DataType;
      typedef ArraySub<typename E::LineType,Intrinsic<T>>
              LineType;

      static const Array2DExpressionSSEState State;

    private:

      size_type _size;
      LineType *_line;

    public:

      Array2DSubBase(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B), _size(A.size()), _line(nullptr) {}
      Array2DSubBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()), _line(nullptr) {}
      ~Array2DSubBase() { __delete_unit<LineType>(_line); }
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
  const Array2DExpressionSSEState Array2DSubBase<E,Intrinsic<T>>::State =
      E::State;

  template <typename T,typename E>
  class Array2DSubBase<Intrinsic<T>,E>
      : public __TwoMemberExpression<Intrinsic<T>,E,
                                     ExpressionOperationName::Substract> {

    public:

      typedef Array2DSubBase<Intrinsic<T>,E>    Type;
      typedef __TwoMemberExpression<Intrinsic<T>,E,
                                    ExpressionOperationName::Substract>
              ParentType;
      typedef unsigned int size_type;

      typedef ArraySub<Intrinsic<T>,typename E::DataType>
              DataType;
      typedef ArraySub<Intrinsic<T>,typename E::LineType>
              LineType;

      static const Array2DExpressionSSEState State;

    private:

      size_type _size;
      LineType *_line;

    public:

      Array2DSubBase(Intrinsic<T> const& A, E const& B)
        : ParentType(A,B), _size(B.size()), _line(nullptr) {}
      Array2DSubBase(const Type& A)
        : ParentType((ParentType const&)A), _size(A.size()), _line(nullptr) {}
      ~Array2DSubBase() { __delete_unit<LineType>(_line); }
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
  const Array2DExpressionSSEState Array2DSubBase<Intrinsic<T>,E>::State =
      E::State;

}

#endif

