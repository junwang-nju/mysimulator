
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
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArraySub<EA,EB>,typename ArraySub<EA,EB>::value_type>&& A) {
        typedef ArraySub<EA,EB>   SType;
        operator=(static_cast<SType const&>(A).first());
        return operator-=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArraySub<EA,EB>,typename ArraySub<EA,EB>::value_type>& A) {
        typedef ArraySub<EA,EB>   SType;
        operator=(static_cast<SType const&>(A).first());
        return operator-=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArrayMul<EA,EB>,typename ArrayMul<EA,EB>::value_type>&& A) {
        typedef ArrayMul<EA,EB>   SType;
        operator=(static_cast<SType const&>(A).first());
        return operator*=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArrayMul<EA,EB>,typename ArrayMul<EA,EB>::value_type>& A) {
        typedef ArrayMul<EA,EB>   SType;
        operator=(static_cast<SType const&>(A).first());
        return operator*=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArrayDiv<EA,EB>,typename ArrayDiv<EA,EB>::value_type>&& A) {
        typedef ArrayDiv<EA,EB>   SType;
        operator=(static_cast<SType const&>(A).first());
        return operator/=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArrayDiv<EA,EB>,typename ArrayDiv<EA,EB>::value_type>& A) {
        typedef ArrayDiv<EA,EB>   SType;
        operator=(static_cast<SType const&>(A).first());
        return operator/=(static_cast<SType const&>(A).second());
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
      template <typename EA,typename EB>
      Type& operator+=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>&& A) {
        typedef ArraySum<EA,EB>   SType;
        operator+=(static_cast<SType const&>(A).first());
        return operator+=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator+=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>& A) {
        typedef ArraySum<EA,EB>   SType;
        operator+=(static_cast<SType const&>(A).first());
        return operator+=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator+=(
          const ArrayExpression<
                  ArraySub<EA,EB>,typename ArraySub<EA,EB>::value_type>&& A) {
        typedef ArraySub<EA,EB>   SType;
        operator+=(static_cast<SType const&>(A).first());
        return operator-=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator+=(
          const ArrayExpression<
                  ArraySub<EA,EB>,typename ArraySub<EA,EB>::value_type>& A) {
        typedef ArraySub<EA,EB>   SType;
        operator+=(static_cast<SType const&>(A).first());
        return operator-=(static_cast<SType const&>(A).second());
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
      template <typename EA,typename EB>
      Type& operator-=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>&& A) {
        typedef ArraySum<EA,EB>   SType;
        operator-=(static_cast<SType const&>(A).first());
        return operator-=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator-=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>& A) {
        typedef ArraySum<EA,EB>   SType;
        operator-=(static_cast<SType const&>(A).first());
        return operator-=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator-=(
          const ArrayExpression<
                  ArraySub<EA,EB>,typename ArraySub<EA,EB>::value_type>&& A) {
        typedef ArraySub<EA,EB>   SType;
        operator-=(static_cast<SType const&>(A).first());
        return operator+=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator-=(
          const ArrayExpression<
                  ArraySub<EA,EB>,typename ArraySub<EA,EB>::value_type>& A) {
        typedef ArraySub<EA,EB>   SType;
        operator-=(static_cast<SType const&>(A).first());
        return operator+=(static_cast<SType const&>(A).second());
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
      template <typename EA,typename EB>
      Type& operator*=(
          const ArrayExpression<
                  ArrayMul<EA,EB>,typename ArrayMul<EA,EB>::value_type>&& A) {
        typedef ArrayMul<EA,EB>   SType;
        operator*=(static_cast<SType const&>(A).first());
        return operator*=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator*=(
          const ArrayExpression<
                  ArrayMul<EA,EB>,typename ArrayMul<EA,EB>::value_type>& A) {
        typedef ArrayMul<EA,EB>   SType;
        operator*=(static_cast<SType const&>(A).first());
        return operator*=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator*=(
          const ArrayExpression<
                  ArrayDiv<EA,EB>,typename ArrayDiv<EA,EB>::value_type>&& A) {
        typedef ArrayDiv<EA,EB>   SType;
        operator*=(static_cast<SType const&>(A).first());
        return operator/=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator*=(
          const ArrayExpression<
                  ArrayDiv<EA,EB>,typename ArrayDiv<EA,EB>::value_type>& A) {
        typedef ArrayDiv<EA,EB>   SType;
        operator*=(static_cast<SType const&>(A).first());
        return operator/=(static_cast<SType const&>(A).second());
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
      template <typename EA,typename EB>
      Type& operator/=(
          const ArrayExpression<
                  ArrayMul<EA,EB>,typename ArrayMul<EA,EB>::value_type>&& A) {
        typedef ArrayMul<EA,EB>   SType;
        operator/=(static_cast<SType const&>(A).first());
        return operator/=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator/=(
          const ArrayExpression<
                  ArrayMul<EA,EB>,typename ArrayMul<EA,EB>::value_type>& A) {
        typedef ArrayMul<EA,EB>   SType;
        operator/=(static_cast<SType const&>(A).first());
        return operator/=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator/=(
          const ArrayExpression<
                  ArrayDiv<EA,EB>,typename ArrayDiv<EA,EB>::value_type>&& A) {
        typedef ArrayDiv<EA,EB>   SType;
        operator/=(static_cast<SType const&>(A).first());
        return operator*=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator/=(
          const ArrayExpression<
                  ArrayDiv<EA,EB>,typename ArrayDiv<EA,EB>::value_type>& A) {
        typedef ArrayDiv<EA,EB>   SType;
        operator/=(static_cast<SType const&>(A).first());
        return operator*=(static_cast<SType const&>(A).second());
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
    public:
      typedef Int::value_type   value_type;
      typedef Array<Int,ArrayFormat::LargeData>   array_type;
      static void copy(long n,const value_type* A,long dA,
                              value_type* B,long dB) {
        static_assert(sizeof(int)==sizeof(float),
                      "Sizes of int and float Needs to Be Equal!\n");
        scopy_(&n,reinterpret_cast<float*>(const_cast<value_type*>(A)),&dA,
               reinterpret_cast<float*>(B),&dB);
      }
  };

  template <>
  class LargeArrayTypeWrapper<Float> {
    public:
      typedef Float::value_type   value_type;
      typedef Array<Float,ArrayFormat::LargeData>   array_type;
      static void copy(long n,const value_type* A, long dA,
                              value_type* B, long dB) {
        scopy_(&n,const_cast<value_type*>(A),&dA,B,&dB);
      }
      static void axpy(long n,const value_type& D,const value_type* A,long dA,
                       value_type* B,long dB) {
        saxpy_(&n,const_cast<value_type*>(&D),const_cast<value_type*>(A),&dA,
               B,&dB);
      }
      static void tbmv(char ul,char ts,char dg,
                       long n,long k,const value_type* A,long lda,
                       value_type* B,long dB) {
        stbmv_(&ul,&ts,&dg,&n,&k,const_cast<value_type*>(A),&lda,B,&dB);
      }
      static void scale(long n,const value_type& D,value_type* A,long dA) {
        sscal_(&n,const_cast<value_type*>(&D),A,&dA);
      }
      static void sbmv(char ul,long n,long k,const value_type& AP,
                       const value_type* A,long lda,const value_type* X,long dX,
                       const value_type& BT,value_type* Y,long dY) {
        ssbmv_(&ul,&n,&k,const_cast<value_type*>(&AP),
               const_cast<value_type*>(A),&lda,const_cast<value_type*>(X),&dX,
               const_cast<value_type*>(&BT),Y,&dY);
      }
  };

  template <>
  class LargeArrayTypeWrapper<Double> {
    public:
      typedef Double::value_type    value_type;
      typedef Array<Double,ArrayFormat::LargeData>  array_type;
      static void copy(long n,const value_type* A,long dA,
                              value_type* B,long dB) {
        dcopy_(&n,const_cast<value_type*>(A),&dA,B,&dB);
      }
      static void axpy(long n,const value_type& D,const value_type* A,long dA,
                       value_type* B,long dB) {
        daxpy_(&n,const_cast<value_type*>(&D),const_cast<value_type*>(A),&dA,
               B,&dB);
      }
      static void tbmv(char ul,char ts,char dg,
                       long n,long k,const value_type* A,long lda,
                       value_type* B,long dB) {
        dtbmv_(&ul,&ts,&dg,&n,&k,const_cast<value_type*>(A),&lda,B,&dB);
      }
      static void scale(long n,const value_type& D,value_type* A,long dA) {
        dscal_(&n,const_cast<value_type*>(&D),A,&dA);
      }
      static void sbmv(char ul,long n,long k,const value_type& AP,
                       const value_type* A,long lda,const value_type* X,long dX,
                       const value_type& BT,value_type* Y,long dY) {
        dsbmv_(&ul,&n,&k,const_cast<value_type*>(&AP),
               const_cast<value_type*>(A),&lda,const_cast<value_type*>(X),&dX,
               const_cast<value_type*>(&BT),Y,&dY);
      }
  };

  template <typename T>
  typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type&
  __assign(typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& A,
           const typename LargeArrayTypeWrapper<Intrinsic<T>>::value_type& D) {
    assert((bool)A);
    long n=A.size(),zero=0,one=1;
    LargeArrayTypeWrapper<Intrinsic<T>>::copy(n,&D,zero,A.head(),one);
    return A;
  }

  template <typename T>
  typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type&
  __plus(typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& A,
         const typename LargeArrayTypeWrapper<Intrinsic<T>>::value_type& D) {
    assert((bool)A);
    long n=A.size(),zero=0,one=1;
    typename LargeArrayTypeWrapper<Intrinsic<T>>::value_type dOne=1.;
    LargeArrayTypeWrapper<Intrinsic<T>>::axpy(n,dOne,&D,zero,A.head(),one);
    return A;
  }

  template <typename T>
  typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type&
  __plus(typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& A,
         const typename LargeArrayTypeWrapper<Intrinsic<T>>::value_type& D,
         const typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& B) {
    assert((bool)A);
    assert((bool)B);
    assert(A.size()<=B.size());
    long n=A.size(),one=1;
    LargeArrayTypeWrapper<Intrinsic<T>>::axpy(n,D,B.head(),one,A.head(),one);
    return A;
  }

  template <typename T>
  typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type&
  __plus(typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& A,
         const typename LargeArrayTypeWrapper<Intrinsic<T>>::value_type& D,
         const typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type&& B) {
    assert((bool)A);
    assert((bool)B);
    assert(A.size()<=B.size());
    long n=A.size(),one=1;
    LargeArrayTypeWrapper<Intrinsic<T>>::axpy(n,D,B.head(),one,A.head(),one);
    return A;
  }

  template <typename T>
  typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type&
  __plus(typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& A,
         const typename LargeArrayTypeWrapper<Intrinsic<T>>::value_type& D,
         const typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& F,
         const typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& B) {
    assert((bool)A);
    assert((bool)F);
    assert((bool)B);
    assert(A.size()<=F.size());
    assert(A.size()<=B.size());
    char FG='L';
    long n=A.size(),zero=0,one=1;
    typename LargeArrayTypeWrapper<Intrinsic<T>>::value_type dOne=1.;
    LargeArrayTypeWrapper<Intrinsic<T>>::sbmv(FG,n,zero,D,F.head(),one,B.head(),
                                              one,dOne,A.head(),one);
  }

  template <typename T>
  typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type&
  __scale(typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& A,
          const typename LargeArrayTypeWrapper<Intrinsic<T>>::value_type& D) {
    assert((bool)A);
    long n=A.size(),one=1;
    LargeArrayTypeWrapper<Intrinsic<T>>::scale(n,D,A.head(),one);
    return A;
  }

  template <typename T>
  typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type&
  __scale(typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& A,
          const typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& B) {
    assert((bool)A);
    assert((bool)B);
    assert(A.size()<=B.size());
    char FG[]="LNN";
    long n=A.size(),zero=0,one=1;
    LargeArrayTypeWrapper<Intrinsic<T>>::tbmv(FG[0],FG[1],FG[2],n,zero,
                                              B.head(),one,A.head(),one);
    return A;
  }

  template <typename T>
  typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type&
  __scale(typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type& A,
          const typename LargeArrayTypeWrapper<Intrinsic<T>>::array_type&& B) {
    assert((bool)A);
    assert((bool)B);
    assert(A.size()<=B.size());
    char FG[]="LNN";
    long n=A.size(),zero=0,one=1;
    LargeArrayTypeWrapper<Intrinsic<T>>::tbmv(FG[0],FG[1],FG[2],n,zero,
                                              B.head(),one,A.head(),one);
    return A;
  }

  typedef Array<Int,ArrayFormat::LargeData>     ItLargeDataArray;
  typedef Array<Float,ArrayFormat::LargeData>   FtLargeDataArray;
  typedef Array<Double,ArrayFormat::LargeData>  DbLargeDataArray;

  template <>
  ItLargeDataArray& ItLargeDataArray::operator=(const int& D) {
    return __assign<int>(*this,D);
  }

  template <>
  FtLargeDataArray& FtLargeDataArray::operator=(const float& D) {
    return __assign<float>(*this,D);
  }

  template <>
  DbLargeDataArray& DbLargeDataArray::operator=(const double& D) {
    return __assign<double>(*this,D);
  }

  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(const float& D) {
    return __plus<float>(*this,D);
  }
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(const double& D) {
    return __plus<double>(*this,D);
  }

  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<FtLargeDataArray,float>& EA) {
    float fOne=1.;
    return __plus<float>(*this,fOne,(FtLargeDataArray const&)EA);
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<FtLargeDataArray,float>&& EA) {
    float fOne=1.;
    return __plus<float>(*this,fOne,(FtLargeDataArray const&)EA);
  }

  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<DbLargeDataArray,double>& EA) {
    double dOne=1.;
    return __plus<double>(*this,dOne,(DbLargeDataArray const&)EA);
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<DbLargeDataArray,double>&& EA) {
    double dOne=1.;
    return __plus<double>(*this,dOne,(DbLargeDataArray const&)EA);
  }

  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<Float,FtLargeDataArray>,float>& EA) {
    typedef ArrayMul<Float,FtLargeDataArray>  SType;
    return __plus<float>(*this,((SType const&)EA).first(),
                               ((SType const&)EA).second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<Float,FtLargeDataArray>,float>&& EA) {
    typedef ArrayMul<Float,FtLargeDataArray>  SType;
    return __plus<float>(*this,((SType const&)EA).first(),
                               ((SType const&)EA).second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<FtLargeDataArray,Float>,float>& EA) {
    typedef ArrayMul<FtLargeDataArray,Float>  SType;
    return __plus<float>(*this,((SType const&)EA).second(),
                               ((SType const&)EA).first());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<FtLargeDataArray,Float>,float>&& EA) {
    typedef ArrayMul<FtLargeDataArray,Float>  SType;
    return __plus<float>(*this,((SType const&)EA).second(),
                               ((SType const&)EA).first());
  }

  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<ArrayDiv<FtLargeDataArray,Float>,float>& EA) {
    typedef ArrayDiv<FtLargeDataArray,Float>  SType;
    return __plus<float>(*this,1./((SType const&)EA).second(),
                               ((SType const&)EA).first());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<ArrayDiv<FtLargeDataArray,Float>,float>&& EA) {
    typedef ArrayDiv<FtLargeDataArray,Float>  SType;
    return __plus<float>(*this,1./((SType const&)EA).second(),
                               ((SType const&)EA).first());
  }

  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<Double,DbLargeDataArray>,double>& EA) {
    typedef ArrayMul<Double,DbLargeDataArray>   SType;
    return __plus<double>(*this,((SType const&)EA).first(),
                                ((SType const&)EA).second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<Double,DbLargeDataArray>,double>&& EA) {
    typedef ArrayMul<Double,DbLargeDataArray>   SType;
    return __plus<double>(*this,((SType const&)EA).first(),
                                ((SType const&)EA).second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<DbLargeDataArray,Double>,double>& EA) {
    typedef ArrayMul<DbLargeDataArray,Double>   SType;
    return __plus<double>(*this,((SType const&)EA).second(),
                                ((SType const&)EA).first());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<DbLargeDataArray,Double>,double>&& EA) {
    typedef ArrayMul<DbLargeDataArray,Double>   SType;
    return __plus<double>(*this,((SType const&)EA).second(),
                                ((SType const&)EA).first());
  }

  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<ArrayDiv<DbLargeDataArray,Double>,double>& EA) {
    typedef ArrayDiv<DbLargeDataArray,Double>   SType;
    return __plus<double>(*this,1./((SType const&)EA).second(),
                                ((SType const&)EA).first());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<ArrayDiv<DbLargeDataArray,Double>,double>&& EA) {
    typedef ArrayDiv<DbLargeDataArray,Double>   SType;
    return __plus<double>(*this,1./((SType const&)EA).second(),
                                ((SType const&)EA).first());
  }

  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<FtLargeDataArray,FtLargeDataArray>,
                            float>& EA) {
    typedef ArrayMul<FtLargeDataArray,FtLargeDataArray>   SType;
    float fOne=1.;
    return __plus<float>(*this,fOne,((SType const&)EA).first(),
                                    ((SType const&)EA).second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<FtLargeDataArray,FtLargeDataArray>,
                            float>&& EA) {
    typedef ArrayMul<FtLargeDataArray,FtLargeDataArray>   SType;
    float fOne=1.;
    return __plus<float>(*this,fOne,((SType const&)EA).first(),
                                    ((SType const&)EA).second());
  }

  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<Float,
                       ArrayMul<FtLargeDataArray,FtLargeDataArray>>,
              float>& EA) {
    typedef ArrayMul<FtLargeDataArray,FtLargeDataArray> MType;
    typedef ArrayMul<Float,MType> SType;
    return __plus<float>(*this,((SType const&)EA).first(),
                               ((SType const&)EA).second().first(),
                               ((SType const&)EA).second().second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<Float,
                       ArrayMul<FtLargeDataArray,FtLargeDataArray>>,
              float>&& EA) {
    printf("========ZZZZ=============\n");
    typedef ArrayMul<FtLargeDataArray,FtLargeDataArray> MType;
    typedef ArrayMul<Float,MType> SType;
    return __plus<float>(*this,((SType const&)EA).first(),
                               ((SType const&)EA).second().first(),
                               ((SType const&)EA).second().second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayMul<Float,FtLargeDataArray>,
                       FtLargeDataArray>,float>& EA) {
    typedef ArrayMul<Float,FtLargeDataArray> MType;
    typedef ArrayMul<MType,FtLargeDataArray>   SType;
    return __plus<float>(*this,((SType const&)EA).first().first(),
                               ((SType const&)EA).first().second(),
                               ((SType const&)EA).second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayMul<Float,FtLargeDataArray>,
                       FtLargeDataArray>,float>&& EA) {
    typedef ArrayMul<Float,FtLargeDataArray> MType;
    typedef ArrayMul<MType,FtLargeDataArray>   SType;
    return __plus<float>(*this,((SType const&)EA).first().first(),
                               ((SType const&)EA).first().second(),
                               ((SType const&)EA).second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<FtLargeDataArray,
                       ArrayMul<Float,FtLargeDataArray>>,float>& EA) {
    typedef ArrayMul<Float,FtLargeDataArray>  MType;
    typedef ArrayMul<FtLargeDataArray,MType>  SType;
    return __plus<float>(*this,((SType const&)EA).second().first(),
                               ((SType const&)EA).first(),
                               ((SType const&)EA).second().second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<FtLargeDataArray,
                       ArrayMul<Float,FtLargeDataArray>>,float>&& EA) {
    typedef ArrayMul<Float,FtLargeDataArray>  MType;
    typedef ArrayMul<FtLargeDataArray,MType>  SType;
    return __plus<float>(*this,((SType const&)EA).second().first(),
                               ((SType const&)EA).first(),
                               ((SType const&)EA).second().second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayMul<FtLargeDataArray,Float>,
                       FtLargeDataArray>,float>& EA) {
    typedef ArrayMul<FtLargeDataArray,Float>  MType;
    typedef ArrayMul<MType,FtLargeDataArray>  SType;
    return __plus<float>(*this,((SType const&)EA).first().second(),
                               ((SType const&)EA).first().first(),
                               ((SType const&)EA).second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayMul<FtLargeDataArray,Float>,
                       FtLargeDataArray>,float>&& EA) {
    typedef ArrayMul<FtLargeDataArray,Float>  MType;
    typedef ArrayMul<MType,FtLargeDataArray>  SType;
    return __plus<float>(*this,((SType const&)EA).first().second(),
                               ((SType const&)EA).first().first(),
                               ((SType const&)EA).second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<FtLargeDataArray,
                       ArrayMul<FtLargeDataArray,Float>>,float>& EA) {
    typedef ArrayMul<FtLargeDataArray,Float>  MType;
    typedef ArrayMul<FtLargeDataArray,MType>  SType;
    return __plus<float>(*this,((SType const&)EA).second().second(),
                               ((SType const&)EA).first(),
                               ((SType const&)EA).second().first());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<FtLargeDataArray,
                       ArrayMul<FtLargeDataArray,Float>>,float>&& EA) {
    typedef ArrayMul<FtLargeDataArray,Float>  MType;
    typedef ArrayMul<FtLargeDataArray,MType>  SType;
    return __plus<float>(*this,((SType const&)EA).second().second(),
                               ((SType const&)EA).first(),
                               ((SType const&)EA).second().first());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayMul<FtLargeDataArray,FtLargeDataArray>,
                       Float>,float>& EA) {
    typedef ArrayMul<FtLargeDataArray,FtLargeDataArray> MType;
    typedef ArrayMul<MType,Float>   SType;
    return __plus<float>(*this,((SType const&)EA).second(),
                               ((SType const&)EA).first().first(),
                               ((SType const&)EA).first().second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayMul<FtLargeDataArray,FtLargeDataArray>,
                       Float>,float>&& EA) {
    typedef ArrayMul<FtLargeDataArray,FtLargeDataArray> MType;
    typedef ArrayMul<MType,Float>   SType;
    return __plus<float>(*this,((SType const&)EA).second(),
                               ((SType const&)EA).first().first(),
                               ((SType const&)EA).first().second());
  }

  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<FtLargeDataArray,
                       ArrayDiv<FtLargeDataArray,Float>>,float>& EA) {
    typedef ArrayDiv<FtLargeDataArray,Float>  MType;
    typedef ArrayMul<FtLargeDataArray,MType>  SType;
    return __plus<float>(*this,1./((SType const&)EA).second().second(),
                               ((SType const&)EA).first(),
                               ((SType const&)EA).second().first());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<FtLargeDataArray,
                       ArrayDiv<FtLargeDataArray,Float>>,float>&& EA) {
    typedef ArrayDiv<FtLargeDataArray,Float>  MType;
    typedef ArrayMul<FtLargeDataArray,MType>  SType;
    return __plus<float>(*this,1./((SType const&)EA).second().second(),
                               ((SType const&)EA).first(),
                               ((SType const&)EA).second().first());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayDiv<FtLargeDataArray,Float>,
                       FtLargeDataArray>,float>& EA) {
    typedef ArrayDiv<FtLargeDataArray,Float>  MType;
    typedef ArrayMul<MType,FtLargeDataArray>  SType;
    return __plus<float>(*this,1./((SType const&)EA).first().second(),
                               ((SType const&)EA).second(),
                               ((SType const&)EA).first().first());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayDiv<FtLargeDataArray,Float>,
                       FtLargeDataArray>,float>&& EA) {
    typedef ArrayDiv<FtLargeDataArray,Float>  MType;
    typedef ArrayMul<MType,FtLargeDataArray>  SType;
    return __plus<float>(*this,1./((SType const&)EA).first().second(),
                               ((SType const&)EA).second(),
                               ((SType const&)EA).first().first());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayDiv<ArrayMul<FtLargeDataArray,FtLargeDataArray>,
                       Float>,float>& EA) {
    typedef ArrayMul<FtLargeDataArray,FtLargeDataArray> MType;
    typedef ArrayDiv<MType,Float>   SType;
    return __plus<float>(*this,1./((SType const&)EA).second(),
                               ((SType const&)EA).first().first(),
                               ((SType const&)EA).first().second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayDiv<ArrayMul<FtLargeDataArray,FtLargeDataArray>,
                       Float>,float>&& EA) {
    typedef ArrayMul<FtLargeDataArray,FtLargeDataArray> MType;
    typedef ArrayDiv<MType,Float>   SType;
    return __plus<float>(*this,1./((SType const&)EA).second(),
                               ((SType const&)EA).first().first(),
                               ((SType const&)EA).first().second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayDiv<FtLargeDataArray,
                       ArrayDiv<Double,FtLargeDataArray>>,float>& EA) {
    typedef ArrayDiv<Double,FtLargeDataArray> MType;
    typedef ArrayDiv<FtLargeDataArray,MType>  SType;
    return __plus<float>(*this,((SType const&)EA).second().first(),
                               ((SType const&)EA).first(),
                               ((SType const&)EA).second().second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayDiv<FtLargeDataArray,
                       ArrayDiv<Double,FtLargeDataArray>>,float>&& EA) {
    typedef ArrayDiv<Double,FtLargeDataArray> MType;
    typedef ArrayDiv<FtLargeDataArray,MType>  SType;
    return __plus<float>(*this,((SType const&)EA).second().first(),
                               ((SType const&)EA).first(),
                               ((SType const&)EA).second().second());
  }

  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<DbLargeDataArray,DbLargeDataArray>,
                            double>& EA) {
    typedef ArrayMul<DbLargeDataArray,DbLargeDataArray> SType;
    double dOne=1.;
    return __plus<double>(*this,dOne,((SType const&)EA).first(),
                                     ((SType const&)EA).second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<ArrayMul<DbLargeDataArray,DbLargeDataArray>,
                            double>&& EA) {
    typedef ArrayMul<DbLargeDataArray,DbLargeDataArray> SType;
    double dOne=1.;
    return __plus<double>(*this,dOne,((SType const&)EA).first(),
                                     ((SType const&)EA).second());
  }

  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<Double,
                       ArrayMul<DbLargeDataArray,DbLargeDataArray>>,
              double>& EA) {
    typedef ArrayMul<DbLargeDataArray,DbLargeDataArray> MType;
    typedef ArrayMul<Double,MType>    SType;
    return __plus<double>(*this,((SType const&)EA).first(),
                                ((SType const&)EA).second().first(),
                                ((SType const&)EA).second().second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<Double,
                       ArrayMul<DbLargeDataArray,DbLargeDataArray>>,
              double>&& EA) {
    typedef ArrayMul<DbLargeDataArray,DbLargeDataArray> MType;
    typedef ArrayMul<Double,MType>    SType;
    return __plus<double>(*this,((SType const&)EA).first(),
                                ((SType const&)EA).second().first(),
                                ((SType const&)EA).second().second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayMul<Double,DbLargeDataArray>,
                       DbLargeDataArray>,double>& EA) {
    typedef ArrayMul<Double,DbLargeDataArray> MType;
    typedef ArrayMul<MType,DbLargeDataArray>  SType;
    return __plus<double>(*this,((SType const&)EA).first().first(),
                                ((SType const&)EA).first().second(),
                                ((SType const&)EA).second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayMul<Double,DbLargeDataArray>,
                       DbLargeDataArray>,double>&& EA) {
    typedef ArrayMul<Double,DbLargeDataArray> MType;
    typedef ArrayMul<MType,DbLargeDataArray>  SType;
    return __plus<double>(*this,((SType const&)EA).first().first(),
                                ((SType const&)EA).first().second(),
                                ((SType const&)EA).second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<DbLargeDataArray,
                       ArrayMul<Double,DbLargeDataArray>>,double>& EA) {
    typedef ArrayMul<Double,DbLargeDataArray> MType;
    typedef ArrayMul<DbLargeDataArray,MType>  SType;
    return __plus<double>(*this,((SType const&)EA).second().first(),
                                ((SType const&)EA).first(),
                                ((SType const&)EA).second().second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<DbLargeDataArray,
                       ArrayMul<Double,DbLargeDataArray>>,double>&& EA) {
    typedef ArrayMul<Double,DbLargeDataArray> MType;
    typedef ArrayMul<DbLargeDataArray,MType>  SType;
    return __plus<double>(*this,((SType const&)EA).second().first(),
                                ((SType const&)EA).first(),
                                ((SType const&)EA).second().second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<DbLargeDataArray,
                       ArrayMul<DbLargeDataArray,Double>>,double>& EA) {
    typedef ArrayMul<DbLargeDataArray,Double>   MType;
    typedef ArrayMul<DbLargeDataArray,MType>    SType;
    return __plus<double>(*this,((SType const&)EA).second().second(),
                                ((SType const&)EA).first(),
                                ((SType const&)EA).second().first());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<DbLargeDataArray,
                       ArrayMul<DbLargeDataArray,Double>>,double>&& EA) {
    typedef ArrayMul<DbLargeDataArray,Double>   MType;
    typedef ArrayMul<DbLargeDataArray,MType>    SType;
    return __plus<double>(*this,((SType const&)EA).second().second(),
                                ((SType const&)EA).first(),
                                ((SType const&)EA).second().first());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayMul<DbLargeDataArray,DbLargeDataArray>,
                       Double>,double>& EA) {
    typedef ArrayMul<DbLargeDataArray,DbLargeDataArray> MType;
    typedef ArrayMul<MType,Double>  SType;
    return __plus<double>(*this,((SType const&)EA).second(),
                                ((SType const&)EA).first().first(),
                                ((SType const&)EA).first().second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayMul<DbLargeDataArray,DbLargeDataArray>,
                       Double>,double>&& EA) {
    typedef ArrayMul<DbLargeDataArray,DbLargeDataArray> MType;
    typedef ArrayMul<MType,Double>  SType;
    return __plus<double>(*this,((SType const&)EA).second(),
                                ((SType const&)EA).first().first(),
                                ((SType const&)EA).first().second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<DbLargeDataArray,
                       ArrayDiv<DbLargeDataArray,Double>>,double>& EA) {
    typedef ArrayDiv<DbLargeDataArray,Double>   MType;
    typedef ArrayMul<DbLargeDataArray,MType>    SType;
    return __plus<double>(*this,1./((SType const&)EA).second().second(),
                                ((SType const&)EA).first(),
                                ((SType const&)EA).second().first());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<DbLargeDataArray,
                       ArrayDiv<DbLargeDataArray,Double>>,double>&& EA) {
    typedef ArrayDiv<DbLargeDataArray,Double>   MType;
    typedef ArrayMul<DbLargeDataArray,MType>    SType;
    return __plus<double>(*this,1./((SType const&)EA).second().second(),
                                ((SType const&)EA).first(),
                                ((SType const&)EA).second().first());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayDiv<DbLargeDataArray,Double>,
                       DbLargeDataArray>,double>& EA) {
    typedef ArrayDiv<DbLargeDataArray,Double> MType;
    typedef ArrayMul<MType,DbLargeDataArray>  SType;
    return __plus<double>(*this,1./((SType const&)EA).first().second(),
                                ((SType const&)EA).second(),
                                ((SType const&)EA).first().first());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayMul<ArrayDiv<DbLargeDataArray,Double>,
                       DbLargeDataArray>,double>&& EA) {
    typedef ArrayDiv<DbLargeDataArray,Double> MType;
    typedef ArrayMul<MType,DbLargeDataArray>  SType;
    return __plus<double>(*this,1./((SType const&)EA).first().second(),
                                ((SType const&)EA).second(),
                                ((SType const&)EA).first().first());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayDiv<ArrayMul<DbLargeDataArray,DbLargeDataArray>,
                       Double>,double>& EA) {
    typedef ArrayMul<DbLargeDataArray,DbLargeDataArray> MType;
    typedef ArrayDiv<MType,Double>  SType;
    return __plus<double>(*this,1./((SType const&)EA).second(),
                                ((SType const&)EA).first().first(),
                                ((SType const&)EA).first().second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayDiv<ArrayMul<DbLargeDataArray,DbLargeDataArray>,
                       Double>,double>&& EA) {
    typedef ArrayMul<DbLargeDataArray,DbLargeDataArray> MType;
    typedef ArrayDiv<MType,Double>  SType;
    return __plus<double>(*this,1./((SType const&)EA).second(),
                                ((SType const&)EA).first().first(),
                                ((SType const&)EA).first().second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayDiv<DbLargeDataArray,
                       ArrayDiv<Double,DbLargeDataArray>>,double>& EA) {
    typedef ArrayDiv<Double,DbLargeDataArray>   MType;
    typedef ArrayDiv<DbLargeDataArray,MType>    SType;
    return __plus<double>(*this,((SType const&)EA).second().first(),
                                ((SType const&)EA).first(),
                                ((SType const&)EA).second().second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator+=(
      const ArrayExpression<
              ArrayDiv<DbLargeDataArray,
                       ArrayDiv<Double,DbLargeDataArray>>,double>&& EA) {
    typedef ArrayDiv<Double,DbLargeDataArray>   MType;
    typedef ArrayDiv<DbLargeDataArray,MType>    SType;
    return __plus<double>(*this,((SType const&)EA).second().first(),
                                ((SType const&)EA).first(),
                                ((SType const&)EA).second().second());
  }

  template <>
  FtLargeDataArray& FtLargeDataArray::operator-=(const float& D) {
    return __plus<float>(*this,-D);
  }

  template <>
  DbLargeDataArray& DbLargeDataArray::operator-=(const double& D) {
    return __plus<double>(*this,-D);
  }

  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator-=(
      const ArrayExpression<FtLargeDataArray,float>& EA) {
    float fNOne=-1.;
    return __plus<float>(*this,fNOne,(FtLargeDataArray const&)EA);
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator-=(
      const ArrayExpression<FtLargeDataArray,float>&& EA) {
    float fNOne=-1.;
    return __plus<float>(*this,fNOne,(FtLargeDataArray const&)EA);
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator-=(
      const ArrayExpression<ArrayMul<Float,FtLargeDataArray>,float>& EA) {
    typedef ArrayMul<Float,FtLargeDataArray>  SType;
    return __plus<float>(*this,-((SType const&)EA).first(),
                               ((SType const&)EA).second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator-=(
      const ArrayExpression<ArrayMul<Float,FtLargeDataArray>,float>&& EA) {
    typedef ArrayMul<Float,FtLargeDataArray>  SType;
    return __plus<float>(*this,-((SType const&)EA).first(),
                               ((SType const&)EA).second());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator-=(
      const ArrayExpression<ArrayMul<FtLargeDataArray,Float>,float>& EA) {
    typedef ArrayMul<FtLargeDataArray,Float>    SType;
    return __plus<float>(*this,-((SType const&)EA).second(),
                               ((SType const&)EA).first());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator-=(
      const ArrayExpression<ArrayMul<FtLargeDataArray,Float>,float>&& EA) {
    typedef ArrayMul<FtLargeDataArray,Float>    SType;
    return __plus<float>(*this,-((SType const&)EA).second(),
                               ((SType const&)EA).first());
  }

  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator-=(
      const ArrayExpression<ArrayDiv<FtLargeDataArray,Float>,float>& EA) {
    typedef ArrayDiv<FtLargeDataArray,Float>  SType;
    return __plus<float>(*this,-1./((SType const&)EA).second(),
                               ((SType const&)EA).first());
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator-=(
      const ArrayExpression<ArrayDiv<FtLargeDataArray,Float>,float>&& EA) {
    typedef ArrayDiv<FtLargeDataArray,Float>  SType;
    return __plus<float>(*this,-1./((SType const&)EA).second(),
                               ((SType const&)EA).first());
  }

  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator-=(
      const ArrayExpression<DbLargeDataArray,double>& EA) {
    double dNOne=-1.;
    return __plus<double>(*this,dNOne,(DbLargeDataArray const&)EA);
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator-=(
      const ArrayExpression<DbLargeDataArray,double>&& EA) {
    double dNOne=-1.;
    return __plus<double>(*this,dNOne,(DbLargeDataArray const&)EA);
  }

  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator-=(
      const ArrayExpression<ArrayMul<Double,DbLargeDataArray>,double>& EA) {
    typedef ArrayMul<Double,DbLargeDataArray>   SType;
    return __plus<double>(*this,-((SType const&)EA).first(),
                                ((SType const&)EA).second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator-=(
      const ArrayExpression<ArrayMul<Double,DbLargeDataArray>,double>&& EA) {
    typedef ArrayMul<Double,DbLargeDataArray>   SType;
    return __plus<double>(*this,-((SType const&)EA).first(),
                                ((SType const&)EA).second());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator-=(
      const ArrayExpression<ArrayMul<DbLargeDataArray,Double>,double>& EA) {
    typedef ArrayMul<DbLargeDataArray,Double>   SType;
    return __plus<double>(*this,-((SType const&)EA).second(),
                                ((SType const&)EA).first());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator-=(
      const ArrayExpression<ArrayMul<DbLargeDataArray,Double>,double>&& EA) {
    typedef ArrayMul<DbLargeDataArray,Double>   SType;
    return __plus<double>(*this,-((SType const&)EA).second(),
                                ((SType const&)EA).first());
  }

  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator-=(
      const ArrayExpression<ArrayDiv<DbLargeDataArray,Double>,double>& EA) {
    typedef ArrayDiv<DbLargeDataArray,Double>   SType;
    return __plus<double>(*this,-1./((SType const&)EA).second(),
                                ((SType const&)EA).first());
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator-=(
      const ArrayExpression<ArrayDiv<DbLargeDataArray,Double>,double>&& EA) {
    typedef ArrayDiv<DbLargeDataArray,Double>   SType;
    return __plus<double>(*this,-1./((SType const&)EA).second(),
                                ((SType const&)EA).first());
  }

  template <>
  FtLargeDataArray& FtLargeDataArray::operator*=(const float& D) {
    return __scale<float>(*this,D);
  }

  template <>
  DbLargeDataArray& DbLargeDataArray::operator*=(const double& D) {
    return __scale<double>(*this,D);
  }

  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator*=(
      const ArrayExpression<FtLargeDataArray,float>& A) {
    return __scale<float>(*this,(FtLargeDataArray const&)A);
  }
  template <>
  template <>
  FtLargeDataArray& FtLargeDataArray::operator*=(
      const ArrayExpression<FtLargeDataArray,float>&& A) {
    return __scale<float>(*this,(FtLargeDataArray const&)A);
  }

  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator*=(
      const ArrayExpression<DbLargeDataArray,double>& A) {
    return __scale<double>(*this,(DbLargeDataArray const&)A);
  }
  template <>
  template <>
  DbLargeDataArray& DbLargeDataArray::operator*=(
      const ArrayExpression<DbLargeDataArray,double>&& A) {
    return __scale<double>(*this,(DbLargeDataArray const&)A);
  }

  template <>
  FtLargeDataArray& FtLargeDataArray::operator/=(const float& D) {
    return operator*=(1./D);
  }

  template <>
  DbLargeDataArray& DbLargeDataArray::operator/=(const double& D) {
    return operator*=(1./D);
  }

}

#endif

