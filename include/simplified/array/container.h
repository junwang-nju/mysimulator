
#ifndef _Array_Container_H_
#define _Array_Container_H_

#include "memory/accessed-ptr.h"
#include "basic/imprint.h"

namespace mysimulator {

  enum class ArrayFormat { Regular, Data, ShortData, LargeData };

  template <typename T,ArrayFormat AF=ArrayFormat::Regular>
  class ArrayContainer {

    public:

      typedef ArrayContainer<T,AF>    Type;
      typedef T             value_type;
      typedef T&            reference;
      typedef const T&      const_reference;
      typedef T*            pointer;
      typedef const T*      const_pointer;
      typedef unsigned int  size_type;

    protected:

      accessed_ptr<T>   _pdata;
      unsigned int      _ndata;

    public:

      ArrayContainer() : _pdata(), _ndata(0U) {}
      ArrayContainer(unsigned int size) : ArrayContainer() { allocate(size); }
      ArrayContainer(const Type&) = delete;
      virtual ~ArrayContainer() { _pdata.~accessed_ptr(); _ndata=0; }

      operator bool() const { return (bool)_pdata && (_ndata>0); }
      unsigned int size() const { return _ndata; }
      reference operator[](unsigned int i) {
        assert(i<_ndata);
        return _pdata[i];
      }
      const_reference operator[](unsigned int i)  const {
        assert(i<_ndata);
        return _pdata[i];
      }
      pointer head() const { return _pdata.get(); }
      const_pointer end() const { return head()+_ndata; }

      template <typename Y,ArrayFormat YAF>
      Type& operator=(const ArrayContainer<Y,YAF>&) = delete;

      virtual void allocate(unsigned int size) {
        this->~ArrayContainer();
        _pdata.reset(new T[size]);
        _pdata.set_deleter(operator delete[]);
        _ndata=size;
      }
      template <typename Y,ArrayFormat YAF>
      void imprint_structure(const ArrayContainer<Y,YAF>& A) {
        assert((bool)A);
        allocate(A.size());
      }
      template <typename Y,ArrayFormat YAF>
      void imprint(const ArrayContainer<Y,YAF>& A) {
        imprint_structure(A);
        pointer p=head(), q=A.head();
        for(pointer p=head(),q=A.head();p!=end();)  __imprint(*(p++),*(q++));
      }

  };

  template <typename T,ArrayFormat AF,typename Y,ArrayFormat YAF>
  void __imprint(ArrayContainer<T,AF>& A,const ArrayContainer<Y,YAF>& B) {
    A.imprint(B);
  }

}

#endif

