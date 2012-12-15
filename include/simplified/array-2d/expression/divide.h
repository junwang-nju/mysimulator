
#ifndef _Array_2D_Expression_Divide_H_
#define _Array_2D_Expression_Divide_H_

#include "array-2d/expression/base/divide.h"

namespace mysimulator {

  template <typename EA,typename EB,
            Array2DExpressionSSEState ST=Array2DDivBase<EA,EB>::State>
  class Array2DDiv : public Array2DDivBase<EA,EB> {

    public:

      typedef Array2DDiv<EA,EB,ST>              Type;
      typedef Array2DDivBase<EA,EB>       ParentType;
      typedef typename ParentType::DataType DataType;

    private:

      DataType _data;

    public:

      Array2DDiv(EA const& A,EB const& B)
        : ParentType(A,B),
          _data(ParentType::first().Data(),ParentType::second().Data()) {}
      Array2DDiv(const Type& E)
        : ParentType((ParentType const&)E), _data(E._data) {}
      ~Array2DDiv() {}
      Type& operator=(const Type&) = delete;

      DataType const& Data() const { return _data; }

  };

  template <typename EA,typename EB>
  class Array2DDiv<EA,EB,Array2DExpressionSSEState::Mixed>
      : public Array2DDivBase<EA,EB> {

    public:

      typedef Array2DDiv<EA,EB,Array2DExpressionSSEState::Mixed>      Type;
      typedef Array2DDivBase<EA,EB>                             ParentType;

      Array2DDiv(EA const& A,EB const& B) : ParentType(A,B) {}
      Array2DDiv(const Type& E) : ParentType((ParentType const&)E) {}
      ~Array2DDiv() {}
      Type& operator=(const Type&) = delete;

  };

  template <typename E,typename T,Array2DExpressionSSEState ST>
  class Array2DDiv<E,Intrinsic<T>,ST>
      : public Array2DDivBase<E,Intrinsic<T>> {

    public:

      typedef Array2DDiv<E,Intrinsic<T>,ST>           Type;
      typedef Array2DDivBase<E,Intrinsic<T>>    ParentType;
      typedef typename ParentType::DataType       DataType;

    private:

      DataType _data;

    public:

      Array2DDiv(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B),
          _data(ParentType::first().Data(),ParentType::second()) {}
      Array2DDiv(const Type& A)
        : ParentType((ParentType const&)A), _data(A._data) {}
      ~Array2DDiv() {}
      Type& operator=(const Type&) = delete;

      DataType const& Data() const { return _data; }

  };

  template <typename T,typename E,Array2DExpressionSSEState ST>
  class Array2DDiv<Intrinsic<T>,E,ST>
      : public Array2DDivBase<Intrinsic<T>,E> {

    public:

      typedef Array2DDiv<Intrinsic<T>,E,ST>             Type;
      typedef Array2DDivBase<Intrinsic<T>,E>      ParentType;
      typedef typename ParentType::DataType         DataType;

    private:

      DataType _data;

    public:

      Array2DDiv(Intrinsic<T> const& A,E const& B)
        : ParentType(A,B),
          _data(ParentType::first(),ParentType::second().Data()) {}
      Array2DDiv(const Type& A)
        : ParentType((ParentType const&)A), _data(A._data) {}
      ~Array2DDiv() {}
      Type& operator=(const Type&) = delete;

      DataType const& Data() const { return _data; }

  };

}

#endif

