
#ifndef _Array_Container_Base_H_
#define _Array_Container_Base_H_

#include "memory/accessed-ptr.h"
#include "basic/imprint.h"
#include "array/content-selector.h"
#include <algorithm>

namespace mysimulator {

  template <typename T>
  class ArrayContainerBase : private ArrayContentSelector<T> {

    public:

      typedef ArrayContainerBase<T>  Type;
      typedef typename ArrayContentSelector<T>::monomer_type monomer_type;
      typedef monomer_type* pointer;
      typedef monomer_type& reference;
      typedef const monomer_type* const_pointer;
      typedef const monomer_type& const_reference;
      typedef unsigned int size_type;

    protected:

      accessed_ptr<monomer_type> _pdata;
      size_type                _ndata;

    public:

      ArrayContainerBase() : _pdata(), _ndata(0U) {}
      ArrayContainerBase(size_type size) : ArrayContainerBase() {
        allocate(size);
      }
      ArrayContainerBase(const Type&) = delete;
      ArrayContainerBase(Type&&) = delete;
      virtual ~ArrayContainerBase() { reset(); }

      operator bool() const { return (bool)_pdata && (_ndata>0U); }
      size_type size() const { return _ndata; }
      reference operator[](size_type i) {
        assert(i<_ndata);
        return _pdata[i];
      }
      const_reference operator[](size_type i) const {
        assert(i<_ndata);
        return _pdata[i];
      }
      pointer head() const { return _pdata.get(); }
      const_pointer end() const { return head()+_ndata; }

      Type& operator=(const Type&) = delete;
      Type& operator=(Type&&) = delete;
      template <typename Y>
      Type& operator=(const ArrayContainerBase<Y>&) = delete;

      virtual void allocate(size_type size) = 0;

      void reset() { _pdata.reset(); _ndata=0U; }
      template <typename Y>
      void imprint_structure(const ArrayContainerBase<Y>& AC) {
        assert((bool)AC);  this->allocate(AC.size());
      }
      template <typename Y>
      void imprint(const ArrayContainerBase<Y>& AC) {
        imprint_structure(AC);
        pointer p=head();
        const_pointer e=end();
        typename ArrayContainerBase<Y>::pointer q=AC.head();
        for(;p!=e;) __imprint(*(p++),*(q++));
      }
      void refer(const Type& AC) {
        reset(); _pdata=AC._pdata; _ndata=AC._ndata;
      }
      void refer(const Type& AC, size_type bg, size_type num) {
        assert(bg+num<=AC.size());
        reset();
        _pdata.reset(AC._pdata,bg);
        _ndata=num;
      }

      void _refer_align16(const Type& AC) {
        assert(AC._pdata.__aligned16());
        refer(AC);
      }
      void _refer_align16(const Type& AC, size_type bg, size_type num) {
        assert(AC._pdata.__aligned16());
        assert(((bg*sizeof(T))&0xFU)==0);
        assert(((num*sizeof(T))&0xFU)==0);
        refer(AC,bg,num);
      }

      void swap(Type& AC) {
        std::swap(_pdata,AC._pdata);
        std::swap(_ndata,AC._ndata);
      }

  };

  template <typename T,typename Y>
  void __imprint(ArrayContainerBase<T>& AC,const ArrayContainerBase<Y>& YAC) {
    AC.imprint(YAC);
  }

}

namespace std {

  template <typename T>
  void swap(mysimulator::ArrayContainerBase<T>& AC1,
            mysimulator::ArrayContainerBase<T>& AC2) {
    AC1.swap(AC2);
  }

}

#endif

