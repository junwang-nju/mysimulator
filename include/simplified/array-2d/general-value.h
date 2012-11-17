
#ifndef _Array_2D_General_Value_H_
#define _Array_2D_General_Value_H_

#include "array-2d/def.h"
#include "array-2d/operation.h"
#include "array/interface.h"

namespace mysimulator {

  template <typename T>
  class Array2D<T,ArrayKernelName::Simple,ArrayKernelName::Simple,true>
      : public Array<Array<T,ArrayKernelName::Simple>> {

    public:

      typedef Array2D<T,ArrayKernelName::Simple,ArrayKernelName::Simple,true>
              Type;
      typedef Array<T,ArrayKernelName::Simple>  DataType;
      typedef Array<T,ArrayKernelName::Simple>  LineType;
      typedef Array<LineType>                   ParentType;
      typedef unsigned int size_type;
      typedef typename T::value_type value_type;

      friend void __allocate_2d<T,false>(Type&,size_type,size_type);
      template <typename T1,bool vF,typename Y,ArrayKernelName YK>
      friend void __allocate_2d(
          Array2D<T1,ArrayKernelName::Simple,ArrayKernelName::Simple,true>&,
          Array<Intrinsic<Y>,YK> const&);

    protected:

      DataType _data;

    public:

      Array2D() : ParentType(), _data() {}
      Array2D(size_type n,size_type dim) : Array2D() { allocate(n,dim); }
      Array2D(const Type& A) : Array2D() { imprint(A); operator=(A); }
      Array2D(Type&& A) : Array2D() { swap(A); }
      ~Array2D() { reset(); }

      operator bool() const {
        return (bool)_data && ParentType::operator bool();
      }
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
      template <ArrayKernelName DK,ArrayKernelName LK>
      void imprint(Array2D<T,DK,LK,false> const& A) {
        assert((bool)A);
        Array<UInt> SZ(A.size());
        for(size_type i=0;i<SZ.size();++i)  SZ[i]=A[i].size();
        allocate(SZ);
        SZ.reset();
        for(unsigned int i=0;i<A.size();++i)
        for(unsigned int j=0;j<A[i].size();++j)
          __imprint((*this)[i][j],A[i][j]);
      }
      void swap(Type& A) {
        ParentType::swap((ParentType&)A);
        std::swap(_data,A._data);
      }

  };

}

#endif

