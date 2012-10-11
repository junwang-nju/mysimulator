
#ifndef _Array_Large_Data_H_
#define _Array_Large_Data_H_

#include "array/interface.h"
#include "array/expression.h"
#include "basic/type/same.h"
#include <cstring>

#include "array/expression-sum.h"
#include "array/expression-substract.h"
#include "array/expression-multiple.h"
#include "array/expression-divide.h"

namespace mysimulator {

  template <typename T>
  class Array<Intrinsic<T>,ArrayFormat::LargeData>
      : public ArrayExpression<Array<Intrinsic<T>,ArrayFormat::LargeData>,T>,
        public ArrayContainer<Intrinsic<T>,ArrayFormat::LargeData> {

    public:

      typedef Array<Intrinsic<T>,ArrayFormat::LargeData>           Type;
      typedef ArrayExpression<Type,T>                              ParentTypeA;
      typedef ArrayContainer<Intrinsic<T>,ArrayFormat::LargeData>  ParentTypeB;
      typedef typename ParentTypeB::value_type value_type;
      typedef unsigned int size_type;
      typedef value_type& reference;
      typedef const value_type& const_reference;

      Array() : ParentTypeA(), ParentTypeB() {}
      Array(size_type size) : ParentTypeA(), ParentTypeB(size) {}
      Array(const Type& A) : Array(A.size()) { operator=(A); }
      ~Array() { ParentTypeB::reset(); }

      template <typename E,typename ET>
      Array(const ArrayExpression<E,ET>& EA) : Array(EA.size()) {
        operator=(EA);
      }
      template <typename E,typename ET>
      Array(const ArrayExpression<E,ET>&& EA) : Array(EA.size()) {
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
      Type& operator=(const ArrayExpression<Type,T>& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        memcpy(this->head(),static_cast<const Type&>(EA).head(),
               size()*sizeof(T));
        return *this;
      }

      Type& operator=(const Type& A) {
        return operator=<ParentTypeA const&>(A);
      }
      Type& operator=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i)   (*this)[i]=D;
        return *this;
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((value_type)D);
      }

      template <typename E,typename ET>
      Type& operator+=(const ArrayExpression<E,ET>& EA) {
        static_assert((
          __same_type<T,typename __dual_selector<T,ET,__sum_flag>::Type>::FG),
          "Type T cannot accept sum result!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]+=EA[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator+=(const ArrayExpression<E,ET>&& EA) {
        static_assert((
          __same_type<T,typename __dual_selector<T,ET,__sum_flag>::Type>::FG),
          "Type T cannot accept sum result!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]+=EA[i];
        return *this;
      }
      Type& operator+=(const T& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i)   (*this)[i]+=D;
        return *this;
      }
      template <typename T1>
      Type& operator+=(const Intrinsic<T1>& D) {
        return operator+=((value_type)D);
      }

      template <typename E,typename ET>
      Type& operator-=(const ArrayExpression<E,ET>& EA) {
        static_assert((
          __same_type<T,typename __dual_selector<T,ET,__sum_flag>::Type>::FG),
          "Type T cannot accept sum result!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]-=EA[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator-=(const ArrayExpression<E,ET>&& EA) {
        static_assert((
          __same_type<T,typename __dual_selector<T,ET,__sum_flag>::Type>::FG),
          "Type T cannot accept sum result!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]-=EA[i];
        return *this;
      }

  };

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  typedef Array<Int,ArrayFormat::LargeData>     ItLargeDataArray;
  typedef Array<Float,ArrayFormat::LargeData>   FtLargeDataArray;
  typedef Array<Double,ArrayFormat::LargeData>  DbLargeDataArray;

  template <>
  ItLargeDataArray& ItLargeDataArray::operator=(
      const ArrayExpression<ItLargeDataArray,int>& EA) {
    static_assert(sizeof(int)==sizeof(float),
                  "Sizes of int and float Needs to Be Equal!\n");
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    long n=size(), one=1;
    scopy_(
      &n,
      reinterpret_cast<float*>(static_cast<const ItLargeDataArray&>(EA).head()),
      &one,
      reinterpret_cast<float*>(this->head()),
      &one);
    return *this;
  }

  template <>
  DbLargeDataArray& DbLargeDataArray::operator=(
      const ArrayExpression<DbLargeDataArray,double>& EA) {
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    long n=size(), one=1;
    dcopy_(
     &n,
     reinterpret_cast<double*>(static_cast<const DbLargeDataArray&>(EA).head()),
     &one,
     this->head(),
     &one);
    return *this;
  }

  template <>
  ItLargeDataArray& ItLargeDataArray::operator=(const int& D) {
    static_assert(sizeof(int)==sizeof(float),
                  "Sizes of int and float Needs to Be Equal!\n");
    assert((bool)(*this));
    long n=size(), one=1, zero=0;
    scopy_(&n,reinterpret_cast<float*>(const_cast<int*>(&D)),&zero,
              reinterpret_cast<float*>(this->head()),&one);
    return *this;
  }

  template <>
  DbLargeDataArray& DbLargeDataArray::operator=(const double& D) {
    assert((bool)(*this));
    long n=size(), one=1, zero=0;
    dcopy_(&n,const_cast<double*>(&D),&zero,this->head(),&one);
    return *this;
  }

  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<DbLargeDataArray,double>& EA) {
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    long n=size(), one=1;
    double D=1.;
    daxpy_(
     &n,
     &D,
     reinterpret_cast<double*>(static_cast<const DbLargeDataArray&>(EA).head()),
     &one,
     this->head(),
     &one);
    return *this;
  }

  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(const double& D) {
    assert((bool)(*this));
    long n=size(), one=1, zero=0;
    double E=1.;
    daxpy_(
        &n,
        &E,
        const_cast<double*>(&D),
        &zero,
        this->head(),
        &one);
    return *this;
  }

}

#endif

