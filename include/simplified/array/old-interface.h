
#ifndef _Array_Interface_H_
#define _Array_Interface_H_

#include "memory/accessed-ptr.h"
#include "basic/imprint.h"

namespace mysimulator {

  enum class ArrayFormat { RegularArray, ShortDataArray, LongDataArray };

  template <typename T,ArrayFormat AF=ArrayFormat::RegularArray>
  class Array {

    public:

      typedef Array<T,AF>    Type;
      typedef T* pointer;
      typedef const T* const_pointer;
      typedef T& reference;
      typedef const T& const_reference;

    protected:

      accessed_ptr<T>   _pdata;
      unsigned int      _ndata;

    public:

      Array() : _pdata(), _ndata(0U) {}
      Array(unsigned int size) : Array() { allocate(size); }
      Array(const Type&) = delete;
      virtual ~Array() { _pdata.~accessed_ptr(); _ndata=0; }

      operator bool() const { return (bool)_pdata && (_ndata>0); }
      unsigned int size() const { return _ndata; }
      template <typename Y,ArrayFormat YAF>
      Type& operator=(const Array<Y,YAF>& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(_ndata<=A.size());
        Y* q=A.head();
        for(pointer p=head();p!=end();) *(p++)=*(q++);
        return *this;
      }
      Type& operator=(const Type& A) { return operator=<T,AF>(A); }
      template <typename Y>
      Type& operator=(const Y& D) {
        assert((bool)(*this));
        for(pointer p=head();p!=end();) *(p++)=D;
        return *this;
      }
      reference operator[](unsigned int i) {
        assert(i<_ndata);
        return _pdata[i];
      }
      const_reference operator[](unsigned int i) const {
        assert(i<_ndata);
        return _pdata[i];
      }
      pointer head() const { return _pdata.get(); }
      const_pointer end() const { return _pdata.get()+_ndata; }

      virtual void allocate(unsigned int size) {
        this->~Array();
        _pdata.reset(new T[size]);
        _pdata.set_deleter(operator delete[]);
        _ndata=size;
      }
      void refer(const Type& A) {
        this->~Array(); _pdata=A._pdata; _ndata=A._ndata;
      }
      void refer(const Type& A, unsigned int bg, unsigned int num) {
        assert(bg+num<=A.size());
        this->~Array();
        _pdata.reset(A.get()+bg,bg==0?AccessContentName::GlobalUsed:
                                      AccessContentName::PartUsed);
        _ndata=num;
      }
      template <typename Y,ArrayFormat YAF>
      void imprint_structure(const Array<Y,YAF>& A) {
        assert((bool)A);
        allocate(A.size());
      }
      template <typename Y,ArrayFormat YAF>
      void imprint(const Array<Y,YAF>& A) {
        imprint_structure(A);
        pointer p=head(), q=A.head();
        for(;p!=end();) __imprint(*(p++),*(q++));
      }
      template <typename Y,ArrayFormat YAF>
      void copy(const Array<Y,YAF>& A, unsigned int num,
                unsigned int bg=0, unsigned int dlt=1,
                unsigned int bgA=0, unsigned int dltA=1) {
        assert((bool)(*this));
        assert((bool)A);
        unsigned int e=bg+num*dlt, eA=bgA+num*dltA;
        assert(e<=size());
        assert(eA<=A.size());
        pointer p=head()+bg;
        Y* q=A.head()+bgA;
        const_pointer ep=p+e;
        for(;p!=ep;p+=dlt,q+=dltA)  (*p)=(*q);
      }
      template <typename Y>
      void fill(const Y& D, unsigned int bg=0, unsigned int dlt=1) {
        unsigned int num=(size()-bg)/dlt+((size()-bg)%dlt>0?1:0);
        pointer p=head()+bg;
        const_pointer ep=p+num*dlt;
        for(;p!=ep;p+=dlt)  (*p)=D;
      }

      void swap(Type& A) {
        std::swap(_pdata,A._pdata);
        std::swap(_ndata,A._ndata);
      }

  };

  template <typename T,ArrayFormat AF,typename Y,ArrayFormat YAF>
  void __imprint(Array<T,AF>& A, const Array<Y,YAF>& B) { A.imprint(B); }

}

#include <algorithm>

namespace std {

  template <typename T,mysimulator::ArrayFormat AF>
  void swap(mysimulator::Array<T,AF>& A, mysimulator::Array<T,AF>& B) {
    A.swap(B);
  }

}

namespace mysimulator {

  static const unsigned int ShortThresholdByte=500;

}

#include "array/short-data-array-interface.h"
#include "array/long-data-array-interface.h"

#endif

