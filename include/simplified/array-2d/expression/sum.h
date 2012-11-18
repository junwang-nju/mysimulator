
#ifndef _Array_2D_Expression_Sum_H_
#define _Array_2D_Expression_Sum_H_

#include "array-2d/expression/base/sum.h"

namespace mysimulator {

  template <typename EA,typename EB,
            Array2DExpressionSSEState ST=Array2DSumBase<EA,EB>::State>
  class Array2DSum : public Array2DSumBase<EA,EB> {

    public:

      typedef Array2DSum<EA,EB,ST>              Type;
      typedef Array2DSumBase<EA,EB>       ParentType;
      typedef typename ParentType::DataType DataType;

      Array2DSum(EA const& A, EB const& B) : ParentType(A,B) {}
      Array2DSum(const Type& E) : ParentType((ParentType const&)E) {}
      ~Array2DSum() {}
      Type& operator=(const Type&) = delete;

      DataType Data() const {
        return DataType(ParentType::first().Data(),
                        ParentType::second().Data());
      }

  };

  template <typename EA,typename EB>
  class Array2DSum<EA,EB,Array2DExpressionSSEState::Mixed>
      : public Array2DSumBase<EA,EB> {

    public:

      typedef Array2DSum<EA,EB,Array2DExpressionSSEState::Mixed> Type;
      typedef Array2DSumBase<EA,EB>                        ParentType;

      Array2DSum(EA const& A,EB const& B) : ParentType(A,B) {}
      Array2DSum(const Type& E) : ParentType((ParentType const&)E) {}
      ~Array2DSum() {}
      Type& operator=(const Type&) = delete;

  };

  template <typename E,typename T,Array2DExpressionSSEState ST>
  class Array2DSum<E,Intrinsic<T>,ST>
      : public Array2DSumBase<E,Intrinsic<T>> {

    public:

      typedef Array2DSum<E,Intrinsic<T>,ST>            Type;
      typedef Array2DSumBase<E,Intrinsic<T>>     ParentType;
      typedef typename ParentType::DataType        DataType;

      Array2DSum(E const& A,Intrinsic<T> const& B) : ParentType(A,B) {}
      Array2DSum(const Type& A) : ParentType((ParentType const&)A) {}
      ~Array2DSum() {}
      Type& operator=(const Type&) = delete;

      DataType Data() const {
        return DataType(ParentType::first().Data(),
                        ParentType::second());
      }

  };

  template <typename T,typename E,Array2DExpressionSSEState ST>
  class Array2DSum<Intrinsic<T>,E,ST>
      : public Array2DSumBase<Intrinsic<T>,E> {

    public:

      typedef Array2DSum<Intrinsic<T>,E,ST>           Type;
      typedef Array2DSumBase<Intrinsic<T>,E>    ParentType;
      typedef typename ParentType::DataType       DataType;

      Array2DSum(Intrinsic<T> const& A,E const& B) : ParentType(A,B) {}
      Array2DSum(const Type& A) : ParentType((ParentType const&)A) {}
      ~Array2DSum() {}
      Type& operator=(const Type&) = delete;

      DataType Data() const {
        return DataType(ParentType::first(),
                        ParentType::second().Data());
      }

  };

}

#endif

