
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
      ~Array() { reset(); }

      operator bool() const { return (bool)_data; }
      size_type size() const { return _data.size(); }
      reference operator[](unsigned int i) { return _data[i]; }
      const_reference operator[](unsigned int i) const { return _data[i]; }

      void reset() { _data.reset(); }

      template <typename Y,ArrayFormat YAF>
      Type& operator=(const Array<Y,YAF>& A) {
        static_assert(!((AF==ArrayFormat::LargeData)&&
                        (YAF==ArrayFormat::ShortData)),
                      "Cannot Assign Short to Large!\n");
        assert((bool)(*this));
        assert((bool)A);
        assert(this->size()<=A.size());
        for(size_type i=0;i<this->size();++i) (*this)[i]=A[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator=(const ArrayExpression<E,ET>& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(this->size()<=EA.size());
        for(size_type i=0;i<this->size();++i) (*this)[i]=EA[i];
        return *this;
      }

  };

}

#endif

