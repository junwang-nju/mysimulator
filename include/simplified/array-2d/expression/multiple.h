
#ifndef _Array_2D_Expression_Multiple_H_
#define _Array_2D_Expression_Multiple_H_

#include "array-2d/expression/base/multiple.h"

namespace mysimulator {

  template <typename EA,typename EB,
            Array2DExpressionSSEState ST=Array2DMulBase<EA,EB>::State>
  class Array2DMul : public Array2DMulBase<EA,EB> {

    public:

      typedef Array2DMul<EA,EB,ST>              Type;
      typedef Array2DMulBase<EA,EB>       ParentType;
      typedef typename ParentType::DataType DataType;

      Array2DMul(EA const& A,EB const& B) : ParentType(A,B) {}
      Array2DMul(const Type& E) : ParentType((ParentType const&)E) {} 
      ~Array2DMul() {}
      Type& operator=(const Type&) = delete;

      DataType Data() const {
        return DataType(ParentType::first().Data(),
                        ParentType::second().Data());
      }

  };

  template <typename EA,typename EB>
  class Array2DMul<EA,EB,Array2DExpressionSSEState::Mixed>
      : public Array2DMulBase<EA,EB> {

    public:

      typedef Array2DMul<EA,EB,Array2DExpressionSSEState::Mixed>      Type;
      typedef Array2DMulBase<EA,EB>                             ParentType;

      Array2DMul(EA const& A,EB const& B) : ParentType(A,B) {}
      Array2DMul(const Type& E) : ParentType((ParentType const&)E) {}
      ~Array2DMul() {}
      Type& operator=(const Type&) = delete;

  };

  template <typename E,typename T,Array2DExpressionSSEState ST>
  class Array2DMul<E,Intrinsic<T>,ST>
      : public Array2DMulBase<E,Intrinsic<T>> {

    public:

      typedef Array2DMul<E,Intrinsic<T>,ST>         Type;
      typedef Array2DMulBase<E,Intrinsic<T>>  ParentType;
      typedef typename ParentType::DataType     DataType;

      Array2DMul(E const& A,Intrinsic<T> const& B) : ParentType(A,B) {}
      Array2DMul(const Type& A) : ParentType((ParentType const&)A) {}
      ~Array2DMul() {}
      Type& operator=(const Type&) = delete;

      DataType Data() const {
        return DataType(ParentType::first().Data(),
                        ParentType::second());
      }

  };

  template <typename T,typename E,Array2DExpressionSSEState ST>
  class Array2DMul<Intrinsic<T>,E,ST>
      : public Array2DMulBase<Intrinsic<T>,E> {

    public:

      typedef Array2DMul<Intrinsic<T>,E,ST>               Type;
      typedef Array2DMulBase<Intrinsic<T>,E>        ParentType;
      typedef typename ParentType::DataType           DataType;

      Array2DMul(Intrinsic<T> const& A,E const& B) : ParentType(A,B) {}
      Array2DMul(const Type& A) : ParentType((ParentType const&)A) {}
      ~Array2DMul() {}
      Type& operator=(const Type&) = delete;

      DataType Data() const {
        return DataType(ParentType::first(),
                        ParentType::second().Data());
      }

  };

}

#endif

