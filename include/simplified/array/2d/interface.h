
#ifndef _Array_2D_Interface_H_
#define _Array_2D_Interface_H_

#include "array/2d/expression.h"
#include "array/2d/container.h"

namespace mysimulator {

  template <typename T,bool _vflag=ArrayContentSelector<T>::_has_value>
  class Array2D {
    public:
      typedef Array2D<T>  Type;
      Array2D() = delete;
      Array2D(const Type&) = delete;
      Type& operator=(const Type&) = delete;
      ~Array2D() {}
  };

  template <typename T>
  class Array2D<T,true> : public Array2DExpression<Array2D<T,true>,T>,
                          public Array2DContainer<T> {

    public:

      typedef Array2D<T,true>   Type;
      typedef Array2DExpression<Type,T>   ParentTypeA;
      typedef Array2DContainer<T>  ParentTypeB;
      typedef unsigned int size_type;
      typedef typename T::value_type  value_type;
      typedef typename ArrayContentSelector<T>::monomer_type monomer_type;
      typedef monomer_type& reference;
      typedef const monomer_type& const_reference;

      Array2D() : ParentTypeA(), ParentTypeB() {}
      Array2D(size_type m,size_type n) : ParentTypeA(), ParentTypeB(m,n) {}
      Array2D(const Type& A) : Array2D() { this->imprint(A); operator=(A); }
      Array2D(Type&& A) : ParentTypeA(), ParentTypeB((ParentTypeB&&)A) {}
      ~Array2D() { ParentTypeB::reset(); }

      operator bool() const { return ParentTypeB::operator bool(); }
      size_type size() const { return ParentTypeB::size(); }
      reference operator()(size_type i,size_type j) {
        return ParentTypeB::operator()(i,j);
      }
      const_reference operator()(size_type i,size_type j) const {
        return ParentTypeB::operator()(i,j);
      }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(IsSameSize(*this,A));
        typedef typename ParentTypeB::ParentTypeA PType;
        PType::operator=((PType const&)A);
        return *this;
      }
      template <typename E,typename ET>
      Type& operator=(const Array2DExpression<E,ET>& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(IsSameSize(*this,(Type const)EA));
        for(size_type i=0,m;i<size();++i) {
          m=(*this)[i].size();
          for(size_type j=0;j<m;++j)
            (*this)[i][j]=EA(i,j);
        }
        return *this;
      }
      Type& operator=(const monomer_type& D) {
        assert((bool)(*this));
        typedef typename ParentTypeB::ParentTypeA PType;
        PType::operator=(D);
        return *this;
      }
      Type& operator=(const value_type& D) {
        assert((bool)(*this));
        typedef typename ParentTypeB::ParentTypeA PType;
        PType::operator=(D);
        return *this;
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((value_type)((T1)D));
      }

  };

  template <typename T>
  class Array2D<T,false> : public Array2DExpression<Array2D<T,false>,T>,
                           public Array2DContainer<T> {

    public:

      typedef Array2D<T,false>    Type;
      typedef Array2DExpression<Type,T>   ParentTypeA;
      typedef Array2DContainer<T>  ParentTypeB;
      typedef unsigned int size_type;
      typedef typename ArrayContentSelector<T>::monomer_type monomer_type;
      typedef monomer_type& reference;
      typedef const monomer_type& const_reference;

      Array2D() : ParentTypeA(), ParentTypeB() {}
      Array2D(size_type m,size_type n) : ParentTypeA(), ParentTypeB(m,n) {}
      Array2D(const Type& A) : Array2D() { this->imprint(A); operator=(A); }
      Array2D(Type&& A) : ParentTypeA(), ParentTypeB((ParentTypeB&&)A) {}
      ~Array2D() { ParentTypeB::reset(); }

      operator bool() const { return ParentTypeB::operator bool(); }
      size_type size() const { return ParentTypeB::size(); }
      reference operator()(size_type i,size_type j) {
        return ParentTypeB::operator()(i,j);
      }
      const_reference operator()(size_type i,size_type j) const {
        return ParentTypeB::operator()(i,j);
      }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(IsSameSize(*this,A));
        typedef typename ParentTypeB::ParentTypeA PType;
        PType::operator=((PType const&)A);
        return *this;
      }
      template <typename E,typename ET>
      Type& operator=(const Array2DExpression<E,ET>& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(IsSameSize(*this,(Type const)EA));
        for(size_type i=0,m;i<size();++i) {
          m=(*this)[i].size();
          for(size_type j=0;j<m;++j)
            (*this)[i][j]=EA(i,j);
        }
        return *this;
      }
      Type& operator=(const monomer_type& D) {
        assert((bool)(*this));
        typedef typename ParentTypeB::ParentTypeA PType;
        PType::operator=(D);
        return *this;
      }

  };

  template <typename T>
  class Array2D<Intrinsic<T>,true>
      : public Array2DExpression<Array2D<Intrinsic<T>,true>,T>,
        public Array2DContainer<Intrinsic<T>> {

    public:

      typedef Array2D<Intrinsic<T>,true>    Type;
      typedef Array2DExpression<Type,T>   ParentTypeA;
      typedef Array2DContainer<Intrinsic<T>>  ParentTypeB;
      typedef unsigned int size_type;
      typedef typename ParentTypeB::ParentTypeB::monomer_type monomer_type;
      typedef T value_type;
      typedef monomer_type& reference;
      typedef const monomer_type& const_reference;

      Array2D() : ParentTypeA(), ParentTypeB() {}
      Array2D(size_type m,size_type n) : ParentTypeA(), ParentTypeB(m,n) {}
      Array2D(const Type& A) : Array2D() { this->imprint(A); operator=(A); }
      Array2D(Type&& A) : ParentTypeA(), ParentTypeB((ParentTypeB&&)A) {}
      ~Array2D() { ParentTypeB::reset(); }

      operator bool() const { return ParentTypeB::operator bool(); }
      size_type size() const { return ParentTypeB::size(); }
      reference operator()(size_type i,size_type j) {
        return ParentTypeB::operator()(i,j);
      }
      const_reference operator()(size_type i,size_type j) const {
        return ParentTypeB::operator()(i,j);
      }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(IsSameSize(*this,A));
        typedef typename ParentTypeB::ParentTypeA  PType;
        PType::operator=((PType const&)A);
        return *this;
      }
      template <typename E,typename ET>
      Type& operator=(const Array2DExpression<E,ET>& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(IsSameSize(*this,(Type const)EA));
        for(size_type i=0,m;i<size();++i) {
          m=(*this)[i].size();
          for(size_type j=0;j<m;++j)
            (*this)[i][j]=EA(i,j);
        }
        return *this;
      }
      Type& operator=(const value_type& D) {
        assert((bool)(*this));
        typedef typename ParentTypeB::ParentTypeA  PType;
        PType::operator=(D);
        return *this;
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((value_type)((T1)D));
      }

  };

}

#endif

