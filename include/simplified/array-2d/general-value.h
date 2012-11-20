
#ifndef _Array_2D_General_Value_H_
#define _Array_2D_General_Value_H_

#include "array-2d/def.h"
#include "array-2d/kernel/allocate.h"
#include "array/interface.h"

namespace mysimulator {

  template <typename T,ArrayKernelName DK,ArrayKernelName LK>
  class Array2D<T,DK,LK,true> : public Array<Array<T,LK>> {

    public:

      static_assert(DK==ArrayKernelName::Simple &&
                    LK==ArrayKernelName::Simple,
                    "Only Simple style work for General-Value case!\n");

      typedef Array2D<T,DK,LK,true>                 Type;
      typedef Array<T,DK>                       DataType;
      typedef Array<T,LK>                       LineType;
      typedef Array<LineType>                 ParentType;
      typedef unsigned int size_type;
      typedef typename T::value_type value_type;

      static const Array2DExpressionSSEState State;

      DataType _data;

      Array2D() : ParentType(), _data() {}
      Array2D(size_type n,size_type dim) : Array2D() { allocate(n,dim); }
      Array2D(const Type& A) : Array2D() { imprint(A); operator=(A); }
      Array2D(Type&& A) : Array2D() { swap(A); }
      ~Array2D() { reset(); }

      operator bool() const {
        return (bool)_data && ParentType::operator bool();
      }
      DataType const& Data() const { return _data; }
      DataType& Data() { return _data; }
      void reset() { ParentType::reset(); _data.reset(); }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(__is_same(*this,A));
        _data=A._data;
        return *this;
      }
      Type& operator=(const T& D) {
        assert((bool)(*this));
        _data=D;
        return *this;
      }
      Type& operator=(const value_type& D) {
        assert((bool)(*this));
        _data=D;
        return *this;
      }
      template <typename Y>
      Type& operator=(const Intrinsic<Y>& D) {
        return operator=((value_type)((Y)D));
      }

      void allocate(size_type n,size_type dim) { __allocate_2d(*this,n,dim); }
      template <typename Y,ArrayKernelName YK>
      void allocate(Array<Intrinsic<Y>,YK> const& Z) { __allocate_2d(*this,Z); }
      void refer(const Type& A) {
        assert((bool)A);
        reset();
        _data.refer(A._data);
        ParentType::refer((ParentType const&)A);
      }
      void refer(const Type& A,size_type bg,size_type num) {
        assert((bool)A);
        reset();
        ParentType::refer((ParentType const&)A,bg,num);
        size_type y=A[bg].head()-A[0].head();
        size_type w=(A[bg+num-1].head()-A[bg].head())+A[bg+num-1].size();
        _data.refer(A._data,y,w);
      }
      template <typename T1,ArrayKernelName DK1,ArrayKernelName LK1,bool vF1>
      void imprint_structure(Array2D<T1,DK1,LK1,vF1> const& A) {
        assert((bool)A);
        Array<UInt> SZ(A.size());
        for(size_type i=0;i<SZ.size();++i)  SZ[i]=A[i].size();
        allocate(SZ);
        SZ.reset();
      }
      template <ArrayKernelName DK1,ArrayKernelName LK1>
      void imprint(Array2D<T,DK1,LK1,true> const& A) {
        imprint_structure(A);
        for(unsigned int i=0;i<A.size();++i)
        for(unsigned int j=0;j<A[i].size();++j)
          __imprint((*this)[i][j],A[i][j]);
      }
      void swap(Type& A) {
        ParentType::swap((ParentType&)A);
        std::swap(_data,A._data);
      }

  };

  template <typename T,ArrayKernelName DK,ArrayKernelName LK>
  const Array2DExpressionSSEState Array2D<T,DK,LK,true>::State =
      Array2DExpressionSSEState::NoSSE;

}

#endif

