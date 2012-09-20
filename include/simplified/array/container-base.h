
#ifndef _Array_Container_Base_H_
#define _Array_Container_Base_H_

#include "memory/accessed-ptr.h"
#include "basic/imprint.h"
#include "array/content-selector.h"
#include <algorithm>

namespace mysimulator {

  enum class ArrayFormat { Regular, Data, ShortData, LargeData };

  template <typename T,ArrayFormat AF=ArrayFormat::Regular>
  class ArrayContainerBase : private ArrayContentSelector<T> {

    public:

      typedef ArrayContainerBase<T,AF>  Type;
      typedef typename ArrayContentSelector<T>::value_type value_type;
      typedef value_type* pointer;
      typedef value_type& reference;
      typedef const value_type* const_pointer;
      typedef const value_type& const_reference;
      typedef unsigned int size_type;

    protected:

      accessed_ptr<value_type> _pdata;
      size_type                _ndata;

    public:

      ArrayContainerBase() : _pdata(), _ndata(0U) {}
      ArrayContainerBase(size_type size) : ArrayContainerBase() {
        allocate(size);
      }
      ArrayContainerBase(const Type&) = delete;
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
      template <typename Y,ArrayFormat YAF>
      Type& operator=(const ArrayContainerBase<Y,YAF>&) = delete;

      virtual void allocate(size_type size) = 0;

      void reset() { _pdata.reset(); _ndata=0U; }
      template <typename Y,ArrayFormat YAF>
      void imprint_structure(const ArrayContainerBase<Y,YAF>& AC) {
        assert((bool)AC);  this->allocate(AC.size());
      }
      template <typename Y,ArrayFormat YAF>
      void imprint(const ArrayContainerBase<Y,YAF>& AC) {
        imprint_structure(AC);
        pointer p=head();
        const_pointer e=end();
        typename ArrayContainerBase<Y,YAF>::pointer q=AC.head();
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

      void swap(Type& AC) {
        std::swap(_pdata,AC._pdata);
        std::swap(_ndata,AC._ndata);
      }

  };

  template <typename T,ArrayFormat AF,typename Y,ArrayFormat YAF>
  void __imprint(ArrayContainerBase<T,AF>& AC,
                 const ArrayContainerBase<Y,YAF>& YAC) {
    AC.imprint(YAC);
  }

}

namespace std {

  template <typename T,mysimulator::ArrayFormat AF>
  void swap(mysimulator::ArrayContainerBase<T,AF>& AC1,
            mysimulator::ArrayContainerBase<T,AF>& AC2) {
    AC1.swap(AC2);
  }

}

#endif

