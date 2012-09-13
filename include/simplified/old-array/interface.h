
#ifndef _Array_Interface_H_
#define _Array_Interface_H_

#include "array/expression.h"

namespace mysimulator {

  template <typename T,ArrayFormat AF=ArrayFormat::Regular>
  class Array : public ArrayExpression<Array<T,AF>,T> {

    public:

      typedef Array<T,AF>   Type;
      typedef ArrayExpression<Array<T,AF>,T>  ParentType;
      typedef T         value_type;
      typedef T&        reference;
      typedef const T&  const_reference;
      typedef T*        pointer;
      typedef const T*  const_pointer;
      typedef unsigned int size_type;

      template <typename Y,ArrayFormat YAF> friend class Array;

    protected:

      ArrayContainer<T,AF> _data;

    public:

      Array() : ParentType(), _data() {}
      Array(unsigned int size) : ParentType(), _data(size) {}
      ~Array() { _data.~ArrayContainer(); }

      operator bool() const { return (bool)_data; }
      unsigned int size() const { return _data.size(); }
      reference operator[](unsigned int i) { return _data[i]; }
      const_reference operator[](unsigned int i) const { return _data[i]; }
      pointer head() const { return _data.head(); }
      const_pointer end() const { return _data.end(); }

      void allocate(unsigned int size) { _data.allocate(size); }
      template <typename Y,ArrayFormat YAF>
      void imprint_structure(const Array<Y,YAF>& A) {
        _data.imprint_structure(A._data);
      }
      template <typename Y,ArrayFormat YAF>
      void imprint(const Array<Y,YAF>& A) { _data.imprint(A._data); }

      template <typename E,typename ET>
      Array(ArrayExpression<E,ET> const& A) {
        allocate(A.size());
        operator=(A);
      }
      Array(const Type& A) : Array() { imprint(A); operator=(A); }

      template <typename Y,ArrayFormat YAF>
      Type& operator=(const Array<Y,YAF>& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(unsigned int i=0;i<size();++i)  _data[i]=A[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator=(ArrayExpression<E,ET> const& A) {
        assert((bool)(*this));
        assert(size()<=A.size());
        for(unsigned int i=0;i<size();++i)  _data[i]=A[i];
        return *this;
      }

  };

  template <typename T,ArrayFormat AF,typename Y,ArrayFormat YAF>
  void __imprint(Array<T,AF>& A, const Array<Y,YAF>& B) { A.imprint(B); }

}

#endif

