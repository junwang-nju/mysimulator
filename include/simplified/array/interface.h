
#ifndef _Array_Interface_H_
#define _Array_Interface_H_

#include "array/container.h"
#include "array/expression.h"

namespace mysimulator {

  template <typename T,ArrayFormat AF>
  class Array : public ArrayExpression<Array<T,AF>,T> {

    public:

      typedef Array<T,AF>   Type;
      typedef ArrayExpression<Type,T> ParentType;
      typedef ArrayContainer<T,AF>  container_type;
      typedef unsigned int size_type;
      typedef T   value_type;
      typedef T*  pointer;
      typedef const T* const_pointer;
      typedef T&  reference;
      typedef const T& const_reference;

    private:

      container_type _data;

    public:

      Array() : ParentType(), _data() {}
      Array(size_type size) : ParentType(), _data(size) {}
      Array(const Type& A) : Array(A.size()) { operator=(A); }
      template <typename E,typename ET>
      Array(const ArrayExpression<E,ET>& EA) : Array(EA.size()) {
        operator=(EA);
      }
      template <typename E,typename ET>
      Array(const ArrayExpression<E,ET>&& EA) : Array(EA.size()) {
        operator=(EA);
      }
      ~Array() { reset(); }

      operator bool() const { return (bool)_data; }
      size_type size() const { return _data.size(); }
      reference operator[](unsigned int i) { return _data[i]; }
      const_reference operator[](unsigned int i) const { return _data[i]; }
      pointer head() const { return _data.head(); }
      const_pointer end() const { return _data.end(); }
      container_type const& __container() const { return _data; }

      void reset() { _data.reset(); }
      void allocate(size_type size) { _data.allocate(size); }
      template <typename Y,ArrayFormat YAF>
      void imprint_structure(const Array<Y,YAF>& A) {
        _data.imprint_structure(A.__container());
      }
      template <typename Y,ArrayFormat YAF>
      void imprint(const Array<Y,YAF>& A) { _data.imprint(A.__container()); }
      void refer(const Type& A) { _data.refer(A._data); }
      void refer(const Type& A,size_type bg,size_type num) {
        _data.refer(A._data,bg,num);
      }

      void swap(Type& A) { _data.swap(A._data); }

      template <typename E,typename ET>
      Type& operator=(const ArrayExpression<E,ET>&& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i) (*this)[i]=EA[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator=(const ArrayExpression<E,ET>& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i) (*this)[i]=EA[i];
        return *this;
      }
      Type& operator=(const Type& A) {
        return operator=<Array<T,AF>,T>(A);
      }

  };

  template <typename T,ArrayFormat AF,typename Y,ArrayFormat YAF>
  void __imprint(Array<T,AF>& A, const Array<Y,YAF>& YA) { A.imprint(YA); }

}

namespace std {

  template <typename T,mysimulator::ArrayFormat AF>
  void swap(mysimulator::Array<T,AF>& A1, mysimulator::Array<T,AF>& A2) {
    A1.swap(A2);
  }

}

#include "array/expression-sum.h"

#endif

