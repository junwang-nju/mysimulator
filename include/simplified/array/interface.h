
#ifndef _Array_Interface_H_
#define _Array_Interface_H_

#include "array/container.h"
#include "array/expression.h"

namespace mysimulator {

  template <typename T>
  class Array : public ArrayExpression<Array<T>,T>, public ArrayContainer<T> {

    public:

      typedef Array<T>   Type;
      typedef ArrayExpression<Type,T> ParentTypeA;
      typedef ArrayContainer<T>       ParentTypeB;
      typedef typename ParentTypeB::value_type  value_type;
      typedef unsigned int size_type;
      typedef value_type& reference;
      typedef const value_type& const_reference;

      Array() : ParentTypeA(), ParentTypeB() {}
      Array(size_type size) : ParentTypeA(), ParentTypeB(size) {}
      Array(const Type& A) : Array(A.size()) { operator=(A); }
      Array(Type&& A) : Array() {
        ParentTypeB::swap(static_cast<ParentTypeB>(A));
      }
      template <typename E,typename ET>
      Array(const ArrayExpression<E,ET>& EA) : Array(EA.size()) {
        operator=(EA);
      }
      ~Array() { reset(); }

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
      Type& operator=(const Type& A) { return operator=<Type,T>(A); }
      Type& operator=(const T& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i)   (*this)[i]=D;
        return *this;
      }

      void reset() { ParentTypeB::reset(); }

  };

}

#ifndef __SSE4_1__
#error "\nSSE4.1 is required for Array of intrinsic data! Try -msse4.1 !\n"
#endif

#include "basic/type/same.h"
#include "array/expression-sum.h"
#include "array/expression-substract.h"
#include "array/expression-multiple.h"
#include "array/expression-divide.h"
#include <emmintrin.h>
#include <smmintrin.h>

namespace mysimulator {

  template <typename T>
  class Array<Intrinsic<T>>
      : public ArrayExpression<Array<Intrinsic<T>>,T>,
        public ArrayContainer<Intrinsic<T>> {

    public:

      typedef Array<Intrinsic<T>>           Type;
      typedef ArrayExpression<Type,T>       ParentTypeA;
      typedef ArrayContainer<Intrinsic<T>>  ParentTypeB;
      typedef typename ParentTypeB::value_type  value_type;
      typedef unsigned int size_type;
      typedef value_type& reference;
      typedef const value_type& const_reference;

      Array() : ParentTypeA(), ParentTypeB() {}
      Array(size_type size) : ParentTypeA(), ParentTypeB(size) {}
      Array(const Type& A) : Array(A.size()) { operator=(A); }
      Array(Type&& A) : Array() { ParentTypeB::swap(A); }
      template <typename E,typename ET>
      Array(const ArrayExpression<E,ET>& EA) : Array(EA.size()) {
        operator=(EA);
      }
      ~Array() { reset(); }

      operator bool() const { return ParentTypeB::operator bool(); }
      size_type size() const { return ParentTypeB::size(); }
      reference operator[](size_type i) { return ParentTypeB::operator[](i); }
      const_reference operator[](size_type i) const {
        return ParentTypeB::operator[](i);
      }
      void reset() { ParentTypeB::reset(); }

      template <typename E,typename ET>
      Type& operator=(const ArrayExpression<E,ET>& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i) (*this)[i]=EA[i];
        return *this;
      }
      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        __m128i* p=reinterpret_cast<__m128i*>(this->head());
        __m128i* q=reinterpret_cast<__m128i*>(A.head());
        const __m128i* e=p+this->size128();
        for(;p!=e;) _mm_store_si128(p++,*(q++));
      }
      Type& operator=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i) (*this)[i]=D;
        return *this;
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((value_type)((T1)D));
      }

      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>& A) {
        ArraySum<EA,EB> const& RA=static_cast<ArraySum<EA,EB> const&>(A);
        operator=(RA.first());
        return operator+=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArraySub<EA,EB>,typename ArraySub<EA,EB>::value_type>& A) {
        ArraySub<EA,EB> const& RA=static_cast<ArraySub<EA,EB> const&>(A);
        operator=(RA.first());
        return operator-=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArrayMul<EA,EB>,typename ArrayMul<EA,EB>::value_type>& A) {
        ArrayMul<EA,EB> const& RA=static_cast<ArrayMul<EA,EB> const&>(A);
        operator=(RA.first());
        return operator*=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator=(
          const ArrayExpression<
                  ArrayDiv<EA,EB>,typename ArrayDiv<EA,EB>::value_type>& A) {
        ArrayDiv<EA,EB> const& RA=static_cast<ArrayDiv<EA,EB> const&>(A);
        operator=(RA.first());
        return operator/=(RA.second());
      }

      template <typename E,typename ET>
      Type& operator+=(const ArrayExpression<E,ET>& EA) {
        static_assert(
            __same_type<T,typename __dual_selector<T,ET,__sum_flag>::Type>::FG,
            "Type T cannot accept SUM result!\n");
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
        return operator+=((value_type)((T1)D));
      }

      template <typename EA,typename EB>
      Type& operator+=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>& A) {
        ArraySum<EA,EB> const& RA=static_cast<ArraySum<EA,EB> const&>(A);
        operator+=(RA.first());
        return operator+=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator+=(
          const ArrayExpression<
                  ArraySub<EA,EB>,typename ArraySub<EA,EB>::value_type>& A) {
        ArraySub<EA,EB> const& RA=static_cast<ArraySub<EA,EB> const&>(A);
        operator+=(RA.first());
        return operator-=(RA.second());
      }

      template <typename E,typename ET>
      Type& operator-=(const ArrayExpression<E,ET>& EA) {
        static_assert(
            __same_type<T,typename __dual_selector<T,ET,__sub_flag>::Type>::FG,
            "Type T cannot accept SUBSTRACT result!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]=EA[i];
        return *this;
      }
      Type& operator-=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i)   (*this)[i]-=D;
        return *this;
      }
      template <typename T1>
      Type& operator-=(const Intrinsic<T1>& D) {
        return operator-=((value_type)((T1)D));
      }

      template <typename EA,typename EB>
      Type& operator-=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>& A) {
        ArraySum<EA,EB> const& RA=static_cast<ArraySum<EA,EB> const&>(A);
        operator-=(RA.first());
        return operator-=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator-=(
          const ArrayExpression<
          ArraySub<EA,EB>,typename ArraySub<EA,EB>::value_type>& A) {
        ArraySub<EA,EB> const& RA=static_cast<ArraySub<EA,EB> const&>(A);
        operator-=(RA.first());
        return operator+=(RA.second());
      }

      template <typename E,typename ET>
      Type& operator*=(const ArrayExpression<E,ET>& EA) {
        static_assert(
            __same_type<T,typename __dual_selector<T,ET,__mul_flag>::Type>::FG,
            "Type T cannot accept MULTIPLE result!\n");
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
        return operator*=((value_type)((T1)D));
      }

      template <typename EA,typename EB>
      Type& operator*=(
          const ArrayExpression<
                  ArrayMul<EA,EB>,typename ArrayMul<EA,EB>::value_type>& A) {
        ArrayMul<EA,EB> const& RA=static_cast<ArrayMul<EA,EB> const&>(A);
        operator*=(RA.first());
        return operator*=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator*=(
          const ArrayExpression<
                  ArrayDiv<EA,EB>,typename ArrayDiv<EA,EB>::value_type>& A) {
        ArrayDiv<EA,EB> const& RA=static_cast<ArrayDiv<EA,EB> const&>(A);
        operator*=(RA.first());
        return operator/=(RA.second());
      }

      template <typename E,typename ET>
      Type& operator/=(const ArrayExpression<E,ET>& EA) {
        static_assert(
            __same_type<T,typename __dual_selector<T,ET,__div_flag>::Type>::FG,
            "Type T cannot accept DIVIDE result!\n");
        static_assert(Intrinsic<T>::IsFloatPoint,
                      "Divide only works for float-point data!\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]/=EA[i];
        return *this;
      }
      Type& operator/=(const value_type& D) {
        static_assert(Intrinsic<T>::IsFloatPoint,
                      "Divide only works for float-point data!\n");
        assert((bool)(*this));
        for(size_type i=0;i<size();++i)   (*this)[i]/=D;
      }
      template <typename T1>
      Type& operator/=(const Intrinsic<T1>& D) {
        return operator/=((value_type)((T1)D));
      }

      template <typename EA,typename EB>
      Type& operator/=(
          const ArrayExpression<
                  ArrayMul<EA,EB>,typename ArrayMul<EA,EB>::value_type>& A) {
        ArrayMul<EA,EB> const& RA=static_cast<ArrayMul<EA,EB> const&>(A);
        operator/=(RA.first());
        return operator/=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator/=(
          const ArrayExpression<
                  ArrayDiv<EA,EB>,typename ArrayDiv<EA,EB>::value_type>& A) {
        ArrayDiv<EA,EB> const& RA=static_cast<ArrayDiv<EA,EB> const&>(A);
        operator/=(RA.first());
        return operator*=(RA.second());
      }

  };

  template <typename T>
  class __ArrayWrapper {};

  template <>
  class __ArrayWrapper<Int> {
    public:
      typedef Int::value_type value_type;
      typedef Array<Int>      array_type;
      typedef __m128i         value128_type;
      static inline
      value128_type set_from_unit(int D) { return _mm_set1_epi32(D); }
  };

  template <>
  class __ArrayWrapper<Float> {
    public:
      typedef Float::value_type value_type;
      typedef Array<Float>      array_type;
      typedef __m128            value128_type;
      static inline
      value128_type set_from_unit(float D) { return _mm_set1_ps(D); }
  };

  template <>
  class __ArrayWrapper<Double> {
    public:
      typedef Double::value_type    value_type;
      typedef Array<Double>         array_type;
      typedef __m128d               value128_type;
      static inline
      value128_type set_from_unit(double D) { return _mm_set1_pd(D); }
  };

  template <typename T,__ArrayOperationName RunOp>
  typename __ArrayWrapper<Intrinsic<T>>::value128_type
  __Op128(typename __ArrayWrapper<Intrinsic<T>>::value128_type const& a,
          typename __ArrayWrapper<Intrinsic<T>>::value128_type const& b) {
    assert("This Operation is not found!\n");
    return (typename __ArrayWrapper<Intrinsic<T>>::value128_type)0;
  }

  template <>
  inline typename __ArrayWrapper<Int>::value128_type
  __Op128<int,__ArrayOperationName::Add>(
      typename __ArrayWrapper<Int>::value128_type const& a,
      typename __ArrayWrapper<Int>::value128_type const& b) {
    return _mm_add_epi32(a,b);
  }

  template <>
  inline typename __ArrayWrapper<Int>::value128_type
  __Op128<int,__ArrayOperationName::Substract>(
      typename __ArrayWrapper<Int>::value128_type const& a,
      typename __ArrayWrapper<Int>::value128_type const& b) {
    return _mm_sub_epi32(a,b);
  }

  template <>
  inline typename __ArrayWrapper<Int>::value128_type
  __Op128<int,__ArrayOperationName::Multiple>(
      typename __ArrayWrapper<Int>::value128_type const& a,
      typename __ArrayWrapper<Int>::value128_type const& b) {
    return _mm_mullo_epi32(a,b);
  }

  template <>
  inline typename __ArrayWrapper<Float>::value128_type
  __Op128<float,__ArrayOperationName::Add>(
      typename __ArrayWrapper<Float>::value128_type const& a,
      typename __ArrayWrapper<Float>::value128_type const& b) {
    return _mm_add_ps(a,b);
  }

  template <>
  inline typename __ArrayWrapper<Float>::value128_type
  __Op128<float,__ArrayOperationName::Substract>(
      typename __ArrayWrapper<Float>::value128_type const& a,
      typename __ArrayWrapper<Float>::value128_type const& b) {
    return _mm_sub_ps(a,b);
  }

  template <>
  inline typename __ArrayWrapper<Float>::value128_type
  __Op128<float,__ArrayOperationName::Multiple>(
      typename __ArrayWrapper<Float>::value128_type const& a,
      typename __ArrayWrapper<Float>::value128_type const& b) {
    return _mm_mul_ps(a,b);
  }

  template <>
  inline typename __ArrayWrapper<Float>::value128_type
  __Op128<float,__ArrayOperationName::Divide>(
      typename __ArrayWrapper<Float>::value128_type const& a,
      typename __ArrayWrapper<Float>::value128_type const& b) {
    return _mm_div_ps(a,b);
  }

  template <>
  inline typename __ArrayWrapper<Double>::value128_type
  __Op128<double,__ArrayOperationName::Add>(
      typename __ArrayWrapper<Double>::value128_type const& a,
      typename __ArrayWrapper<Double>::value128_type const& b) {
    return _mm_add_pd(a,b);
  }

  template <>
  inline typename __ArrayWrapper<Double>::value128_type
  __Op128<double,__ArrayOperationName::Substract>(
      typename __ArrayWrapper<Double>::value128_type const& a,
      typename __ArrayWrapper<Double>::value128_type const& b) {
    return _mm_sub_pd(a,b);
  }

  template <>
  inline typename __ArrayWrapper<Double>::value128_type
  __Op128<double,__ArrayOperationName::Multiple>(
      typename __ArrayWrapper<Double>::value128_type const& a,
      typename __ArrayWrapper<Double>::value128_type const& b) {
    return _mm_mul_pd(a,b);
  }

  template <>
  inline typename __ArrayWrapper<Double>::value128_type
  __Op128<double,__ArrayOperationName::Divide>(
      typename __ArrayWrapper<Double>::value128_type const& a,
      typename __ArrayWrapper<Double>::value128_type const& b) {
    return _mm_div_pd(a,b);
  }

  template <typename T>
  typename __ArrayWrapper<Intrinsic<T>>::array_type&
  __assign(typename __ArrayWrapper<Intrinsic<T>>::array_type& A,
           const typename __ArrayWrapper<Intrinsic<T>>::value_type& D) {
    assert((bool)A);
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=__ArrayWrapper<Intrinsic<T>>::set_from_unit(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;)   *(p++)=u;
    return A;
  }

  template <typename T,__ArrayOperationName RunOp>
  typename __ArrayWrapper<Intrinsic<T>>::array_type&
  __val_op(typename __ArrayWrapper<Intrinsic<T>>::array_type& A,
           const typename __ArrayWrapper<Intrinsic<T>>::value_type& D) {
    assert((bool)A);
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=__ArrayWrapper<Intrinsic<T>>::set_from_unit(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;) { *p=__Op128<T,RunOp>(*p,u); ++p; }
  }

  template <typename T,__ArrayOperationName RunOp>
  typename __ArrayWrapper<Intrinsic<T>>::array_type&
  __array_op(typename __ArrayWrapper<Intrinsic<T>>::array_type& A,
             const ArrayExpression<
               typename __ArrayWrapper<Intrinsic<T>>::array_type,
               typename __ArrayWrapper<Intrinsic<T>>::value_type>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    typedef typename __ArrayWrapper<Intrinsic<T>>::array_type AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    T128 *q=reinterpret_cast<T128*>(((AType const&)E).head());
    const T128 *e=p+A.size128();
    for(;p!=e;) { *p=__Op128<T,RunOp>(*p,*(q++));  ++p; }
    return A;
  }

  template <typename T,template<typename,typename> class ArrayOp,
            __ArrayOperationName RunOp>
  typename __ArrayWrapper<Intrinsic<T>>::array_type&
  __two_level_op(
      typename __ArrayWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
        ArrayOp<Intrinsic<T>,typename __ArrayWrapper<Intrinsic<T>>::array_type>,
        typename __ArrayWrapper<Intrinsic<T>>::value_type>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<Intrinsic<T>,
                    typename __ArrayWrapper<Intrinsic<T>>::array_type> AType;
    AType const& RA=static_cast<AType const&>(E);
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=__ArrayWrapper<Intrinsic<T>>::set_from_unit(RA.first());
    T128 *q=reinterpret_cast<T128*>(RA.second().head());
    for(;p!=e;) {
      *p=__Op128<T,RunOp>(*p,__Op128<T,AType::OpName>(u,*(q++)));
      ++p;
    }
    return A;
  }
  template <typename T,template<typename,typename> class ArrayOp,
            __ArrayOperationName RunOp>
  typename __ArrayWrapper<Intrinsic<T>>::array_type&
  __two_level_op(
      typename __ArrayWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
        ArrayOp<typename __ArrayWrapper<Intrinsic<T>>::array_type,Intrinsic<T>>,
        typename __ArrayWrapper<Intrinsic<T>>::value_type>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<typename __ArrayWrapper<Intrinsic<T>>::array_type,
                    Intrinsic<T>> AType;
    AType const& RA=static_cast<AType const&>(E);
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=__ArrayWrapper<Intrinsic<T>>::set_from_unit(RA.second());
    T128 *q=reinterpret_cast<T128*>(RA.first().head());
    for(;p!=e;) {
      *p=__Op128<T,RunOp>(*p,__Op128<T,AType::OpName>(*(q++),u));
      ++p;
    }
    return A;
  }
  template <typename T,template<typename,typename> class ArrayOp,
            __ArrayOperationName RunOp>
  typename __ArrayWrapper<Intrinsic<T>>::array_type&
  __two_level_op(
      typename __ArrayWrapper<Intrinsic<T>>::array_type& A,
      const ArrayExpression<
        ArrayOp<typename __ArrayWrapper<Intrinsic<T>>::array_type,
                typename __ArrayWrapper<Intrinsic<T>>::array_type>,
        typename __ArrayWrapper<Intrinsic<T>>::value_type>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<typename __ArrayWrapper<Intrinsic<T>>::array_type,
                    typename __ArrayWrapper<Intrinsic<T>>::array_type> AType;
    AType const& RA=static_cast<AType const&>(E);
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 *q=reinterpret_cast<T128*>(RA.first().head());
    T128 *r=reinterpret_cast<T128*>(RA.second().head());
    for(;p!=e;) {
      *p=__Op128<T,RunOp>(*p,__Op128<T,AType::OpName>(*(q++),*(r++)));
      ++p;
    }
    return A;
  }

  template <>
  Array<Int>& Array<Int>::operator=(const int& D) {
    return __assign<int>(*this,D);
  }
  template <>
  Array<Float>& Array<Float>::operator=(const float& D) {
    return __assign<float>(*this,D);
  }
  template <>
  Array<Double>& Array<Double>::operator=(const double& D) {
    return __assign<double>(*this,D);
  }

  template <>
  Array<Int>& Array<Int>::operator+=(const int& D) {
    return __val_op<int,__ArrayOperationName::Add>(*this,D);
  }
  template <>
  Array<Float>& Array<Float>::operator+=(const float& D) {
    return __val_op<float,__ArrayOperationName::Add>(*this,D);
  }
  template <>
  Array<Double>& Array<Double>::operator+=(const double& D) {
    return __val_op<double,__ArrayOperationName::Add>(*this,D);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator+=(const ArrayExpression<Array<Int>,int>& A) {
    return __array_op<int,__ArrayOperationName::Add>(*this,A);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayExpression<Array<Float>,float>& A) {
    return __array_op<float,__ArrayOperationName::Add>(*this,A);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayExpression<Array<Double>,double>& A) {
    return __array_op<double,__ArrayOperationName::Add>(*this,A);
  }

  template <>
  Array<Int>& Array<Int>::operator-=(const int& D) {
    return __val_op<int,__ArrayOperationName::Substract>(*this,D);
  }
  template <>
  Array<Float>& Array<Float>::operator-=(const float& D) {
    return __val_op<float,__ArrayOperationName::Substract>(*this,D);
  }
  template <>
  Array<Double>& Array<Double>::operator-=(const double& D) {
    return __val_op<double,__ArrayOperationName::Substract>(*this,D);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator-=(const ArrayExpression<Array<Int>,int>& A) {
    return __array_op<int,__ArrayOperationName::Substract>(*this,A);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayExpression<Array<Float>,float>& A) {
    return __array_op<float,__ArrayOperationName::Substract>(*this,A);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayExpression<Array<Double>,double>& A) {
    return __array_op<double,__ArrayOperationName::Add>(*this,A);
  }

  template <>
  Array<Int>& Array<Int>::operator*=(const int& D) {
    return __val_op<int,__ArrayOperationName::Multiple>(*this,D);
  }
  template <>
  Array<Float>& Array<Float>::operator*=(const float& D) {
    return __val_op<float,__ArrayOperationName::Multiple>(*this,D);
  }
  template <>
  Array<Double>& Array<Double>::operator*=(const double& D) {
    return __val_op<double,__ArrayOperationName::Multiple>(*this,D);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(const ArrayExpression<Array<Int>,int>& A) {
    return __array_op<int,__ArrayOperationName::Multiple>(*this,A);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArrayExpression<Array<Float>,float>& A) {
    return __array_op<float,__ArrayOperationName::Multiple>(*this,A);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArrayExpression<Array<Double>,double>& A) {
    return __array_op<double,__ArrayOperationName::Multiple>(*this,A);
  }

  template <>
  Array<Float>& Array<Float>::operator/=(const float& D) {
    return __val_op<float,__ArrayOperationName::Divide>(*this,D);
  }
  template <>
  Array<Double>& Array<Double>::operator/=(const double& D) {
    return __val_op<double,__ArrayOperationName::Divide>(*this,D);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArrayExpression<Array<Float>,float>& A) {
    return __array_op<float,__ArrayOperationName::Divide>(*this,A);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArrayExpression<Array<Double>,double>& A) {
    return __array_op<double,__ArrayOperationName::Divide>(*this,A);
  }

  // for too-short array, direct operation may be faster
  // for double, 16-mer is balance
  // for float,  2-mer is balance
  template <>
  template <>
  Array<Int>& Array<Int>::operator+=(
      const ArrayExpression<ArrayMul<Int,Array<Int>>,int>& EA) {
    return __two_level_op<int,ArrayMul,__ArrayOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayExpression<ArrayMul<Float,Array<Float>>,float>& EA) {
    return __two_level_op<float,ArrayMul,__ArrayOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayExpression<ArrayMul<Double,Array<Double>>,double>& EA) {
    return __two_level_op<double,ArrayMul,__ArrayOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator+=(
      const ArrayExpression<ArrayMul<Array<Int>,Int>,int>& EA) {
    return __two_level_op<int,ArrayMul,__ArrayOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayExpression<ArrayMul<Array<Float>,Float>,float>& EA) {
    return __two_level_op<float,ArrayMul,__ArrayOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayExpression<ArrayMul<Array<Double>,Double>,double>& EA) {
    return __two_level_op<double,ArrayMul,__ArrayOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator+=(
      const ArrayExpression<ArrayMul<Array<Int>,Array<Int>>,int>& EA) {
    return __two_level_op<int,ArrayMul,__ArrayOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayExpression<ArrayMul<Array<Float>,Array<Float>>,float>& EA) {
    return __two_level_op<float,ArrayMul,__ArrayOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayExpression<ArrayMul<Array<Double>,Array<Double>>,double>& EA) {
    return __two_level_op<double,ArrayMul,__ArrayOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayExpression<ArrayDiv<Float,Array<Float>>,float>& EA) {
    return __two_level_op<float,ArrayDiv,__ArrayOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayExpression<ArrayDiv<Double,Array<Double>>,double>& EA) {
    return __two_level_op<double,ArrayDiv,__ArrayOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayExpression<ArrayDiv<Array<Float>,Float>,float>& EA) {
    return __two_level_op<float,ArrayDiv,__ArrayOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayExpression<ArrayDiv<Array<Double>,Double>,double>& EA) {
    return __two_level_op<double,ArrayDiv,__ArrayOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayExpression<ArrayDiv<Array<Float>,Array<Float>>,float>& EA) {
    return __two_level_op<float,ArrayDiv,__ArrayOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayExpression<ArrayDiv<Array<Double>,Array<Double>>,double>& EA) {
    return __two_level_op<double,ArrayDiv,__ArrayOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator-=(
      const ArrayExpression<ArrayMul<Int,Array<Int>>,int>& EA) {
    return
    __two_level_op<int,ArrayMul,__ArrayOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayExpression<ArrayMul<Float,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArrayMul,__ArrayOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayExpression<ArrayMul<Double,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArrayMul,__ArrayOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator-=(
      const ArrayExpression<ArrayMul<Array<Int>,Int>,int>& EA) {
    return
    __two_level_op<int,ArrayMul,__ArrayOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayExpression<ArrayMul<Array<Float>,Float>,float>& EA) {
    return
    __two_level_op<float,ArrayMul,__ArrayOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayExpression<ArrayMul<Array<Double>,Double>,double>& EA) {
    return
    __two_level_op<double,ArrayMul,__ArrayOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator-=(
      const ArrayExpression<ArrayMul<Array<Int>,Array<Int>>,int>& EA) {
    return
    __two_level_op<int,ArrayMul,__ArrayOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayExpression<ArrayMul<Array<Float>,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArrayMul,__ArrayOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayExpression<ArrayMul<Array<Double>,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArrayMul,__ArrayOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayExpression<ArrayDiv<Float,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArrayDiv,__ArrayOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayExpression<ArrayDiv<Double,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArrayDiv,__ArrayOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayExpression<ArrayDiv<Array<Float>,Float>,float>& EA) {
    return
    __two_level_op<float,ArrayDiv,__ArrayOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayExpression<ArrayDiv<Array<Double>,Double>,double>& EA) {
    return
    __two_level_op<double,ArrayDiv,__ArrayOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayExpression<ArrayDiv<Array<Float>,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArrayDiv,__ArrayOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayExpression<ArrayDiv<Array<Double>,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArrayDiv,__ArrayOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArrayExpression<ArraySum<Int,Array<Int>>,int>& EA) {
    return
    __two_level_op<int,ArraySum,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArrayExpression<ArraySum<Float,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArraySum,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArrayExpression<ArraySum<Double,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArraySum,__ArrayOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArrayExpression<ArraySum<Array<Int>,Int>,int>& EA) {
    return
    __two_level_op<int,ArraySum,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArrayExpression<ArraySum<Array<Float>,Float>,float>& EA) {
    return
    __two_level_op<float,ArraySum,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArrayExpression<ArraySum<Array<Double>,Double>,double>& EA) {
    return
    __two_level_op<double,ArraySum,__ArrayOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArrayExpression<ArraySum<Array<Int>,Array<Int>>,int>& EA) {
    return
    __two_level_op<int,ArraySum,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArrayExpression<ArraySum<Array<Float>,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArraySum,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArrayExpression<ArraySum<Array<Double>,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArraySum,__ArrayOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArrayExpression<ArraySub<Int,Array<Int>>,int>& EA) {
    return
    __two_level_op<int,ArraySub,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArrayExpression<ArraySub<Float,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArraySub,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArrayExpression<ArraySub<Double,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArraySub,__ArrayOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArrayExpression<ArraySub<Array<Int>,Int>,int>& EA) {
    return
    __two_level_op<int,ArraySub,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArrayExpression<ArraySub<Array<Float>,Float>,float>& EA) {
    return
    __two_level_op<float,ArraySub,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArrayExpression<ArraySub<Array<Double>,Double>,double>& EA) {
    return
    __two_level_op<double,ArraySub,__ArrayOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArrayExpression<ArraySub<Array<Int>,Array<Int>>,int>& EA) {
    return
    __two_level_op<int,ArraySub,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArrayExpression<ArraySub<Array<Float>,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArraySub,__ArrayOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArrayExpression<ArraySub<Array<Double>,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArraySub,__ArrayOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArrayExpression<ArraySum<Float,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArraySum,__ArrayOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArrayExpression<ArraySum<Double,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArraySum,__ArrayOperationName::Divide>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArrayExpression<ArraySum<Array<Float>,Float>,float>& EA) {
    return
    __two_level_op<float,ArraySum,__ArrayOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArrayExpression<ArraySum<Array<Double>,Double>,double>& EA) {
    return
    __two_level_op<double,ArraySum,__ArrayOperationName::Divide>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArrayExpression<ArraySum<Array<Float>,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArraySum,__ArrayOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArrayExpression<ArraySum<Array<Double>,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArraySum,__ArrayOperationName::Divide>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArrayExpression<ArraySub<Float,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArraySub,__ArrayOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArrayExpression<ArraySub<Double,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArraySub,__ArrayOperationName::Divide>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArrayExpression<ArraySub<Array<Float>,Float>,float>& EA) {
    return
    __two_level_op<float,ArraySub,__ArrayOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArrayExpression<ArraySub<Array<Double>,Double>,double>& EA) {
    return
    __two_level_op<double,ArraySub,__ArrayOperationName::Divide>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArrayExpression<ArraySub<Array<Float>,Array<Float>>,float>& EA) {
    return
    __two_level_op<float,ArraySub,__ArrayOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArrayExpression<ArraySub<Array<Double>,Array<Double>>,double>& EA) {
    return
    __two_level_op<double,ArraySub,__ArrayOperationName::Divide>(*this,EA);
  }

}

#endif

