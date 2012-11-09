
#ifndef _Array_General_H_
#define _Array_General_H_

#include "array/def.h"
#include "array/monomer-type.h"
#include "array/kernel/name.h"
#include "array/kernel/simple.h"
#include "basic/memory/access-pointer.h"

namespace mysimulator {

  template <typename T>
  class Array<T,false> {

    public:

      typedef Array<T,false>    Type;
      typedef typename __array_monomer<T>::Type   monomer_type;
      typedef monomer_type * pointer;
      typedef monomer_type & reference;
      typedef const monomer_type * const_pointer;
      typedef const monomer_type & const_reference;
      typedef unsigned int size_type;

      typedef void (*_alloc_type)(Type&,size_type);
      typedef void (*_copy_type)(Type&,const Type&);
      typedef void (*_mono_copy_type)(Type&,const monomer_type&);
      typedef void (*_refer_type)(Type&,const Type&,size_type,size_type);

      ArrayKernelName           _tag;
      access_ptr<monomer_type>  _pdata;
      size_type                 _ndata;
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
                _allocator ( nullptr ), _copier ( nullptr ),
                _mono_copier ( nullptr ), _referer ( nullptr ) {}
      Array(size_type size, ArrayKernelName KN) : Array() {
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

      void reset() {
        _ndata = 0;
        _pdata.reset();
        _tag = ArrayKernelName::Unknown;
      }
      void reset_kernel(ArrayKernelName KName = ArrayKernelName::Simple) {
        _tag = KName;
        switch ( _tag ) {
          case ArrayKernelName::Simple:
            _allocator = _allocate_simple<T>;
            _copier = _copy_simple<T>;
            _mono_copier = _mono_copy_simple<T>;
            _referer = _refer_simple<T>;
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
      }
      void refer(const Type& A, size_type bg, size_type num) {
        assert ( _referer != nullptr );
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
        std::swap(_allocator,A._allocator);
        std::swap(_copier,A._copier);
        std::swap(_mono_copier,A._mono_copier);
        std::swap(_referer,A._referer);
      }

  };

}

#endif

