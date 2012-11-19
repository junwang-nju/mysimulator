
#ifndef _Array_2D_Expression_Substract_H_
#define _Array_2D_Expression_Substract_H_

#include "array-2d/expression/base/substract.h"

namespace mysimulator {

  template <typename EA,typename EB,
            Array2DExpressionSSEState ST=Array2DSubBase<EA,EB>::State>
  class Array2DSub : public Array2DSubBase<EA,EB> {

    public:

      typedef Array2DSub<EA,EB,ST>                    Type;
      typedef Array2DSubBase<EA,EB>             ParentType;
      typedef typename ParentType::DataType       DataType;

    private:

      DataType _data;

    public:

      Array2DSub(EA const& A, EB const& B)
        : ParentType(A,B),
          _data(ParentType::first().Data(),ParentType::second().Data()) {}
      Array2DSub(const Type& E)
        : ParentType((ParentType const&)E), _data(E._data) {}
      ~Array2DSub() {}
      Type& operator=(const Type&) = delete;

      DataType const& Data() const { return _data; }

  };

  template <typename EA,typename EB>
  class Array2DSub<EA,EB,Array2DExpressionSSEState::Mixed>
      : public Array2DSubBase<EA,EB> {

    public:

      typedef Array2DSub<EA,EB,Array2DExpressionSSEState::Mixed>      Type;
      typedef Array2DSubBase<EA,EB>                             ParentType;

      Array2DSub(EA const& A,EB const& B) : ParentType(A,B) {}
      Array2DSub(const Type& E) : ParentType((ParentType const&)E) {}
      ~Array2DSub() {}
      Type& operator=(const Type&) = delete;

  };

  template <typename E,typename T,Array2DExpressionSSEState ST>
  class Array2DSub<E,Intrinsic<T>,ST>
      : public Array2DSubBase<E,Intrinsic<T>> {

    public:

      typedef Array2DSub<E,Intrinsic<T>,ST>           Type;
      typedef Array2DSubBase<E,Intrinsic<T>>    ParentType;
      typedef typename ParentType::DataType       DataType;

    private:

      DataType _data;

    public:

      Array2DSub(E const& A,Intrinsic<T> const& B)
        : ParentType(A,B),
          _data(ParentType::first().Data(),ParentType::second()) {}
      Array2DSub(const Type& A)
        : ParentType((ParentType const&)A), _data(A._data) {}
      ~Array2DSub() {}
      Type& operator=(const Type&) = delete;

      DataType const& Data() const { return _data; }

  };

  template <typename T,typename E,Array2DExpressionSSEState ST>
  class Array2DSub<Intrinsic<T>,E,ST>
      : public Array2DSubBase<Intrinsic<T>,E> {

    public:

      typedef Array2DSub<Intrinsic<T>,E,ST>             Type;
      typedef Array2DSubBase<Intrinsic<T>,E>      ParentType;
      typedef typename ParentType::DataType         DataType;

    private:

      DataType _data;

    public:

      Array2DSub(Intrinsic<T> const& A,E const& B)
        : ParentType(A,B),
          _data(ParentType::first(),ParentType::second().Data()) {}
      Array2DSub(const Type& A)
        : ParentType((ParentType const&)A), _data(A._data) {}
      ~Array2DSub() {}
      Type& operator=(const Type&) = delete;

      DataType const& Data() const { return _data; }

  };

}

#endif

