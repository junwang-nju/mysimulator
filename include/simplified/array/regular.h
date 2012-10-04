
#ifndef _Array_Regular_H_
#define _Array_Regular_H_

#include "array/interface.h"
#include "array/expression.h"

namespace mysimulator {

  template <typename T>
  class Array<T,ArrayFormat::Regular>
      : public ArrayExpression<Array<T,ArrayFormat::Regular>,T>,
        public ArrayContainer<T,ArrayFormat::Regular> {

    public:

      static_assert(!__intrinsic_flag<T>::FG,
                    "For Intrinsic Type, please use Intrinsic<T>!\n");

      typedef Array<T,ArrayFormat::Regular>             Type;
      typedef ArrayExpression<Type,T>                   ParentTypeA;
      typedef ArrayContainer<T,ArrayFormat::Regular>    ParentTypeB;
      typedef typename ParentTypeB::value_type          value_type;
      typedef unsigned int size_type;
      typedef value_type& reference;
      typedef const value_type& const_reference;

      Array() : ParentTypeA(), ParentTypeB() {}
      Array(size_type size) : ParentTypeA(), ParentTypeB(size) {}
      Array(const Type& A) : Array(A.size()) { operator=(A); }
      ~Array() { ParentTypeB::reset(); }

      template <typename E,typename ET>
      Array(const ArrayExpression<E,ET> & EA) : Array(EA.size()) {
        operator=(EA);
      }
      template <typename E,typename ET>
      Array(const ArrayExpression<E,ET> && EA) : Array(EA.size()) {
        operator=(EA);
      }

      operator bool() const { return ParentTypeB::operator bool(); }
      size_type size() const { return ParentTypeB::size(); }
      reference operator[](size_type i) { return ParentTypeB::operator[](i); }
      const_reference operator[](size_type i) const {
        return ParentTypeB::operator[](i);
      }

      template <typename E,typename ET>
      Type& operator=(const ArrayExpression<E,ET>& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i) (*this)[i]=EA[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator=(const ArrayExpression<E,ET>&& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i) (*this)[i]=EA[i];
        return *this;
      }

      Type& operator=(const Type& A) { return operator=<Type,T>(A); }
      Type& operator=(const T& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i) (*this)[i]=D;
        return *this;
      }

  };

}

#endif

