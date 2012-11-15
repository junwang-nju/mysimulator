
#ifndef _Array_Intrinsic_H_
#define _Array_Intrinsic_H_

#include "array/def.h"
#include "array/monomer-type.h"
#include "array/kernel/name.h"
#include "array/kernel/simple.h"
#include "array/kernel/sse.h"
#include "basic/memory/access-pointer.h"
#include "array/expression/operation.h"

namespace mysimulator {

  template <typename T>
  class Array<Intrinsic<T>,true> {

    public:

      typedef Array<Intrinsic<T>,true>    Type;
      typedef typename __array_monomer<Intrinsic<T>>::Type monomer_type;
      typedef T value_type;
      typedef monomer_type * pointer;
      typedef monomer_type & reference;
      typedef const monomer_type * const_pointer;
      typedef const monomer_type & const_reference;
      typedef unsigned int size_type;

      typedef void (*_alloc_type)(Type&,size_type);
      typedef void (*_copy_type)(Type&,const Type&);
      typedef void (*_mono_copy_type)(Type&,const monomer_type&);
      typedef void (*_refer_type)(Type&,const Type&,size_type,size_type);

      static const bool _is_SSE_valid;

      ArrayKernelName           _tag;
      access_ptr<monomer_type>  _pdata;
      size_type                 _ndata;
      size_type                 _n128;
      _alloc_type               _allocator;
      _copy_type                _copier;
      _mono_copy_type           _mono_copier;
      _refer_type               _referer;

    private:

      void _clear_kernel() {
        _allocator = nullptr;
        _copier = nullptr;
        _mono_copier = nullptr;
        _referer = nullptr;
      }

    public:

      Array() : _tag(ArrayKernelName::Unknown), _pdata(), _ndata(0U),
                _n128(0U), _allocator ( nullptr ), _copier ( nullptr ),
                _mono_copier ( nullptr ), _referer ( nullptr ) {}
      Array(size_type size, ArrayKernelName KN=ArrayKernelName::SSE) : Array() {
        allocate(size,KN);
      }
      Array(const Type& A) : Array() {
        allocate( A.size(), A.KernelName() );
        operator=(A);
      }
      Array(Type&& A) : Array() { swap(A); }
      ~Array() { reset(); _clear_kernel(); }

      operator bool() const { return (bool)_pdata && _ndata>0U; }
      ArrayKernelName KernelName() const { return _tag; }
      size_type size() const { return _ndata; }
      size_type size128() const { return _n128; }
      pointer head() const { return _pdata.get(); }
      const_pointer end() const { return head()+size(); }
      reference operator[](size_type i) { assert(i<_ndata); return _pdata[i]; }
      const_reference operator[](size_type i) const {
        assert(i<_ndata);
        return _pdata[i];
      }

      Type& operator=(const Type& A) {
        assert ( _copier != nullptr );
        _copier(*this,A);
        return *this;
      }
      Type& operator=(const monomer_type& D) {
        assert ( _mono_copier != nullptr );
        _mono_copier(*this,D);
        return *this;
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((value_type)((T1)D));
      }

      template <typename EA,typename EB>
      Type& operator=(ArraySum<EA,EB> const& E) {
        __assign_sum_simple<Intrinsic<T>,EA,EB>(*this,E);
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator=(ArraySum<EA,EB,value_type,true> const& E) {
        __assign_sum_simple<Intrinsic<T>,EA,EB>(*this,E);
        return *this;
      }

      template <typename EA,typename EB>
      Type& operator=(ArraySub<EA,EB> const& E) {
        __assign_sub_simple<Intrinsic<T>,EA,EB>(*this,E);
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator=(ArraySub<EA,EB,value_type,true> const& E) {
        __assign_sub_simple<Intrinsic<T>,EA,EB>(*this,E);
        return *this;
      }

      template <typename EA,typename EB>
      Type& operator=(ArrayMul<EA,EB> const& E) {
        __assign_mul_simple<Intrinsic<T>,EA,EB>(*this,E);
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayMul<EA,EB,value_type,true> const& E) {
        __assign_mul_simple<Intrinsic<T>,EA,EB>(*this,E);
        return *this;
      }

      template <typename EA,typename EB>
      Type& operator=(ArrayDiv<EA,EB> const& E) {
        __assign_div_simple<Intrinsic<T>,EA,EB>(*this,E);
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayDiv<EA,EB,value_type,true> const& E) {
        __assign_div_simple<Intrinsic<T>,EA,EB>(*this,E);
        return *this;
      }

      template <typename E>
      Type& operator+=(E const& A) { return operator=((*this)+A); }
      template <typename E>
      Type& operator-=(E const& A) { return operator=((*this)-A); }
      template <typename E>
      Type& operator*=(E const& A) { return operator=((*this)*A); }
      template <typename E>
      Type& operator/=(E const& A) { return operator=((*this)/A); }

      void reset() {
        _n128 = 0;
        _ndata = 0;
        _pdata.reset();
        _tag = ArrayKernelName::Unknown;
      }
      void reset_kernel(ArrayKernelName KName = ArrayKernelName::Simple) {
        assert( (_tag==ArrayKernelName::Unknown) ||
                ! ( (KName==ArrayKernelName::SSE) &&
                    (_tag!=ArrayKernelName::SSE) ) );
        _tag = KName;
        switch ( _tag ) {
          case ArrayKernelName::Simple:
            _allocator = __allocate_simple<Intrinsic<T>>;
            _copier = __copy_simple<Intrinsic<T>>;
            _mono_copier = __mono_copy_simple<Intrinsic<T>>;
            _referer = __refer_simple<Intrinsic<T>>;
            break;
          case ArrayKernelName::SSE:
            _allocator = __allocate_sse<T>;
            _copier = __copy_sse<T>;
            _mono_copier = __mono_copy_sse<T>;
            _referer = __refer_sse<T>;
            break;
          default:
            throw "Kernel Not Implemented OR Not Valid!\n";
        }
      }
      void allocate(size_type size,
                    ArrayKernelName KName = ArrayKernelName::Simple) {
        reset();
        reset_kernel(KName);
        _allocator(*this,size);
      }
      void refer(const Type& A) {
        reset();
        reset_kernel(A.KernelName());
        _pdata = A._pdata;
        _ndata = A._ndata;
        _n128 = A._n128;
      }
      void refer(const Type& A, size_type bg, size_type num) {
        assert ( _referer != nullptr );
        reset();
        reset_kernel(A.KernelName());
        _referer(*this,A,bg,num);
      }
      template <typename Y>
      void imprint_structure(const Array<Y>& A) {
        assert( (bool)A );
        allocate(A.size());
      }
      void swap(Type& A) {
        std::swap(_tag,A._tag);
        std::swap(_pdata,A._pdata);
        std::swap(_ndata,A._ndata);
        std::swap(_n128,A._n128);
        std::swap(_allocator,A._allocator);
        std::swap(_copier,A._copier);
        std::swap(_mono_copier,A._mono_copier);
        std::swap(_referer,A._referer);
      }

  };

  template <typename T>
  const bool Array<Intrinsic<T>,true>::_is_SSE_valid = false;

  template <>
  const bool Array<Double>::_is_SSE_valid = true;

  template <>
  const bool Array<Float>::_is_SSE_valid = true;

  template <>
  const bool Array<Int>::_is_SSE_valid = true;

  static_assert( sizeof(int)==sizeof(long),
                 "Sizes of Int and Long are not Equal!\n");
  template <>
  const bool Array<Long>::_is_SSE_valid = true;

  template <typename T>
  typename __sse_value<T>::Type&
  value128(Array<Intrinsic<T>,true>& A, unsigned int i) {
    assert(A.KernelName()==ArrayKernelName::SSE);
    return ((typename __sse_value<T>::Type*)(A.head()))[i];
  }
  template <typename T>
  typename __sse_value<T>::Type
  value128(Array<Intrinsic<T>,true> const& A, unsigned int i) {
    assert(A.KernelName()==ArrayKernelName::SSE);
    return ((typename __sse_value<T>::Type*)(A.head()))[i];
  }

  template<>
  template <typename EA,typename EB>
  Array<Double>&
  Array<Double>::operator=(ArraySum<EA,EB,double,true> const& E) {
    if(_tag==ArrayKernelName::SSE && E.KernelName()==ArrayKernelName::SSE )
      __assign_sum_sse<Double,EA,EB>(*this,E);
    else
      __assign_sum_simple<Double,EA,EB>(*this,E);
    return *this;
  }

  template <>
  template <typename EA,typename EB>
  Array<Int>&
  Array<Int>::operator=(ArraySum<EA,EB,int,true> const& E) {
    if(_tag==ArrayKernelName::SSE && E.KernelName()==ArrayKernelName::SSE )
      __assign_sum_sse<Int,EA,EB>(*this,E);
    else
      __assign_sum_simple<Int,EA,EB>(*this,E);
    return *this;
  }

  template <>
  template <typename EA,typename EB>
  Array<Float>&
  Array<Float>::operator=(ArraySum<EA,EB,float,true> const& E) {
    if(_tag==ArrayKernelName::SSE && E.KernelName()==ArrayKernelName::SSE )
      __assign_sum_sse<Float,EA,EB>(*this,E);
    else
      __assign_sum_simple<Float,EA,EB>(*this,E);
    return *this;
  }

  template <>
  template <typename EA,typename EB>
  Array<Double>&
  Array<Double>::operator=(ArraySub<EA,EB,double,true> const& E) {
    if(_tag==ArrayKernelName::SSE && E.KernelName()==ArrayKernelName::SSE )
      __assign_sub_sse<Double,EA,EB>(*this,E);
    else
      __assign_sub_simple<Double,EA,EB>(*this,E);
    return *this;
  }
  template <>
  template <typename EA,typename EB>
  Array<Int>&
  Array<Int>::operator=(ArraySub<EA,EB,int,true> const& E) {
    if(_tag==ArrayKernelName::SSE && E.KernelName()==ArrayKernelName::SSE )
      __assign_sub_sse<Int,EA,EB>(*this,E);
    else
      __assign_sub_simple<Int,EA,EB>(*this,E);
    return *this;
  }
  template <>
  template <typename EA,typename EB>
  Array<Float>&
  Array<Float>::operator=(ArraySub<EA,EB,float,true> const& E) {
    if(_tag==ArrayKernelName::SSE && E.KernelName()==ArrayKernelName::SSE )
      __assign_sub_sse<Float,EA,EB>(*this,E);
    else
      __assign_sub_simple<Float,EA,EB>(*this,E);
    return *this;
  }

  template <>
  template <typename EA,typename EB>
  Array<Double>&
  Array<Double>::operator=(ArrayMul<EA,EB,double,true> const& E) {
    if(_tag==ArrayKernelName::SSE && E.KernelName()==ArrayKernelName::SSE )
      __assign_mul_sse<Double,EA,EB>(*this,E);
    else
      __assign_mul_simple<Double,EA,EB>(*this,E);
    return *this;
  }
  template <>
  template <typename EA,typename EB>
  Array<Int>&
  Array<Int>::operator=(ArrayMul<EA,EB,int,true> const& E) {
    if(_tag==ArrayKernelName::SSE && E.KernelName()==ArrayKernelName::SSE )
      __assign_mul_sse<Int,EA,EB>(*this,E);
    else
      __assign_mul_simple<Int,EA,EB>(*this,E);
    return *this;
  }
  template <>
  template <typename EA,typename EB>
  Array<Float>&
  Array<Float>::operator=(ArrayMul<EA,EB,float,true> const& E) {
    if(_tag==ArrayKernelName::SSE && E.KernelName()==ArrayKernelName::SSE )
      __assign_mul_sse<Float,EA,EB>(*this,E);
    else
      __assign_mul_simple<Float,EA,EB>(*this,E);
    return *this;
  }

  template <>
  template <typename EA,typename EB>
  Array<Double>&
  Array<Double>::operator=(ArrayDiv<EA,EB,double,true> const& E) {
    if(_tag==ArrayKernelName::SSE && E.KernelName()==ArrayKernelName::SSE )
      __assign_div_sse<Double,EA,EB>(*this,E);
    else
      __assign_div_simple<Double,EA,EB>(*this,E);
    return *this;
  }
  template <>
  template <typename EA,typename EB>
  Array<Float>&
  Array<Float>::operator=(ArrayDiv<EA,EB,float,true> const& E) {
    if(_tag==ArrayKernelName::SSE && E.KernelName()==ArrayKernelName::SSE )
      __assign_div_sse<Float,EA,EB>(*this,E);
    else
      __assign_div_simple<Float,EA,EB>(*this,E);
    return *this;
  }

}

#endif

