
#ifndef _Array_ShortData_H_
#define _Array_ShortData_H_

#include "array/interface.h"
#include "array/expression.h"
#include "basic/type/same.h"
#include "basic/type/selector.h"
#include "basic/type/sum.h"
#include "basic/type/substract.h"
#include "basic/type/multiple.h"
#include "basic/type/divide.h"

#ifndef _HAVE_SSE4
#error "\nSSE4 is required for ShortData Array! Try -msse4 -D_HAVE_SSE4\n"
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

    private:

      unsigned int _n128;

    public:

      Array() : ParentTypeA(), ParentTypeB(), _n128(0U) {}
      Array(size_type size) : ParentTypeA(), ParentTypeB(size),
                              _n128((size*sizeof(value_type))>>4) {}
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
      void allocate(size_type size) {
        ParentTypeB::allocate(size);
        _n128=(size*sizeof(value_type))>>4;
      }

      template <typename E,typename ET>
      Type& operator=(const ArrayExpression<E,ET>& EA) {
        printf("------------G---------------\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]=EA[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator=(const ArrayExpression<E,ET>&& EA) {
        printf("------------E---------------\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]=EA[i];
        return *this;
      }
      Type& operator=(const ArrayExpression<Type,T>& EA) {
        printf("------------D---------------\n");
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        __m128i* p=reinterpret_cast<__m128i*>(this->head());
        __m128i* q=reinterpret_cast<__m128i*>(
                                    static_cast<const Type&>(EA).head());
        const __m128i* e=p+_n128;
        for(;p!=e;) _mm_store_si128(p++,*(q++));
        return *this;
      }

      Type& operator=(const Type& A) {
        printf("------------C---------------\n");
        return operator=(static_cast<const ParentTypeA&>(A));
      }
      Type& operator=(const value_type& D) {
        assert((bool)(*this));
        printf("------------A---------------\n");
        for(size_type i=0;i<size();++i) (*this)[i]=D;
        return *this;
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        printf("------------B---------------\n");
        return operator=((value_type)D);
      }

      //====----------==========-------------
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
      //====----------==========-------------

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
      //====----------==========-------------
      template <typename EA,typename EB>
      Type& operator+=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>&& A) {
        typedef ArraySub<EA,EB>   SType;
        operator+=(static_cast<SType const&>(A).first());
        return operator+=(static_cast<SType const&>(A).second());
      }
      template <typename EA,typename EB>
      Type& operator+=(
          const ArrayExpression<
                  ArraySum<EA,EB>,typename ArraySum<EA,EB>::value_type>& A) {
        typedef ArraySub<EA,EB>   SType;
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
      //====----------==========-------------

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
      Type& operator-=(const Intrinsic<T1>& D) {
        return operator-=((value_type)D);
      }
      //====----------==========-------------
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
      //====----------==========-------------

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
      //====----------==========-------------
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
      //====----------==========-------------

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
      //====----------==========-------------
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
      //====----------==========-------------
      template <typename T1,typename T2,
                template<typename,typename> class ArrayOp>
      Type& operator=(const ArrayOp<Intrinsic<T1>,Intrinsic<T2>>&& A) {
        return operator=(A.result());
      }
      template <typename T1,typename T2,
                template<typename,typename> class ArrayOp>
      Type& operator=(const ArrayOp<Intrinsic<T1>,Intrinsic<T2>>& A) {
        return operator=(A.result());
      }

  };

  typedef Array<Int,ArrayFormat::ShortData>     ItShortDataArray;
  typedef Array<Float,ArrayFormat::ShortData>   FtShortDataArray;
  typedef Array<Double,ArrayFormat::ShortData>  DbShortDataArray;

  template <>
  ItShortDataArray& ItShortDataArray::operator=(const int& D) {
    assert((bool)(*this));
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    const __m128i *e=p+_n128;
    __m128i u=_mm_set1_epi32(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;)   _mm_store_si128(p++,u);
    return *this;
  }
  template <>
  FtShortDataArray& FtShortDataArray::operator=(const float& D) {
    assert((bool)(*this));
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    const __m128 *e=p+_n128;
    __m128 u=_mm_set1_ps(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;)   *(p++)=u;
    return *this;
  }
  template <>
  DbShortDataArray& DbShortDataArray::operator=(const double& D) {
    printf("------------Z---------------\n");
    assert((bool)(*this));
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    __m128d u=_mm_set1_pd(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;)   *(p++)=u;
    return *this;
  }

  template <>
  ItShortDataArray& ItShortDataArray::operator+=(const int& D) {
    assert((bool)(*this));
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    const __m128i *e=p+_n128;
    __m128i u=_mm_set1_epi32(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;)  { *p=_mm_add_epi32(*p,u); ++p; }
    return *this;
  }
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(const float& D) {
    assert((bool)(*this));
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    const __m128 *e=p+_n128;
    __m128 u=_mm_set1_ps(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;)  { *p=_mm_add_ps(*p,u);  ++p; }
    return *this;
  }
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(const double& D) {
    assert((bool)(*this));
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    __m128d u=_mm_set1_pd(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;)  { *p=_mm_add_pd(*p,u); ++p; }
    return *this;
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator+=(
      const ArrayExpression<ItShortDataArray,int>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(size()<=A.size());
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    __m128i *q=reinterpret_cast<__m128i*>(((ItShortDataArray const&)A).head());
    const __m128i *e=p+_n128;
    for(;p!=e;)   { *p=_mm_add_epi32(*p,*(q++));  ++p; }
    return *this;
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<FtShortDataArray,float>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(size()<=A.size());
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    __m128 *q=reinterpret_cast<__m128*>(((FtShortDataArray const&)A).head());
    const __m128 *e=p+_n128;
    for(;p!=e;)   { *p=_mm_add_ps(*p,*(q++));  ++p; }
    return *this;
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<DbShortDataArray,double>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(size()<=A.size());
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    __m128d *q=reinterpret_cast<__m128d*>(((DbShortDataArray const&)A).head());
    const __m128d *e=p+_n128;
    for(;p!=e;)   { *p=_mm_add_pd(*p,*(q++));  ++p; }
    return *this;
  }

  template <>
  ItShortDataArray& ItShortDataArray::operator-=(const int& D) {
    assert((bool)(*this));
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    const __m128i *e=p+_n128;
    __m128i u=_mm_set1_epi32(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;) { *p=_mm_sub_epi32(*p,u); ++p; }
    return *this;
  }
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(const float& D) {
    assert((bool)(*this));
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    const __m128 *e=p+_n128;
    __m128 u=_mm_set1_ps(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;)  { *p=_mm_sub_ps(*p,u);  ++p; }
    return *this;
  }
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(const double& D) {
    assert((bool)(*this));
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    __m128d u=_mm_set1_pd(D);
    assert((((int)(&u))&0xFU)==0);
    for(;p!=e;)  { *p=_mm_sub_pd(*p,u); ++p; }
    return *this;
  }
  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator-=(
      const ArrayExpression<ItShortDataArray,int>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(size()<=A.size());
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    __m128i *q=reinterpret_cast<__m128i*>(((ItShortDataArray const&)A).head());
    const __m128i *e=p+_n128;
    for(;p!=e;)   { *p=_mm_sub_epi32(*p,*(q++));  ++p; }
    return *this;
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator-=(
      const ArrayExpression<FtShortDataArray,float>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(size()<=A.size());
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    __m128 *q=reinterpret_cast<__m128*>(((FtShortDataArray const&)A).head());
    const __m128 *e=p+_n128;
    for(;p!=e;)   { *p=_mm_sub_ps(*p,*(q++));  ++p; }
    return *this;
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator-=(
      const ArrayExpression<DbShortDataArray,double>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(size()<=A.size());
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    __m128d *q=reinterpret_cast<__m128d*>(((DbShortDataArray const&)A).head());
    const __m128d *e=p+_n128;
    for(;p!=e;)   { *p=_mm_sub_pd(*p,*(q++));  ++p; }
    return *this;
  }

  /*
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(const int& D) {
    assert((bool)(*this));
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    const __m128i *e=p+_n128;
    __m128i u=_mm_set1_epi32(D);
    for(;p!=e;)  { *p=_mm_mullo_epi32(*p,u); ++p; }
    return *this;
  }
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(const float& D) {
    assert((bool)(*this));
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    const __m128 *e=p+_n128;
    __m128 u=_mm_set1_ps(D);
    for(;p!=e;)  { *p=_mm_mul_ps(*p,u); ++p; }
    return *this;
  }
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(const double& D) {
    assert((bool)(*this));
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    __m128d u=_mm_set1_pd(D);
    for(;p!=e;)  { *p=_mm_mul_pd(*p,u); ++p; }
    return *this;
  }

  template <>
  FtShortDataArray& FtShortDataArray::operator/=(const float& D) {
    assert((bool)(*this));
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    const __m128 *e=p+_n128;
    __m128 u=_mm_set1_ps(D);
    for(;p!=e;)  { *p=_mm_div_ps(*p,u); ++p; }
    return *this;
  }
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(const double& D) {
    assert((bool)(*this));
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    __m128d u=_mm_set1_pd(D);
    for(;p!=e;)  { *p=_mm_div_pd(*p,u); ++p; }
    return *this;
  }


  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator*=(
      const ArrayExpression<ItShortDataArray,int>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(size()<=A.size());
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    __m128i *q=reinterpret_cast<__m128i*>(((ItShortDataArray const&)A).head());
    const __m128i *e=p+_n128;
    for(;p!=e;)   { *p=_mm_mullo_epi32(*p,*(q++));  ++p; }
    return *this;
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator*=(
      const ArrayExpression<FtShortDataArray,float>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(size()<=A.size());
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    __m128 *q=reinterpret_cast<__m128*>(((FtShortDataArray const&)A).head());
    const __m128 *e=p+_n128;
    for(;p!=e;)   { *p=_mm_mul_ps(*p,*(q++));  ++p; }
    return *this;
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator*=(
      const ArrayExpression<DbShortDataArray,double>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(size()<=A.size());
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    __m128d *q=reinterpret_cast<__m128d*>(((DbShortDataArray const&)A).head());
    const __m128d *e=p+_n128;
    for(;p!=e;)   { *p=_mm_mul_pd(*p,*(q++));  ++p; }
    return *this;
  }

  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator/=(
      const ArrayExpression<FtShortDataArray,float>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(size()<=A.size());
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    __m128 *q=reinterpret_cast<__m128*>(((FtShortDataArray const&)A).head());
    const __m128 *e=p+_n128;
    for(;p!=e;)   { *p=_mm_div_ps(*p,*(q++));  ++p; }
    return *this;
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator/=(
      const ArrayExpression<DbShortDataArray,double>& A) {
    assert((bool)(*this));
    assert((bool)A);
    assert(size()<=A.size());
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    __m128d *q=reinterpret_cast<__m128d*>(((DbShortDataArray const&)A).head());
    const __m128d *e=p+_n128;
    for(;p!=e;)   { *p=_mm_div_pd(*p,*(q++));  ++p; }
    return *this;
  }

  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator=(
      const ArrayExpression<ArraySum<ItShortDataArray,ItShortDataArray>,
                            int>&& EA) {
    typedef ArraySum<ItShortDataArray,ItShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    __m128i *q=reinterpret_cast<__m128i*>(
                                static_cast<const SType&>(EA).first());
    __m128i *r=reinterpret_cast<__m128i*>(
                                static_cast<const SType&>(EA).second());
    const __m128i *e=p+_n128;
    for(;p!=e;) *(p++)=_mm_add_epi32(*(q++),*(r++));
    return *this;
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator=(
      const ArrayExpression<ArraySum<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    typedef ArraySum<FtShortDataArray,FtShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    __m128 *q=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).first());
    __m128 *r=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).second());
    const __m128 *e=p+_n128;
    for(;p!=e;) *(p++)=_mm_add_ps(*(q++),*(r++));
    return *this;
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator=(
      const ArrayExpression<ArraySum<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    typedef ArraySum<DbShortDataArray,DbShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    __m128d *q=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).first());
    __m128d *r=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).second());
    for(;p!=e;) *(p++)=_mm_add_pd(*(q++),*(r++));
    return *this;
  }

  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator=(
      const ArrayExpression<ArraySub<ItShortDataArray,ItShortDataArray>,
                            int>&& EA) {
    typedef ArraySub<ItShortDataArray,ItShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    const __m128i *e=p+_n128;
    __m128i *q=reinterpret_cast<__m128i*>(
                                static_cast<const SType&>(EA).first());
    __m128i *r=reinterpret_cast<__m128i*>(
                                static_cast<const SType&>(EA).second());
    for(;p!=e;) *(p++)=_mm_sub_epi32(*(q++),*(r++));
    return *this;
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator=(
      const ArrayExpression<ArraySub<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    typedef ArraySub<FtShortDataArray,FtShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    const __m128 *e=p+_n128;
    __m128 *q=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).first());
    __m128 *r=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).second());
    for(;p!=e;) *(p++)=_mm_sub_ps(*(q++),*(r++));
    return *this;
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator=(
      const ArrayExpression<ArraySub<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    typedef ArraySub<DbShortDataArray,DbShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    __m128d *q=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).first());
    __m128d *r=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).second());
    for(;p!=e;) *(p++)=_mm_sub_pd(*(q++),*(r++));
    return *this;
  }

  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator=(
      const ArrayExpression<ArrayMul<ItShortDataArray,ItShortDataArray>,
                            int>&& EA) {
    typedef ArrayMul<ItShortDataArray,ItShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    const __m128i *e=p+_n128;
    __m128i *q=reinterpret_cast<__m128i*>(
                                static_cast<const SType&>(EA).first());
    __m128i *r=reinterpret_cast<__m128i*>(
                                static_cast<const SType&>(EA).second());
    for(;p!=e;) *(p++)=_mm_mullo_epi32(*(q++),*(r++));
    return *this;
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator=(
      const ArrayExpression<ArrayMul<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    typedef ArrayMul<FtShortDataArray,FtShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    const __m128 *e=p+_n128;
    __m128 *q=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).first());
    __m128 *r=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).second());
    for(;p!=e;) *(p++)=_mm_mul_ps(*(q++),*(r++));
    return *this;
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator=(
      const ArrayExpression<ArrayMul<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    typedef ArrayMul<DbShortDataArray,DbShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    __m128d *q=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).first());
    __m128d *r=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).second());
    for(;p!=e;) *(p++)=_mm_mul_pd(*(q++),*(r++));
    return *this;
  }

  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator=(
      const ArrayExpression<ArrayDiv<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    typedef ArrayDiv<FtShortDataArray,FtShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    const __m128 *e=p+_n128;
    __m128 *q=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).first());
    __m128 *r=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).second());
    for(;p!=e;) *(p++)=_mm_div_ps(*(q++),*(r++));
    return *this;
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator=(
      const ArrayExpression<ArrayDiv<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    typedef ArrayDiv<DbShortDataArray,DbShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    __m128d *q=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).first());
    __m128d *r=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).second());
    for(;p!=e;) *(p++)=_mm_div_pd(*(q++),*(r++));
    return *this;
  }
  /////////-------------

  template <>
  template <>
  ItShortDataArray& ItShortDataArray::operator+=(
      const ArrayExpression<ArraySum<ItShortDataArray,ItShortDataArray>,
                            int>&& EA) {
    typedef ArraySum<ItShortDataArray,ItShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    __m128i *q=reinterpret_cast<__m128i*>(
                                static_cast<const SType&>(EA).first());
    __m128i *r=reinterpret_cast<__m128i*>(
                                static_cast<const SType&>(EA).second());
    const __m128i *e=p+_n128;
    __m128i u;
    for(;p!=e;) { u=_mm_add_epi32(*(q++),*(r++)); *p=_mm_add_epi32(*p,u); ++p; }
    return *this;
  }
  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator+=(
      const ArrayExpression<ArraySum<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    typedef ArraySum<FtShortDataArray,FtShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    __m128 *q=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).first());
    __m128 *r=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).second());
    const __m128 *e=p+_n128;
    __m128 u;
    for(;p!=e;) { u=_mm_add_ps(*(q++),*(r++)); *p=_mm_add_ps(*p,u); p++; }
    return *this;
  }
  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator+=(
      const ArrayExpression<ArraySum<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    typedef ArraySum<DbShortDataArray,DbShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    __m128d *q=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).first());
    __m128d *r=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).second());
    for(;p!=e;) { *p=_mm_add_pd(*p,_mm_add_pd(*(q++),*(r++))); ++p; }
    return *this;
  }
  */

}

#endif

