
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

      Array() : ParentType() {}
      Array(size_type size) : ParentType(size) {}
      Array(const Type& A) : Array() { ParentType::imprint(A); operator=(A); }
      Array(Type&& A) : ParentType((ParentType&&)A) {}
      ~Array() { ParentType::reset(); }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]=A[i];
        return *this;
      }
      Type& operator=(const monomer_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]=D;
        return *this;
      }
      Type& operator=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]=D;
        return *this;
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((value_type)((T1)D));
      }

  };

  template <typename T>
  class Array<T,false> : public ArrayContainer<T> {

    public:

      typedef Array<T,false>   Type;
      typedef ArrayContainer<T>       ParentType;
      typedef typename ParentType::monomer_type  monomer_type;
      typedef unsigned int size_type;

      Array() : ParentType() {}
      Array(size_type size) : ParentType(size) {}
      Array(const Type& A) : Array(A.size()) { operator=(A); }
      Array(Type&& A) : ParentType((ParentType&&)A) {}
      ~Array() { ParentType::reset(); }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]=A[i];
        return *this;
      }
      Type& operator=(const monomer_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]=D;
        return *this;
      }

  };

}

#ifndef __SSE4_1__
#error "\nSSE4.1 is required for Array of intrinsic data! Try -msse4.1 !\n"
#endif

#include "basic/type/same.h"
#include "basic/square-root.h"
#include "array/expression-operation.h"
#include <emmintrin.h>
#include <smmintrin.h>

namespace mysimulator {

  template <typename T>
  class Array<Intrinsic<T>,true> : public ArrayContainer<Intrinsic<T>> {

    public:

      typedef Array<Intrinsic<T>,true>           Type;
      typedef ArrayContainer<Intrinsic<T>>  ParentType;
      typedef typename ParentType::monomer_type  monomer_type;
      typedef T  value_type;
      typedef unsigned int size_type;

      Array() : ParentType() {}
      Array(size_type size) : ParentType(size) {}
      Array(const Type& A) : Array(A.size()) { operator=(A); }
      Array(Type&& A) : ParentType((ParentType&&)A) {}
      ~Array() { ParentType::reset(); }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        __m128i* p=reinterpret_cast<__m128i*>(this->head());
        __m128i* q=reinterpret_cast<__m128i*>(A.head());
        const __m128i* e=p+this->size128();
        for(;p!=e;) _mm_store_si128(p++,*(q++));
        return *this;
      }
      template <typename ET>
      Type& operator=(Array<ET> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i) (*this)[i]=A[i];
        return *this;
      }
      Type& operator=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<ParentType::size();++i) (*this)[i]=D;
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
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]+=A[i];
        return *this;
      }
      Type& operator+=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]+=D;
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
        assert(ParentType::size()<=RA.size());
        for(size_type i=0;i<ParentType::size();++i) (*this)[i]+=RA[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator+=(ArrayDiv<EA,EB> const& RA) {
        assert((bool)(*this));
        assert((bool)RA);
        assert(ParentType::size()<=RA.size());
        for(size_type i=0;i<ParentType::size();++i) (*this)[i]+=RA[i];
        return *this;
      }

      template <typename ET>
      Type& operator-=(const Array<ET>& A) {
        static_assert(
            __same_type<T,typename __dual_selector<T,ET,__sub_flag>::Type>::FG,
            "Type T cannot accept SUBSTRACT result!\n");
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]=A[i];
        return *this;
      }
      Type& operator-=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]-=D;
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
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i) (*this)[i]-=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator-=(ArrayDiv<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i) (*this)[i]-=A[i];
        return *this;
      }

      template <typename ET>
      Type& operator*=(const Array<ET>& A) {
        static_assert(
            __same_type<T,typename __dual_selector<T,ET,__mul_flag>::Type>::FG,
            "Type T cannot accept MULTIPLE result!\n");
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]*=A[i];
        return *this;
      }
      Type& operator*=(const value_type& D) {
        assert((bool)(*this));
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]*=D;
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
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]*=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator*=(ArraySub<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]*=A[i];
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
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]/=A[i];
        return *this;
      }
      Type& operator/=(const value_type& D) {
        static_assert(Intrinsic<T>::IsFloatPoint,
                      "Divide only works for float-point data!\n");
        assert((bool)(*this));
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]/=D;
      }
      template <typename T1>
      Type& operator/=(const Intrinsic<T1>& D) {
        return operator/=((value_type)((T1)D));
      }

      template <typename EA,typename EB>
      Type& operator/=(ArraySum<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]/=A[i];
        return *this;
      }
      template <typename EA,typename EB>
      Type& operator/=(ArraySub<EA,EB> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i)   (*this)[i]/=A[i];
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

      T NormSQ() const { return Dot(*this,*this); }

      T Norm() const {
        static_assert(
            Intrinsic<T>::IsFloatPoint,
            "Norm is related to SQRT. Only works for float-point data!\n");
        return __SquareRoot(NormSQ());
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

  template <typename T1,typename T2>
  typename __dual_selector<T1,T2,__mul_flag>::Type
  Dot(Array<Intrinsic<T1>> const& A,Array<Intrinsic<T2>> const& B) {
    assert((bool)A);
    assert((bool)B);
    typename __dual_selector<T1,T2,__mul_flag>::Type S=0;
    unsigned int n=(A.size()<=B.size()?A.size():B.size());
    for(unsigned int i=0;i<n;++i) S+=A[i]*B[i];
    return S;
  }

  template <>
  double
  Dot(Array<Double> const& A, Array<Double> const& B) {
    assert((bool)A);
    assert((bool)B);
    unsigned int n=(A.size128()<B.size128()?A.size128():B.size128());
    __m128d *p=(__m128d*)(A.head());
    __m128d *q=(__m128d*)(B.head());
    const __m128d *e=p+n;
    double T,S=0;
    for(;p!=e;)  { _mm_store_sd(&T,_mm_dp_pd(*(p++),*(q++),0x31)); S+=T; }
    return S;
  }

  template <>
  float
  Dot(Array<Float> const& A, Array<Float> const& B) {
    assert((bool)A);
    assert((bool)B);
    unsigned int n=(A.size128()<B.size128()?A.size128():B.size128());
    __m128 *p=(__m128*)(A.head());
    __m128 *q=(__m128*)(B.head());
    const __m128 *e=p+n;
    float T,S=0;
    for(;p!=e;)  { _mm_store_ss(&T,_mm_dp_ps(*(p++),*(q++),0xF1)); S+=T; }
    return S;
  }

  template <>
  class Array<Unique,false> : public ArrayContainer<Unique> {

    public:

      typedef Array<Unique,false>    Type;
      typedef ArrayContainer<Unique>  ParentType;
      typedef typename ParentType::monomer_type  monomer_type;
      typedef Unique value_type;
      typedef unsigned int size_type;

      Array() : ParentType() {}
      Array(size_type size) : ParentType(size) {}
      Array(const Type& A) : Array() { ParentType::imprint(A); operator=(A); }
      Array(Type&& A) : ParentType((ParentType&&)A) {}
      ~Array() { ParentType::reset(); }

      Type& operator=(const Type& A) {
        return _copy_array_128<monomer_type>(A);
      }
      Type& operator=(const Array<Double>& A) {
        return _copy_array_128<Double>(A);
      }
      template <typename T>
      Type& operator=(const Intrinsic<T>& D) { return operator=((T)D); }
      template <typename T>
      Type& operator=(const Array<Intrinsic<T>>& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        for(size_type i=0;i<ParentType::size();++i) (*this)[i]=A[i];
        return *this;
      }

    private:

      template <typename T>
      Type& operator=(const T& D) {
        assert((bool)(*this));
        __m128d *p=(__m128d*)(this->head());
        const __m128d* e=p+this->size128();
        Unique U;
        (T&)U=D;
        __m128d u=_mm_set1_pd((double)U);
        assert((((int)(&u))&0xFU)==0);
        for(;p!=e;)   *(p++)=u;
        return *this;
      }
      template <typename T>
      Type& _copy_array_128(Array<T> const& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(ParentType::size()<=A.size());
        __m128d *p=(__m128d*)(this->head());
        __m128d *q=(__m128d*)(A.head());
        const __m128d *e=p+this->size128();
        for(;p!=e;) *(p++)=*(q++);
        return *this;
      }

  };

}

#endif

