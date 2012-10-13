
#ifndef _Array_ShortData_H_
#define _Array_ShortData_H_

#include "array/interface.h"
#include "array/expression.h"
#include "basic/type/same.h"

#ifndef __SSE4_1__
#error "\nSSE4.1 is required for ShortData Array! Try -msse4.1 !\n"
#endif

#include <emmintrin.h>
#include <smmintrin.h>

#include "array/expression-sum.h"
#include "array/expression-substract.h"
#include "array/expression-multiple.h"
#include "array/expression-divide.h"

namespace mysimulator {

  template <typename T>
  class Array<Intrinsic<T>,ArrayFormat::ShortData>
      : public ArrayExpression<Array<Intrinsic<T>,ArrayFormat::ShortData>,T>,
        public ArrayContainer<Intrinsic<T>,ArrayFormat::ShortData> {

    public:

      typedef Array<Intrinsic<T>,ArrayFormat::ShortData>           Type;
      typedef ArrayExpression<Type,T>                              ParentTypeA;
      typedef ArrayContainer<Intrinsic<T>,ArrayFormat::ShortData>  ParentTypeB;
      typedef typename ParentTypeB::value_type  value_type;
      typedef unsigned int size_type;
      typedef value_type& reference;
      typedef const value_type& const_reference;

    public:

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
        for(size_type i=0;i<size();++i)   (*this)[i]=EA[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator=(const ArrayExpression<E,ET>&& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]=EA[i];
        return *this;
      }
      Type& operator=(const ArrayExpression<Type,T>& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        __m128i* p=reinterpret_cast<__m128i*>(this->head());
        __m128i* q=reinterpret_cast<__m128i*>(
                                    static_cast<const Type&>(EA).head());
        const __m128i* e=p+this->size128();
        for(;p!=e;) _mm_store_si128(p++,*(q++));
        return *this;
      }

      Type& operator=(const Type& A) {
        return operator=(static_cast<const ParentTypeA&>(A));
      }
      Type& operator=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i) (*this)[i]=D;
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
        typedef ArraySum<EA,EB> SType;
        operator=(static_cast<SType const&>(A).first());
        return operator+=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>& A) {
        typedef ArraySum<EA,EB> SType;
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
                  ArrayMul<EA,EB>,typename ArrayMul<EA,EB>::value_type>& A) {
        typedef ArrayMul<EA,EB> SType;
        operator=(static_cast<SType const&>(A).first());
        return operator*=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArrayMul<EA,EB>,typename ArrayMul<EA,EB>::value_type>&& A) {
        typedef ArrayMul<EA,EB> SType;
        operator=(static_cast<SType const&>(A).first());
        return operator*=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArrayDiv<EA,EB>,typename ArrayDiv<EA,EB>::value_type>& A) {
        typedef ArrayDiv<EA,EB> SType;
        operator=(static_cast<SType const&>(A).first());
        return operator/=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArrayDiv<EA,EB>,typename ArrayDiv<EA,EB>::value_type>&& A) {
        typedef ArrayDiv<EA,EB> SType;
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
      Type& operator+=(const value_type& D) {
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
      Type& operator-=(const ArrayExpression<E,ET> & EA) {
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
      Type& operator-=(const ArrayExpression<E,ET> && EA) {
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
        for(size_type i=0;i<size();++i)   (*this)[i]-=D;
        return *this;
      }
      template <typename T1>
      Type& operator-=(const Intrinsic<T1>&& D) {
        return operator-=((value_type)D);
      }
      template <typename T1>
      Type& operator-=(const Intrinsic<T1>& D) {
        return operator-=((value_type)D);
      }
      template <typename EA,typename EB>
      Type& operator-=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>&& A) {
        typedef ArraySum<EA,EB> SType;
        operator-=(static_cast<SType const&>(A).first());
        return operator-=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator-=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>& A) {
        typedef ArraySum<EA,EB> SType;
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
      Type& operator*=(const Intrinsic<T1>&& D) {
        return operator*=((value_type)D);
      }
      template <typename T1>
      Type& operator*=(const Intrinsic<T1>& D) {
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
            "Type T cannot accept this divide result!\n");
        assert(Intrinsic<T>::IsFloatPoint);
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
            "Type T cannot accept this divide result!\n");
        assert(Intrinsic<T>::IsFloatPoint);
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]/=EA[i];
        return *this;
      }
      Type& operator/=(const value_type& D) {
        assert(Intrinsic<T>::IsFloatPoint);
        assert((bool)(*this));
        value_type iD=((value_type)1.)/D;
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
  class ShortArrayTypeWrapper {
    public:
      typedef ShortArrayTypeWrapper<T>  Type;
      ShortArrayTypeWrapper() = delete;
      ShortArrayTypeWrapper(const Type&) = delete;
      Type& operator=(const Type&) = delete;
      ~ShortArrayTypeWrapper() {}
  };

  template <>
  class ShortArrayTypeWrapper<Int> {
    public:
      typedef Int::value_type value_type;
      typedef Array<Int,ArrayFormat::ShortData>   array_type;
      typedef __m128i value128_type;
      static
      inline value128_type set_from_unit(int D) { return _mm_set1_epi32(D); }
      static
      inline value128_type add128(value128_type const& a,
                                  value128_type const& b) {
        return _mm_add_epi32(a,b);
      }
      static
      inline value128_type substract128(value128_type const& a,
                                        value128_type const& b) {
        return _mm_sub_epi32(a,b);
      }
      static
      inline value128_type mul128(value128_type const& a,
                                  value128_type const& b) {
        return _mm_mullo_epi32(a,b);
      }
  };

  template <>
  class ShortArrayTypeWrapper<Float> {
    public:
      typedef Float::value_type   value_type;
      typedef Array<Float,ArrayFormat::ShortData> array_type;
      typedef __m128 value128_type;
      static
      inline value128_type set_from_unit(float D) { return _mm_set1_ps(D); }
      static
      inline value128_type add128(value128_type const& a,
                                  value128_type const& b) {
        return _mm_add_ps(a,b);
      }
      static
      inline value128_type substract128(value128_type const& a,
                                        value128_type const& b) {
        return _mm_sub_ps(a,b);
      }
      static
      inline value128_type mul128(value128_type const& a,
                                  value128_type const& b) {
        return _mm_mul_ps(a,b);
      }
      static
      inline value128_type div128(value128_type const& a,
                                  value128_type const& b) {
        return _mm_div_ps(a,b);
      }
  };

  template <>
  class ShortArrayTypeWrapper<Double> {
    public:
      typedef Double::value_type    value_type;
      typedef Array<Double,ArrayFormat::ShortData>  array_type;
      typedef __m128d value128_type;
      static
      inline value128_type set_from_unit(double D) { return _mm_set1_pd(D); }
      static
      inline value128_type add128(value128_type const& a,
                                  value128_type const& b) {
        return _mm_add_pd(a,b);
      }
      static
      inline value128_type substract128(value128_type const& a,
                                        value128_type const& b) {
        return _mm_sub_pd(a,b);
      }
      static
      inline value128_type mul128(value128_type const& a,
                                  value128_type const& b) {
        return _mm_mul_pd(a,b);
      }
      static
      inline value128_type div128(value128_type const& a,
                                  value128_type const& b) {
        return _mm_div_pd(a,b);
      }
  };

  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __assign(typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
           const typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type& D) {
    assert((bool)A);
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=ShortArrayTypeWrapper<Intrinsic<T>>::set_from_unit(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;) *(p++)=u;
    return A;
  }

  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __add_to(typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
           const typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type& D) {
    assert((bool)A);
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=ShortArrayTypeWrapper<Intrinsic<T>>::set_from_unit(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;) { *p=ShortArrayTypeWrapper<Intrinsic<T>>::add128(*p,u); ++p; }
    return A;
  }

  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __add_to(typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
           const ArrayExpression<
              typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
              typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).head());
    const T128 *e=p+A.size128();
    for(;p!=e;) { *p=ShortArrayTypeWrapper<Intrinsic<T>>::add128(*p,*(q++)); ++p; }
    return A;
  }
  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __add_to(typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
           const ArrayExpression<
              typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
              typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>&& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).head());
    const T128 *e=p+A.size128();
    for(;p!=e;) { *p=ShortArrayTypeWrapper<Intrinsic<T>>::add128(*p,*(q++)); ++p; }
    return A;
  }

  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __substract_to(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type& D) {
    assert((bool)A);
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=ShortArrayTypeWrapper<Intrinsic<T>>::set_from_unit(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;) {
      *p=ShortArrayTypeWrapper<Intrinsic<T>>::substract128(*p,u);
      ++p;
    }
  }

  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __substract_to(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).head());
    const T128 *e=p+A.size128();
    for(;p!=e;) {
      *p=ShortArrayTypeWrapper<Intrinsic<T>>::substract128(*p,*(q++));
      ++p;
    }
    return A;
  }
  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __substract_to(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>&& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).head());
    const T128 *e=p+A.size128();
    for(;p!=e;) {
      *p=ShortArrayTypeWrapper<Intrinsic<T>>::substract128(*p,*(q++));
      ++p;
    }
    return A;
  }

  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __multiple_to(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type& D) {
    assert((bool)A);
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=ShortArrayTypeWrapper<Intrinsic<T>>::set_from_unit(D);
    for(;p!=e;) {
      *p=ShortArrayTypeWrapper<Intrinsic<T>>::mul128(*p,u);
      ++p;
    }
    return A;
  }

  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __multiple_to(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).head());
    const T128 *e=p+A.size128();
    for(;p!=e;) {
      *p=ShortArrayTypeWrapper<Intrinsic<T>>::mul128(*p,*(q++));
      ++p;
    }
    return A;
  }
  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __multiple_to(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>&& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).head());
    const T128 *e=p+A.size128();
    for(;p!=e;) {
      *p=ShortArrayTypeWrapper<Intrinsic<T>>::mul128(*p,*(q++));
      ++p;
    }
    return A;
  }

  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __divide_to(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type& D) {
    assert((bool)A);
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=ShortArrayTypeWrapper<Intrinsic<T>>::set_from_unit(D);
    for(;p!=e;) {
      *p=ShortArrayTypeWrapper<Intrinsic<T>>::div128(*p,u);
      ++p;
    }
    return A;
  }
  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __divide_to(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).head());
    for(;p!=e;) {
      *p=ShortArrayTypeWrapper<Intrinsic<T>>::div128(*p,*(q++));
      ++p;
    }
    return A;
  }
  template <typename T>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __divide_to(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>&& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).head());
    for(;p!=e;) {
      *p=ShortArrayTypeWrapper<Intrinsic<T>>::div128(*p,*(q++));
      ++p;
    }
    return A;
  }

  typedef Array<Int,ArrayFormat::ShortData>     ItShortDataArray;
  typedef Array<Float,ArrayFormat::ShortData>   FtShortDataArray;
  typedef Array<Double,ArrayFormat::ShortData>  DbShortDataArray;

  template <>
  ItShortDataArray& ItShortDataArray::operator=(const int& D) {
    return __assign<int>(*this,D);
  }
  template <>
  FtShortDataArray& FtShortDataArray::operator=(const float& D) {
    return __assign<float>(*this,D);
  }
  template <>
  DbShortDataArray& DbShortDataArray::operator=(const double& D) {
    return __assign<double>(*this,D);
  }

  template <>
  ItShortDataArray& ItShortDataArray::operator+=(const int& D) {
    return __add_to<int>(*this,D);
  }
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(const float& D) {
    return __add_to<float>(*this,D);
  }
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(const double& D) {
    return __add_to<double>(*this,D);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator+=(
      const ArrayExpression<ItShortDataArray,int>& A) {
    return __add_to<int>(*this,A);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator+=(
      const ArrayExpression<ItShortDataArray,int>&& A) {
    return __add_to<int>(*this,A);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<FtShortDataArray,float>& A) {
    return __add_to<float>(*this,A);;
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<FtShortDataArray,float>&& A) {
    return __add_to<float>(*this,A);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<DbShortDataArray,double>& A) {
    return __add_to<double>(*this,A);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<DbShortDataArray,double>&& A) {
    return __add_to<double>(*this,A);
  }

  template <>
  ItShortDataArray& ItShortDataArray::operator-=(const int& D) {
    return __substract_to<int>(*this,D);
  }
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(const float& D) {
    return __substract_to<float>(*this,D);
  }
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(const double& D) {
    return __substract_to<double>(*this,D);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator-=(
      const ArrayExpression<ItShortDataArray,int>& A) {
    return __substract_to<int>(*this,A);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator-=(
      const ArrayExpression<ItShortDataArray,int>&& A) {
    return __substract_to<int>(*this,A);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<FtShortDataArray,float>& A) {
    return __substract_to<float>(*this,A);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<FtShortDataArray,float>&& A) {
    return __substract_to<float>(*this,A);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<DbShortDataArray,double>& A) {
    return __substract_to<double>(*this,A);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<DbShortDataArray,double>&& A) {
    return __substract_to<double>(*this,A);
  }

  template <>
  ItShortDataArray& ItShortDataArray::operator*=(const int& D) {
    return __multiple_to<int>(*this,D);
  }
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(const float& D) {
    return __multiple_to<float>(*this,D);
  }
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(const double& D) {
    return __multiple_to<double>(*this,D);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ItShortDataArray,int>& A) {
    return __multiple_to<int>(*this,A);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ItShortDataArray,int>&& A) {
    return __multiple_to<int>(*this,A);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<FtShortDataArray,float>& A) {
    return __multiple_to<float>(*this,A);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<FtShortDataArray,float>&& A) {
    return __multiple_to<float>(*this,A);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<DbShortDataArray,double>& A) {
    return __multiple_to<double>(*this,A);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<DbShortDataArray,double>&& A) {
    return __multiple_to<double>(*this,A);
  }

  template <>
  FtShortDataArray& FtShortDataArray::operator/=(const float& D) {
    return __divide_to<float>(*this,D);
  }
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(const double& D) {
    return __divide_to<double>(*this,D);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<FtShortDataArray,float>& A) {
    return __divide_to<float>(*this,A);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<FtShortDataArray,float>&& A) {
    return __divide_to<float>(*this,A);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<DbShortDataArray,double>& A) {
    return __divide_to<double>(*this,A);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<DbShortDataArray,double>&& A) {
    return __divide_to<double>(*this,A);
  }

  template <typename T,template<typename,typename> class ArrayOp>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __more_more(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         ArrayOp<Intrinsic<T>,
                 typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type>,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>& E,
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*f)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&),
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*g)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&)) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<Intrinsic<T>,
                    typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type>
            AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=ShortArrayTypeWrapper<Intrinsic<T>>::set_from_unit(
              ((AType const&)E).first());
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).second().head());
    for(;p!=e;) { *p=f(*p,g(u,*(q++))); ++p; }
  }
  template <typename T,template<typename,typename> class ArrayOp>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __more_more(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         ArrayOp<Intrinsic<T>,
                 typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type>,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>&& E,
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*f)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&),
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*g)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&)) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<Intrinsic<T>,
                    typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type>
            AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=ShortArrayTypeWrapper<Intrinsic<T>>::set_from_unit(
              ((AType const&)E).first());
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).second().head());
    for(;p!=e;) { *p=f(*p,g(u,*(q++))); ++p; }
  }
  template <typename T,template<typename,typename> class ArrayOp>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __more_more(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         ArrayOp<typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
                 Intrinsic<T>>,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>& E,
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*f)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&),
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*g)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&)) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
                    Intrinsic<T>>
            AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=ShortArrayTypeWrapper<Intrinsic<T>>::set_from_unit(
              ((AType const&)E).second());
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).first().head());
    for(;p!=e;) { *p=f(*p,g(*(q++),u)); ++p; }
  }
  template <typename T,template<typename,typename> class ArrayOp>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __more_more(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         ArrayOp<typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
                 Intrinsic<T>>,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>&& E,
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*f)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&),
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*g)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&)) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
                    Intrinsic<T>>
            AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=ShortArrayTypeWrapper<Intrinsic<T>>::set_from_unit(
              ((AType const&)E).second());
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).first().head());
    for(;p!=e;) { *p=f(*p,g(*(q++),u)); ++p; }
  }
  template <typename T,template<typename,typename> class ArrayOp>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __more_more(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         ArrayOp<typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
                 typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type>,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>& E,
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*f)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&),
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*g)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&)) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
                    typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type>
            AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).first().head());
    T128 *r=reinterpret_cast<T128*>(((AType const&)E).second().head());
    for(;p!=e;) { *p=f(*p,g(*(q++),*(r++))); ++p; }
  }
  template <typename T,template<typename,typename> class ArrayOp>
  typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type&
  __more_more(
      typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
         ArrayOp<typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
                 typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type>,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value_type>&& E,
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*f)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&),
      typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type (*g)(
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&,
         typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type const&)) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename ShortArrayTypeWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type,
                    typename ShortArrayTypeWrapper<Intrinsic<T>>::array_type>
            AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).first().head());
    T128 *r=reinterpret_cast<T128*>(((AType const&)E).second().head());
    for(;p!=e;) { *p=f(*p,g(*(q++),*(r++))); ++p; }
  }

  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<Int,ItShortDataArray>,int>& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::add128,
        ShortArrayTypeWrapper<Int>::mul128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<Int,ItShortDataArray>,int>&& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::add128,
        ShortArrayTypeWrapper<Int>::mul128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<ItShortDataArray,Int>,int>& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::add128,
        ShortArrayTypeWrapper<Int>::mul128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<ItShortDataArray,Int>,int>&& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::add128,
        ShortArrayTypeWrapper<Int>::mul128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<ItShortDataArray,ItShortDataArray>,
                                     int>& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::add128,
        ShortArrayTypeWrapper<Int>::mul128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<ItShortDataArray,ItShortDataArray>,
                                     int>&& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::add128,
        ShortArrayTypeWrapper<Int>::mul128);
  }

  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<Float,FtShortDataArray>,float>& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::mul128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<Float,FtShortDataArray>,float>&& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::mul128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<FtShortDataArray,Float>,float>& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::mul128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<FtShortDataArray,Float>,float>&& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::mul128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<FtShortDataArray,FtShortDataArray>,
                                     float>& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::mul128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<FtShortDataArray,FtShortDataArray>,
                                     float>&& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::mul128);
  }

  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<Double,DbShortDataArray>,double>& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::mul128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<Double,DbShortDataArray>,double>&& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::mul128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<DbShortDataArray,Double>,double>& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::mul128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<ArrayMul<DbShortDataArray,Double>,double>&& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::mul128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
     const ArrayExpression<ArrayMul<DbShortDataArray,DbShortDataArray>,
                           double>& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::mul128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
     const ArrayExpression<ArrayMul<DbShortDataArray,DbShortDataArray>,
                           double>&& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::mul128);
  }

  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<Float,FtShortDataArray>,float>& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::div128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<Float,FtShortDataArray>,float>&& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::div128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<FtShortDataArray,Float>,float>& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::div128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<FtShortDataArray,Float>,float>&& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::div128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<FtShortDataArray,FtShortDataArray>,
                            float>& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::div128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::add128,
        ShortArrayTypeWrapper<Float>::div128);
  }

  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<Double,DbShortDataArray>,double>& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::div128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<Double,DbShortDataArray>,double>&& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::div128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<DbShortDataArray,Double>,double>& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::div128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<DbShortDataArray,Double>,double>&& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::div128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<DbShortDataArray,DbShortDataArray>,
                            double>& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::div128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<ArrayDiv<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::add128,
        ShortArrayTypeWrapper<Double>::div128);
  }

  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<Int,ItShortDataArray>,int>& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::substract128,
        ShortArrayTypeWrapper<Int>::mul128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<Int,ItShortDataArray>,int>&& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::substract128,
        ShortArrayTypeWrapper<Int>::mul128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<ItShortDataArray,Int>,int>& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::substract128,
        ShortArrayTypeWrapper<Int>::mul128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<ItShortDataArray,Int>,int>&& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::substract128,
        ShortArrayTypeWrapper<Int>::mul128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<ItShortDataArray,ItShortDataArray>,
                            int>& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::substract128,
        ShortArrayTypeWrapper<Int>::mul128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<ItShortDataArray,ItShortDataArray>,
                            int>&& EA) {
    return __more_more<int,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Int>::substract128,
        ShortArrayTypeWrapper<Int>::mul128);
  }

  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<Float,FtShortDataArray>,float>& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::mul128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<Float,FtShortDataArray>,float>&& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::mul128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<FtShortDataArray,Float>,float>& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::mul128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<FtShortDataArray,Float>,float>&& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::mul128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<FtShortDataArray,FtShortDataArray>,
                            float>& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::mul128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    return __more_more<float,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::mul128);
  }

  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<Double,DbShortDataArray>,double>& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::mul128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<Double,DbShortDataArray>,double>&& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::mul128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<DbShortDataArray,Double>,double>& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::mul128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<DbShortDataArray,Double>,double>&& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::mul128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<DbShortDataArray,DbShortDataArray>,
                            double>& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::mul128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayMul<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    return __more_more<double,ArrayMul>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::mul128);
  }

  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<Float,FtShortDataArray>,float>& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::div128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<Float,FtShortDataArray>,float>&& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::div128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<FtShortDataArray,Float>,float>& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::div128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<FtShortDataArray,Float>,float>&& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::div128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<FtShortDataArray,FtShortDataArray>,
                            float>& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::div128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    return __more_more<float,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Float>::substract128,
        ShortArrayTypeWrapper<Float>::div128);
  }

  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<Double,DbShortDataArray>,double>& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::div128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<Double,DbShortDataArray>,double>&& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::div128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<DbShortDataArray,Double>,double>& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::div128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<DbShortDataArray,Double>,double>&& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::div128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<DbShortDataArray,DbShortDataArray>,
                            double>& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::div128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<ArrayDiv<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    return __more_more<double,ArrayDiv>(*this,EA,
        ShortArrayTypeWrapper<Double>::substract128,
        ShortArrayTypeWrapper<Double>::div128);
  }

  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySum<Int,ItShortDataArray>,int>& EA) {
    return __more_more<int,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::add128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySum<Int,ItShortDataArray>,int>&& EA) {
    return __more_more<int,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::add128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySum<ItShortDataArray,Int>,int>& EA) {
    return __more_more<int,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::add128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySum<ItShortDataArray,Int>,int>&& EA) {
    return __more_more<int,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::add128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySum<ItShortDataArray,ItShortDataArray>,
                            int>& EA) {
    return __more_more<int,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::add128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySum<ItShortDataArray,ItShortDataArray>,
                            int>&& EA) {
    return __more_more<int,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::add128);
  }

  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySum<Float,FtShortDataArray>,float>& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::add128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySum<Float,FtShortDataArray>,float>&& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::add128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySum<FtShortDataArray,Float>,float>& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::add128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySum<FtShortDataArray,Float>,float>&& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::add128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySum<FtShortDataArray,FtShortDataArray>,
                            float>& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::add128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySum<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::add128);
  }

  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySum<Double,DbShortDataArray>,double>& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::add128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySum<Double,DbShortDataArray>,double>&& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::add128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySum<DbShortDataArray,Double>,double>& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::add128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySum<DbShortDataArray,Double>,double>&& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::add128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySum<DbShortDataArray,DbShortDataArray>,
                            double>& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::add128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySum<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::add128);
  }

  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySub<Int,ItShortDataArray>,int>& EA) {
    return __more_more<int,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::substract128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySub<Int,ItShortDataArray>,int>&& EA) {
    return __more_more<int,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::substract128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySub<ItShortDataArray,Int>,int>& EA) {
    return __more_more<int,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::substract128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySub<ItShortDataArray,Int>,int>&& EA) {
    return __more_more<int,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::substract128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySub<ItShortDataArray,ItShortDataArray>,
                            int>& EA) {
    return __more_more<int,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::substract128);
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ArraySub<ItShortDataArray,ItShortDataArray>,
                            int>&& EA) {
    return __more_more<int,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Int>::mul128,
        ShortArrayTypeWrapper<Int>::substract128);
  }

  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySub<Float,FtShortDataArray>,float>& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::substract128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySub<Float,FtShortDataArray>,float>&& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::substract128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySub<FtShortDataArray,Float>,float>& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::substract128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySub<FtShortDataArray,Float>,float>&& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::substract128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySub<FtShortDataArray,FtShortDataArray>,
                            float>& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::substract128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<ArraySub<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::mul128,
        ShortArrayTypeWrapper<Float>::substract128);
  }

  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySub<Double,DbShortDataArray>,double>& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::substract128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySub<Double,DbShortDataArray>,double>&& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::substract128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySub<DbShortDataArray,Double>,double>& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::substract128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySub<DbShortDataArray,Double>,double>&& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::substract128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySub<DbShortDataArray,DbShortDataArray>,
                            double>& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::substract128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<ArraySub<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::mul128,
        ShortArrayTypeWrapper<Double>::substract128);
  }

  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySum<Float,FtShortDataArray>,float>& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::add128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySum<Float,FtShortDataArray>,float>&& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::add128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySum<FtShortDataArray,Float>,float>& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::add128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySum<FtShortDataArray,Float>,float>&& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::add128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySum<FtShortDataArray,FtShortDataArray>,
                            float>& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::add128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySum<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    return __more_more<float,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::add128);
  }

  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySum<Double,DbShortDataArray>,double>& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::add128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySum<Double,DbShortDataArray>,double>&& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::add128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySum<DbShortDataArray,Double>,double>& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::add128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySum<DbShortDataArray,Double>,double>&& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::add128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySum<DbShortDataArray,DbShortDataArray>,
                            double>& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::add128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySum<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    return __more_more<double,ArraySum>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::add128);
  }

  //------------
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySub<Float,FtShortDataArray>,float>& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::substract128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySub<Float,FtShortDataArray>,float>&& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::substract128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySub<FtShortDataArray,Float>,float>& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::substract128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySub<FtShortDataArray,Float>,float>&& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::substract128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySub<FtShortDataArray,FtShortDataArray>,
                            float>& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::substract128);
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<ArraySub<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    return __more_more<float,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Float>::div128,
        ShortArrayTypeWrapper<Float>::substract128);
  }

  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySub<Double,DbShortDataArray>,double>& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::substract128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySub<Double,DbShortDataArray>,double>&& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::substract128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySub<DbShortDataArray,Double>,double>& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::substract128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySub<DbShortDataArray,Double>,double>&& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::substract128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySub<DbShortDataArray,DbShortDataArray>,
                            double>& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::substract128);
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<ArraySub<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    return __more_more<double,ArraySub>(*this,EA,
        ShortArrayTypeWrapper<Double>::div128,
        ShortArrayTypeWrapper<Double>::substract128);
  }

}

#endif

