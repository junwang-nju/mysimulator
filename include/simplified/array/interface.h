
#ifndef _Array_Interface_H_
#define _Array_Interface_H_

#include "array/container.h"

namespace mysimulator {

  template <typename T,bool _vflag=ArrayContentSelector<T>::_has_value>
  class Array {
    public:
      typedef Array<T,_vflag>   Type;
      Array() = delete;
      Array(const Type&) = delete;
      Type& operator=(const Type&) = delete;
      ~Array() {}
  };

  template <typename T>
  class Array<T,true> : public ArrayContainer<T> {

    public:

      typedef Array<T,true>   Type;
      typedef ArrayContainer<T>       ParentType;
      typedef typename ParentType::monomer_type  monomer_type;
      typedef typename T::value_type  value_type;
      typedef unsigned int size_type;
      typedef monomer_type& reference;
      typedef const monomer_type& const_reference;

      Array() : ParentType() {}
      Array(size_type size) : ParentType(size) {}
      Array(const Type& A) : Array() { ParentType::imprint(A); operator=(A); }
      Array(Type&& A) : ParentType((ParentType&&)A) {}
      ~Array() { reset(); }

      operator bool() const { return ParentType::operator bool(); }
      size_type size() const { return ParentType::size(); }
      reference operator[](size_type i) { return ParentType::operator[](i); }
      const_reference operator[](size_type i) const {
        return ParentType::operator[](i);
      }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i)   (*this)[i]=A[i];
        return *this;
      }
      Type& operator=(const monomer_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i)   (*this)[i]=D;
        return *this;
      }
      Type& operator=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i)   (*this)[i]=D;
        return *this;
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((value_type)((T1)D));
      }

      void reset() { ParentType::reset(); }

  };

  template <typename T>
  class Array<T,false> : public ArrayContainer<T> {

    public:

      typedef Array<T,false>   Type;
      typedef ArrayContainer<T>       ParentType;
      typedef typename ParentType::monomer_type  monomer_type;
      typedef unsigned int size_type;
      typedef monomer_type& reference;
      typedef const monomer_type& const_reference;

      Array() : ParentType() {}
      Array(size_type size) : ParentType(size) {}
      Array(const Type& A) : Array(A.size()) { operator=(A); }
      Array(Type&& A) : ParentType((ParentType&&)A) {}
      ~Array() { reset(); }

      operator bool() const { return ParentType::operator bool(); }
      size_type size() const { return ParentType::size(); }
      reference operator[](size_type i) { return ParentType::operator[](i); }
      const_reference operator[](size_type i) const {
        return ParentType::operator[](i);
      }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i)   (*this)[i]=A[i];
        return *this;
      }
      Type& operator=(const monomer_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i)   (*this)[i]=D;
        return *this;
      }

      void reset() { ParentType::reset(); }

  };

}

#ifndef __SSE4_1__
#error "\nSSE4.1 is required for Array of intrinsic data! Try -msse4.1 !\n"
#endif

#include "basic/type/same.h"
#include "array/expression-operation.h"
#include <emmintrin.h>
#include <smmintrin.h>

namespace mysimulator {

  template <typename T>
  class Array<Intrinsic<T>,true>
      : public ArrayContainer<Intrinsic<T>> {

    public:

      typedef Array<Intrinsic<T>,true>           Type;
      typedef ArrayContainer<Intrinsic<T>>  ParentType;
      typedef typename ParentType::monomer_type  monomer_type;
      typedef T  value_type;
      typedef unsigned int size_type;
      typedef monomer_type& reference;
      typedef const monomer_type& const_reference;

      Array() : ParentType() {}
      Array(size_type size) : ParentType(size) {}
      Array(const Type& A) : Array(A.size()) { operator=(A); }
      Array(Type&& A) : ParentType((ParentType&&)A) {}
      ~Array() { reset(); }

      operator bool() const { return ParentType::operator bool(); }
      size_type size() const { return ParentType::size(); }
      reference operator[](size_type i) { return ParentType::operator[](i); }
      const_reference operator[](size_type i) const {
        return ParentType::operator[](i);
      }
      void reset() { ParentType::reset(); }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        __m128i* p=reinterpret_cast<__m128i*>(this->head());
        __m128i* q=reinterpret_cast<__m128i*>(A.head());
        const __m128i* e=p+this->size128();
        for(;p!=e;) _mm_store_si128(p++,*(q++));
      }
      template <typename ET>
      Type& operator=(Array<ET> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i) (*this)[i]=A[i];
        return *this;
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
      Type& operator=(ArraySum<EA,EB> const& RA) {
        operator=(RA.first());
        return operator+=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator=(ArraySub<EA,EB> const& RA) {
        operator=(RA.first());
        return operator-=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayMul<EA,EB> const& RA) {
        operator=(RA.first());
        return operator*=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayDiv<EA,EB> const& RA) {
        operator=(RA.first());
        return operator/=(RA.second());
      }

      template <typename ET>
      Type& operator+=(const Array<ET>& A) {
        static_assert(
            __same_type<T,typename __dual_selector<T,ET,__sum_flag>::Type>::FG,
            "Type T cannot accept SUM result!\n");
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i)   (*this)[i]+=A[i];
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
      Type& operator+=(ArraySum<EA,EB> const& RA) {
        operator+=(RA.first());
        return operator+=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator+=(ArraySub<EA,EB> const& RA) {
        operator+=(RA.first());
        return operator-=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator+=(ArrayMul<EA,EB> const& RA) {
        assert((bool)(*this));
        assert((bool)RA);
        assert(size()<=RA.size());
        for(size_type i=0;i<size();++i) (*this)[i]+=RA[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator+=(ArrayDiv<EA,EB> const& RA) {
        assert((bool)(*this));
        assert((bool)RA);
        assert(size()<=RA.size());
        for(size_type i=0;i<size();++i) (*this)[i]+=RA[i];
        return *this;
      }

      template <typename ET>
      Type& operator-=(const Array<ET>& A) {
        static_assert(
            __same_type<T,typename __dual_selector<T,ET,__sub_flag>::Type>::FG,
            "Type T cannot accept SUBSTRACT result!\n");
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i)   (*this)[i]=A[i];
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
      Type& operator-=(ArraySum<EA,EB> const& RA) {
        operator-=(RA.first());
        return operator-=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator-=(ArraySub<EA,EB> const& RA) {
        operator-=(RA.first());
        return operator+=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator-=(ArrayMul<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i) (*this)[i]-=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator-=(ArrayDiv<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i) (*this)[i]-=A[i];
        return *this;
      }

      template <typename ET>
      Type& operator*=(const Array<ET>& A) {
        static_assert(
            __same_type<T,typename __dual_selector<T,ET,__mul_flag>::Type>::FG,
            "Type T cannot accept MULTIPLE result!\n");
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i)   (*this)[i]*=A[i];
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
      Type& operator*=(ArraySum<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i)   (*this)[i]*=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator*=(ArraySub<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i)   (*this)[i]*=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator*=(ArrayMul<EA,EB> const& RA) {
        operator*=(RA.first());
        return operator*=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator*=(ArrayDiv<EA,EB> const& RA) {
        operator*=(RA.first());
        return operator/=(RA.second());
      }

      template <typename ET>
      Type& operator/=(const Array<ET>& A) {
        static_assert(
            __same_type<T,typename __dual_selector<T,ET,__div_flag>::Type>::FG,
            "Type T cannot accept DIVIDE result!\n");
        static_assert(Intrinsic<T>::IsFloatPoint,
                      "Divide only works for float-point data!\n");
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i)   (*this)[i]/=A[i];
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
      Type& operator/=(ArraySum<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i)   (*this)[i]/=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator/=(ArraySub<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        for(size_type i=0;i<size();++i)   (*this)[i]/=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator/=(ArrayMul<EA,EB> const& RA) {
        operator/=(RA.first());
        return operator/=(RA.second());
      }
      template <typename EA,typename EB>
      Type& operator/=(ArrayDiv<EA,EB> const& RA) {
        operator/=(RA.first());
        return operator*=(RA.second());
      }

  };

  template <typename T>
  class __ArrayWrapper {};

  template <>
  class __ArrayWrapper<Int> {
    public:
      typedef __m128i         value128_type;
      static inline
      value128_type set_from_unit(int D) { return _mm_set1_epi32(D); }
  };

  template <>
  class __ArrayWrapper<Float> {
    public:
      typedef __m128            value128_type;
      static inline
      value128_type set_from_unit(float D) { return _mm_set1_ps(D); }
  };

  template <>
  class __ArrayWrapper<Double> {
    public:
      typedef __m128d               value128_type;
      static inline
      value128_type set_from_unit(double D) { return _mm_set1_pd(D); }
  };

  template <typename T,__ExpressionOperationName RunOp>
  typename __ArrayWrapper<Intrinsic<T>>::value128_type
  __Op128(typename __ArrayWrapper<Intrinsic<T>>::value128_type const& a,
          typename __ArrayWrapper<Intrinsic<T>>::value128_type const& b) {
    assert("This Operation is not found!\n");
    return (typename __ArrayWrapper<Intrinsic<T>>::value128_type)0;
  }

  template <>
  inline __m128i __Op128<int,__ExpressionOperationName::Add>(
      __m128i const& a,__m128i const& b) {
    return _mm_add_epi32(a,b);
  }

  template <>
  inline __m128i __Op128<int,__ExpressionOperationName::Substract>(
      __m128i const& a,__m128i const& b) {
    return _mm_sub_epi32(a,b);
  }

  template <>
  inline __m128i __Op128<int,__ExpressionOperationName::Multiple>(
      __m128i const& a,__m128i const& b) {
    return _mm_mullo_epi32(a,b);
  }

  template <>
  inline __m128 __Op128<float,__ExpressionOperationName::Add>(
      __m128 const& a,__m128 const& b) {
    return _mm_add_ps(a,b);
  }

  template <>
  inline __m128 __Op128<float,__ExpressionOperationName::Substract>(
      __m128 const& a,__m128 const& b) {
    return _mm_sub_ps(a,b);
  }

  template <>
  inline __m128 __Op128<float,__ExpressionOperationName::Multiple>(
      __m128 const& a,__m128 const& b) {
    return _mm_mul_ps(a,b);
  }

  template <>
  inline __m128 __Op128<float,__ExpressionOperationName::Divide>(
      __m128 const& a,__m128 const& b) {
    return _mm_div_ps(a,b);
  }

  template <>
  inline __m128d __Op128<double,__ExpressionOperationName::Add>(
      __m128d const& a,__m128d const& b) {
    return _mm_add_pd(a,b);
  }

  template <>
  inline __m128d __Op128<double,__ExpressionOperationName::Substract>(
      __m128d const& a,__m128d const& b) {
    return _mm_sub_pd(a,b);
  }

  template <>
  inline __m128d __Op128<double,__ExpressionOperationName::Multiple>(
      __m128d const& a,__m128d const& b) {
    return _mm_mul_pd(a,b);
  }

  template <>
  inline __m128d __Op128<double,__ExpressionOperationName::Divide>(
      __m128d const& a,__m128d const& b) {
    return _mm_div_pd(a,b);
  }

  template <typename T>
  Array<Intrinsic<T>>&
  __assign(Array<Intrinsic<T>>& A,const T& D) {
    assert((bool)A);
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=__ArrayWrapper<Intrinsic<T>>::set_from_unit(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;)   *(p++)=u;
    return A;
  }

  template <typename T,__ExpressionOperationName RunOp>
  Array<Intrinsic<T>>&
  __val_op(Array<Intrinsic<T>>& A,const T& D) {
    assert((bool)A);
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=__ArrayWrapper<Intrinsic<T>>::set_from_unit(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;) { *p=__Op128<T,RunOp>(*p,u); ++p; }
    return A;
  }

  template <typename T,__ExpressionOperationName RunOp>
  Array<Intrinsic<T>>&
  __array_op(Array<Intrinsic<T>>& A,const Array<Intrinsic<T>>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    T128 *p=reinterpret_cast<T128*>(A.head());
    T128 *q=reinterpret_cast<T128*>(E.head());
    const T128 *e=p+A.size128();
    for(;p!=e;) { *p=__Op128<T,RunOp>(*p,*(q++));  ++p; }
    return A;
  }

  template <typename T,template<typename,typename> class ArrayOp,
            __ExpressionOperationName RunOp>
  Array<Intrinsic<T>>&
  __two_level_op(
      Array<Intrinsic<T>>& A,
      const ArrayOp<Intrinsic<T>,Array<Intrinsic<T>>>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<Intrinsic<T>,Array<Intrinsic<T>>> AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=__ArrayWrapper<Intrinsic<T>>::set_from_unit(E.first());
    T128 *q=reinterpret_cast<T128*>(E.second().head());
    for(;p!=e;) {
      *p=__Op128<T,RunOp>(*p,__Op128<T,AType::OpName>(u,*(q++)));
      ++p;
    }
    return A;
  }
  template <typename T,template<typename,typename> class ArrayOp,
            __ExpressionOperationName RunOp>
  Array<Intrinsic<T>>&
  __two_level_op(
      Array<Intrinsic<T>>& A,
      const ArrayOp<Array<Intrinsic<T>>,Intrinsic<T>>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<Array<Intrinsic<T>>,Intrinsic<T>> AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 u=__ArrayWrapper<Intrinsic<T>>::set_from_unit(E.second());
    T128 *q=reinterpret_cast<T128*>(E.first().head());
    for(;p!=e;) {
      *p=__Op128<T,RunOp>(*p,__Op128<T,AType::OpName>(*(q++),u));
      ++p;
    }
    return A;
  }
  template <typename T,template<typename,typename> class ArrayOp,
            __ExpressionOperationName RunOp>
  Array<Intrinsic<T>>&
  __two_level_op(
      Array<Intrinsic<T>>& A,
      const ArrayOp<Array<Intrinsic<T>>,Array<Intrinsic<T>>>& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size()<=E.size());
    typedef typename __ArrayWrapper<Intrinsic<T>>::value128_type T128;
    typedef ArrayOp<Array<Intrinsic<T>>,Array<Intrinsic<T>>> AType;
    T128 *p=reinterpret_cast<T128*>(A.head());
    const T128 *e=p+A.size128();
    T128 *q=reinterpret_cast<T128*>(E.first().head());
    T128 *r=reinterpret_cast<T128*>(E.second().head());
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
    return __val_op<int,__ExpressionOperationName::Add>(*this,D);
  }
  template <>
  Array<Float>& Array<Float>::operator+=(const float& D) {
    return __val_op<float,__ExpressionOperationName::Add>(*this,D);
  }
  template <>
  Array<Double>& Array<Double>::operator+=(const double& D) {
    return __val_op<double,__ExpressionOperationName::Add>(*this,D);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator+=(const Array<Int>& A) {
    return __array_op<int,__ExpressionOperationName::Add>(*this,A);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(const Array<Float>& A) {
    return __array_op<float,__ExpressionOperationName::Add>(*this,A);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(const Array<Double>& A) {
    return __array_op<double,__ExpressionOperationName::Add>(*this,A);
  }

  template <>
  Array<Int>& Array<Int>::operator-=(const int& D) {
    return __val_op<int,__ExpressionOperationName::Substract>(*this,D);
  }
  template <>
  Array<Float>& Array<Float>::operator-=(const float& D) {
    return __val_op<float,__ExpressionOperationName::Substract>(*this,D);
  }
  template <>
  Array<Double>& Array<Double>::operator-=(const double& D) {
    return __val_op<double,__ExpressionOperationName::Substract>(*this,D);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator-=(const Array<Int>& A) {
    return __array_op<int,__ExpressionOperationName::Substract>(*this,A);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(const Array<Float>& A) {
    return __array_op<float,__ExpressionOperationName::Substract>(*this,A);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(const Array<Double>& A) {
    return __array_op<double,__ExpressionOperationName::Add>(*this,A);
  }

  template <>
  Array<Int>& Array<Int>::operator*=(const int& D) {
    return __val_op<int,__ExpressionOperationName::Multiple>(*this,D);
  }
  template <>
  Array<Float>& Array<Float>::operator*=(const float& D) {
    return __val_op<float,__ExpressionOperationName::Multiple>(*this,D);
  }
  template <>
  Array<Double>& Array<Double>::operator*=(const double& D) {
    return __val_op<double,__ExpressionOperationName::Multiple>(*this,D);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(const Array<Int>& A) {
    return __array_op<int,__ExpressionOperationName::Multiple>(*this,A);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(const Array<Float>& A) {
    return __array_op<float,__ExpressionOperationName::Multiple>(*this,A);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(const Array<Double>& A) {
    return __array_op<double,__ExpressionOperationName::Multiple>(*this,A);
  }

  template <>
  Array<Float>& Array<Float>::operator/=(const float& D) {
    return __val_op<float,__ExpressionOperationName::Divide>(*this,D);
  }
  template <>
  Array<Double>& Array<Double>::operator/=(const double& D) {
    return __val_op<double,__ExpressionOperationName::Divide>(*this,D);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(const Array<Float>& A) {
    return __array_op<float,__ExpressionOperationName::Divide>(*this,A);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(const Array<Double>& A) {
    return __array_op<double,__ExpressionOperationName::Divide>(*this,A);
  }

  // for too-short array, direct operation may be faster
  // for double, 16-mer is balance
  // for float,  2-mer is balance
  template <>
  template <>
  Array<Int>& Array<Int>::operator+=(const ArrayMul<Int,Array<Int>>& EA) {
    return __two_level_op<int,ArrayMul,__ExpressionOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayMul<Float,Array<Float>>& EA) {
    return __two_level_op<float,ArrayMul,__ExpressionOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayMul<Double,Array<Double>>& EA) {
    return __two_level_op<double,ArrayMul,__ExpressionOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator+=(
      const ArrayMul<Array<Int>,Int>& EA) {
    return __two_level_op<int,ArrayMul,__ExpressionOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayMul<Array<Float>,Float>& EA) {
    return __two_level_op<float,ArrayMul,__ExpressionOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayMul<Array<Double>,Double>& EA) {
    return __two_level_op<double,ArrayMul,__ExpressionOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator+=(
      const ArrayMul<Array<Int>,Array<Int>>& EA) {
    return __two_level_op<int,ArrayMul,__ExpressionOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayMul<Array<Float>,Array<Float>>& EA) {
    return __two_level_op<float,ArrayMul,__ExpressionOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayMul<Array<Double>,Array<Double>>& EA) {
    return __two_level_op<double,ArrayMul,__ExpressionOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayDiv<Float,Array<Float>>& EA) {
    return __two_level_op<float,ArrayDiv,__ExpressionOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayDiv<Double,Array<Double>>& EA) {
    return __two_level_op<double,ArrayDiv,__ExpressionOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayDiv<Array<Float>,Float>& EA) {
    return __two_level_op<float,ArrayDiv,__ExpressionOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayDiv<Array<Double>,Double>& EA) {
    return __two_level_op<double,ArrayDiv,__ExpressionOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator+=(
      const ArrayDiv<Array<Float>,Array<Float>>& EA) {
    return __two_level_op<float,ArrayDiv,__ExpressionOperationName::Add>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator+=(
      const ArrayDiv<Array<Double>,Array<Double>>& EA) {
    return __two_level_op<double,ArrayDiv,__ExpressionOperationName::Add>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator-=(
      const ArrayMul<Int,Array<Int>>& EA) {
    return
    __two_level_op<int,ArrayMul,__ExpressionOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayMul<Float,Array<Float>>& EA) {
    return
    __two_level_op<float,ArrayMul,__ExpressionOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayMul<Double,Array<Double>>& EA) {
    return
    __two_level_op<double,ArrayMul,__ExpressionOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator-=(
      const ArrayMul<Array<Int>,Int>& EA) {
    return
    __two_level_op<int,ArrayMul,__ExpressionOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayMul<Array<Float>,Float>& EA) {
    return
    __two_level_op<float,ArrayMul,__ExpressionOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayMul<Array<Double>,Double>& EA) {
    return
    __two_level_op<double,ArrayMul,__ExpressionOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator-=(
      const ArrayMul<Array<Int>,Array<Int>>& EA) {
    return
    __two_level_op<int,ArrayMul,__ExpressionOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayMul<Array<Float>,Array<Float>>& EA) {
    return
    __two_level_op<float,ArrayMul,__ExpressionOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayMul<Array<Double>,Array<Double>>& EA) {
    return
    __two_level_op<double,ArrayMul,__ExpressionOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayDiv<Float,Array<Float>>& EA) {
    return
    __two_level_op<float,ArrayDiv,__ExpressionOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayDiv<Double,Array<Double>>& EA) {
    return
    __two_level_op<double,ArrayDiv,__ExpressionOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayDiv<Array<Float>,Float>& EA) {
    return
    __two_level_op<float,ArrayDiv,__ExpressionOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayDiv<Array<Double>,Double>& EA) {
    return
    __two_level_op<double,ArrayDiv,__ExpressionOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator-=(
      const ArrayDiv<Array<Float>,Array<Float>>& EA) {
    return
    __two_level_op<float,ArrayDiv,__ExpressionOperationName::Substract>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator-=(
      const ArrayDiv<Array<Double>,Array<Double>>& EA) {
    return
    __two_level_op<double,ArrayDiv,__ExpressionOperationName::Substract>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArraySum<Int,Array<Int>>& EA) {
    return
    __two_level_op<int,ArraySum,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArraySum<Float,Array<Float>>& EA) {
    return
    __two_level_op<float,ArraySum,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArraySum<Double,Array<Double>>& EA) {
    return
    __two_level_op<double,ArraySum,__ExpressionOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArraySum<Array<Int>,Int>& EA) {
    return
    __two_level_op<int,ArraySum,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArraySum<Array<Float>,Float>& EA) {
    return
    __two_level_op<float,ArraySum,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArraySum<Array<Double>,Double>& EA) {
    return
    __two_level_op<double,ArraySum,__ExpressionOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArraySum<Array<Int>,Array<Int>>& EA) {
    return
    __two_level_op<int,ArraySum,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArraySum<Array<Float>,Array<Float>>& EA) {
    return
    __two_level_op<float,ArraySum,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArraySum<Array<Double>,Array<Double>>& EA) {
    return
    __two_level_op<double,ArraySum,__ExpressionOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArraySub<Int,Array<Int>>& EA) {
    return
    __two_level_op<int,ArraySub,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArraySub<Float,Array<Float>>& EA) {
    return
    __two_level_op<float,ArraySub,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArraySub<Double,Array<Double>>& EA) {
    return
    __two_level_op<double,ArraySub,__ExpressionOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArraySub<Array<Int>,Int>& EA) {
    return
    __two_level_op<int,ArraySub,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArraySub<Array<Float>,Float>& EA) {
    return
    __two_level_op<float,ArraySub,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArraySub<Array<Double>,Double>& EA) {
    return
    __two_level_op<double,ArraySub,__ExpressionOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Int>& Array<Int>::operator*=(
      const ArraySub<Array<Int>,Array<Int>>& EA) {
    return
    __two_level_op<int,ArraySub,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Float>& Array<Float>::operator*=(
      const ArraySub<Array<Float>,Array<Float>>& EA) {
    return
    __two_level_op<float,ArraySub,__ExpressionOperationName::Multiple>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator*=(
      const ArraySub<Array<Double>,Array<Double>>& EA) {
    return
    __two_level_op<double,ArraySub,__ExpressionOperationName::Multiple>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArraySum<Float,Array<Float>>& EA) {
    return
    __two_level_op<float,ArraySum,__ExpressionOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArraySum<Double,Array<Double>>& EA) {
    return
    __two_level_op<double,ArraySum,__ExpressionOperationName::Divide>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArraySum<Array<Float>,Float>& EA) {
    return
    __two_level_op<float,ArraySum,__ExpressionOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArraySum<Array<Double>,Double>& EA) {
    return
    __two_level_op<double,ArraySum,__ExpressionOperationName::Divide>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArraySum<Array<Float>,Array<Float>>& EA) {
    return
    __two_level_op<float,ArraySum,__ExpressionOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArraySum<Array<Double>,Array<Double>>& EA) {
    return
    __two_level_op<double,ArraySum,__ExpressionOperationName::Divide>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArraySub<Float,Array<Float>>& EA) {
    return
    __two_level_op<float,ArraySub,__ExpressionOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArraySub<Double,Array<Double>>& EA) {
    return
    __two_level_op<double,ArraySub,__ExpressionOperationName::Divide>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArraySub<Array<Float>,Float>& EA) {
    return
    __two_level_op<float,ArraySub,__ExpressionOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArraySub<Array<Double>,Double>& EA) {
    return
    __two_level_op<double,ArraySub,__ExpressionOperationName::Divide>(*this,EA);
  }

  template <>
  template <>
  Array<Float>& Array<Float>::operator/=(
      const ArraySub<Array<Float>,Array<Float>>& EA) {
    return
    __two_level_op<float,ArraySub,__ExpressionOperationName::Divide>(*this,EA);
  }
  template <>
  template <>
  Array<Double>& Array<Double>::operator/=(
      const ArraySub<Array<Double>,Array<Double>>& EA) {
    return
    __two_level_op<double,ArraySub,__ExpressionOperationName::Divide>(*this,EA);
  }

}

#endif

