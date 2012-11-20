
#ifndef _Array_2D_Intrinsic_H_
#define _Array_2D_Intrinsic_H_

#include "array-2d/def.h"
#include "array-2d/kernel/allocate.h"
#include "array-2d/kernel/expression-copy.h"
#include "array-2d/expression/operation.h"
#include "array/interface.h"

namespace mysimulator {

  template <ArrayKernelName LK>
  class __array2d_state {
    public:
      static const Array2DExpressionSSEState Name;
  };

  template <ArrayKernelName LK>
  const Array2DExpressionSSEState __array2d_state<LK>::Name =
      Array2DExpressionSSEState::NoSSE;

  template <>
  const Array2DExpressionSSEState __array2d_state<ArrayKernelName::SSE>::Name =
      Array2DExpressionSSEState::PureSSE;

  template <typename T,ArrayKernelName DK,ArrayKernelName LK>
  class Array2D<Intrinsic<T>,DK,LK,true>
      : public Array<Array<Intrinsic<T>,LK>> {

    public:

      typedef Array2D<Intrinsic<T>,DK,LK,true>  Type;
      typedef Array<Intrinsic<T>,DK>        DataType;
      typedef Array<Intrinsic<T>,LK>        LineType;
      typedef Array<LineType>             ParentType;
      typedef unsigned int size_type;
      typedef T value_type;

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
      template <typename T1,ArrayKernelName DK1>
      Type& operator=(Array2D<Intrinsic<T1>,DK1,LK,true> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(__is_same(*this,A));
        _data=A._data;
        return *this;
      }
      template <typename T1,ArrayKernelName DK1,ArrayKernelName LK1>
      Type& operator=(Array2D<Intrinsic<T1>,DK1,LK,true> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(__is_same(*this,A));
        for(unsigned int i=0;i<ParentType::size();++i)  (*this)[i]=A[i];
        return *this;
      }
      Type& operator=(const value_type& D) {
        assert((bool)(*this));
        _data=D;
        return *this;
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((value_type)((T1)D));
      }
      template <typename EA,typename EB,Array2DExpressionSSEState ST>
      Type& operator=(Array2DSum<EA,EB,ST> const& E) {
        return __copy_sum_mixed_2d(*this,E);
      }
      template <typename EA,typename EB>
      Type& operator=(
          Array2DSum<EA,EB,__array2d_state<LK>::Name> const& E) {
        return __copy_sum_match_2d(*this,E);
      }
      template <typename EA,typename EB,Array2DExpressionSSEState ST>
      Type& operator=(Array2DSub<EA,EB,ST> const& E) {
        return __copy_sub_mixed_2d(*this,E);
      }
      template <typename EA,typename EB>
      Type& operator=(
          Array2DSub<EA,EB,__array2d_state<LK>::Name> const& E) {
        return __copy_sub_match_2d(*this,E);
      }
      template <typename EA,typename EB,Array2DExpressionSSEState ST>
      Type& operator=(Array2DMul<EA,EB,ST> const& E) {
        return __copy_mul_mixed_2d(*this,E);
      }
      template <typename EA,typename EB>
      Type& operator=(
          Array2DMul<EA,EB,__array2d_state<LK>::Name> const& E) {
        return __copy_mul_match_2d(*this,E);
      }
      template <typename EA,typename EB,Array2DExpressionSSEState ST>
      Type& operator=(Array2DDiv<EA,EB,ST> const& E) {
        return __copy_div_mixed_2d(*this,E);
      }
      template <typename EA,typename EB>
      Type& operator=(
          Array2DDiv<EA,EB,__array2d_state<LK>::Name> const& E) {
        return __copy_div_match_2d(*this,E);
      }

      template <typename E>
      Type& operator+=(E const& A) { return operator=((*this)+A); }
      template <typename E>
      Type& operator-=(E const& A) { return operator=((*this)-A); }
      template <typename E>
      Type& operator*=(E const& A) { return operator=((*this)*A); }
      template <typename E>
      Type& operator/=(E const& A) { return operator=((*this)/A); }

      value_type Sum() const { return __sum_2d(*this); }

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
      template <typename T1,ArrayKernelName DK1,ArrayKernelName LK1,bool vF>
      void imprint_structure(Array2D<T1,DK1,LK1,vF> const& A) {
        assert((bool)A);
        Array<Int,ArrayKernelName::SSE>  SZ(A.size());
        for(size_type i=0;i<SZ.size();++i)  SZ[i]=A[i].size();
        allocate(SZ);
        SZ.reset();
      }
      template <ArrayKernelName DK1,ArrayKernelName LK1>
      void imprint(Array2D<Intrinsic<T>,DK1,LK1,true> const& A) {
        imprint_structure(A);
      }
      void swap(Type& A) {
        ParentType::swap((ParentType&)A);
        std::swap(_data,A._data);
      }

  };

  template <typename T,ArrayKernelName DK,ArrayKernelName LK>
  const Array2DExpressionSSEState Array2D<Intrinsic<T>,DK,LK,true>::State =
      __array2d_state<LK>::Name;

}

#endif

