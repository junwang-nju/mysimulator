
#ifndef _Array_Large_Data_H_
#define _Array_Large_Data_H_

#include "array/interface.h"
#include "array/expression.h"
#include "basic/type/same.h"
#include "linear-algebra/blas.h"

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
        assert(sizeof(double)==8);
        //memcpy(this->head(),static_cast<const Type&>(EA).head(),
        //       size()*sizeof(T));
        long n=this->size128()+this->size128(),one=1;
        dcopy_(
          &n,
          reinterpret_cast<double*>(((Type const&)EA).head()),
          &one,
          this->head(),
          &one);
        return *this;
      }
      Type& operator=(const ArrayExpression<Type,T>&& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        assert(sizeof(double)==8);
        long n=this->size128()+this->size128(),one=1;
        dcopy_(
          &n,
          reinterpret_cast<double*>(((Type const&)EA).head()),
          &one,
          this->head(),
          &one);
        return *this;
      }
      Type& operator=(const Type& A) {
        return operator=((ParentTypeA const&)A);
      }
      Type& operator=(const Type&& A) {
        return operator=((ParentTypeA const&)A);
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
      template <typename T1>
      Type& operator=(const Intrinsic<T1>&& D) {
        return operator=((value_type)D);
      }

      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>&& A) {
        typedef ArraySum<EA,EB>   SType;
        operator=(static_cast<SType const&>(A).first());
        return operator+=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>& A) {
        typedef ArraySum<EA,EB>   SType;
        operator=(static_cast<SType const&>(A).first());
        return operator+=(static_cast<SType const&>(A).second());
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
      template <typename T1>
      Type& operator+=(const Intrinsic<T1>&& D) {
        return operator+=((value_type)D);
      }

      template <typename E,typename ET>
      Type& operator-=(const ArrayExpression<E,ET>& EA) {
        static_assert((
          __same_type<T,typename __dual_selector<T,ET,__sub_flag>::Type>::FG),
          "Type T cannot accept sum result!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]-=EA[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator-=(const ArrayExpression<E,ET>&& EA) {
        static_assert((
          __same_type<T,typename __dual_selector<T,ET,__sub_flag>::Type>::FG),
          "Type T cannot accept sum result!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]-=EA[i];
        return *this;
      }
      Type& operator-=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i) (*this)[i]-=D;
        return *this;
      }
      template <typename T1>
      Type& operator-=(const Intrinsic<T1>& D) {
        return operator-=((value_type)D);
      }
      template <typename T1>
      Type& operator-=(const Intrinsic<T1>&& D) {
        return operator-=((value_type)D);
      }

      template <typename E,typename ET>
      Type& operator*=(const ArrayExpression<E,ET>& EA) {
        static_assert((
          __same_type<T,typename __dual_selector<T,ET,__mul_flag>::Type>::FG),
          "Type T cannot accept sum result!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]*=EA[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator*=(const ArrayExpression<E,ET>&& EA) {
        static_assert((
          __same_type<T,typename __dual_selector<T,ET,__mul_flag>::Type>::FG),
          "Type T cannot accept sum result!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]*=EA[i];
        return *this;
      }
      Type& operator*=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i)   (*this)[i]*=D;
        return *this;
      }
      template <typename T1>
      Type& operator*=(const Intrinsic<T1>& D) {
        return operator*=((value_type)D);
      }
      template <typename T1>
      Type& operator*=(const Intrinsic<T1>&& D) {
        return operator*=((value_type)D);
      }

      template <typename E,typename ET>
      Type& operator/=(const ArrayExpression<E,ET>& EA) {
        static_assert((
          __same_type<T,typename __dual_selector<T,ET,__div_flag>::Type>::FG),
          "Type T cannot accept sum result!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]/=EA[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator/=(const ArrayExpression<E,ET>&& EA) {
        static_assert((
          __same_type<T,typename __dual_selector<T,ET,__div_flag>::Type>::FG),
          "Type T cannot accept sum result!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]/=EA[i];
        return *this;
      }
      Type& operator/=(const value_type& D) {
        assert((bool)(*this));
        value_type iD=1./D;
        for(size_type i=0;i<size();++i)   (*this)[i]*=iD;
        return *this;
      }
      template <typename T1>
      Type& operator/=(const Intrinsic<T1>& D) {
        return operator/=((value_type)D);
      }
      template <typename T1>
      Type& operator/=(const Intrinsic<T1>&& D) {
        return operator/=((value_type)D);
      }

  };

  template <typename T>
  class LargeArrayTypeWrapper {
    public:
      typedef LargeArrayTypeWrapper<T>  Type;
      LargeArrayTypeWrapper() = delete;
      LargeArrayTypeWrapper(const Type&) = delete;
      Type& operator=(const Type&) = delete;
      ~LargeArrayTypeWrapper() {}
  };

  template <>
  class LargeArrayTypeWrapper<Int> {
  };

  typedef Array<Int,ArrayFormat::LargeData>     ItLargeDataArray;
  typedef Array<Float,ArrayFormat::LargeData>   FtLargeDataArray;
  typedef Array<Double,ArrayFormat::LargeData>  DbLargeDataArray;

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
    static double E=1.;
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

