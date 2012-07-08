
#ifndef _Array_Numeric_Interface_H_
#define _Array_Numeric_Interface_H_

#include "array/interface.h"
#include "basic/sum.h"
#include "basic/abs-sum.h"
#include "basic/norm-square.h"
#include "basic/scale.h"
#include "basic/shift.h"
#include "basic/inverse.h"
#include "basic/square-root.h"
#include "basic/dot.h"
#include "type/combine.h"
#include "type/blas-size.h"
#include "type/is-blas.h"
#include "type/is-blas-size.h"
#include "type/is-numeric-object.h"
#include "linear-algebra/blas.h"

namespace mysimulator {

  template<typename T> class ArrayNumeric;
  template<typename T> T BlasDot(const ArrayNumeric<T>&,const ArrayNumeric<T>&);

  template <typename T>
  class ArrayNumeric : public Array<T> {

    public:

      typedef ArrayNumeric<T>   Type;
      typedef Array<T>      ParentType;
      typedef typename IsNumericObject<Type>::Type NumericCheck;
      friend T BlasDot<T>(const ArrayNumeric<T>&,const ArrayNumeric<T>&);
      template <typename T1> friend class ArrayNumeric;

      ArrayNumeric() : ParentType() {}
      ~ArrayNumeric() { Clear(*this); }

      typename DataType<Type>::Type Summation() const {
        typedef typename IsNumericObject<ArrayNumeric<T> >::Type   SumCheck;
        assert(this->IsValid());
        typename DataType<Type>::Type sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;) sum+=_Sum(*(p++));
        return sum;
      }
      typename DataType<Type>::Type AbsSummation() const {
        typedef typename IsNumericObject<ArrayNumeric<T> >::Type   SumCheck;
        assert(this->IsValid());
        typename DataType<Type>::Type sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;) sum+=_AbsSum(*(p++));
        return sum;
      }

      typename DataType<Type>::Type NormSQ() const {
        typedef typename IsNumericObject<ArrayNumeric<T> >::Type NormSQCheck;
        typename DataType<Type>::Type sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  sum+=_NormSQ(*(p++));
        return sum;
      }

      typename DataType<Type>::Type Norm() const {
        typedef
        typename IsFloatPoint<typename DataType<ArrayNumeric<T> >::Type>::Type
        NormCheck;
        return __SqRoot(NormSQ());
      }

      template <typename T1>
      void Scale(const T1& fac) {
        assert(this->IsValid());
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  _Scale(*(p++),fac);
      }
      template <typename T1>
      void Scale(const ArrayNumeric<T1>& fac) {
        assert(this->IsValid());
        assert(fac.IsValid());
        assert(this->Size()==fac.Size());
        T *p=this->Head(), *pEnd=p+this->Size();
        T1 *q=fac.Head();
        for(;p!=pEnd;)  _Scale(*(p++),*(q++));
      }

      template <typename T1>
      void Shift(const T1& fac) {
        assert(this->IsValid());
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  _Shift(*(p++),fac);
      }
      template <typename T1>
      void Shift(const ArrayNumeric<T1>& fac) {
        assert(this->IsValid());
        assert(fac.IsValid());
        assert(this->Size()==fac.Size());
        T *p=this->Head(), *pEnd=p+this->Size();
        T1 *q=fac.Head();
        for(;p!=pEnd;)  _Shift(*(p++),*(q++));
      }

      template <typename T1>
      void NegShift(const T1& fac) {
        assert(this->IsValid());
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  _NegShift(*(p++),fac);
      }
      template <typename T1>
      void NegShift(const ArrayNumeric<T1>& fac) {
        assert(this->IsValid());
        assert(fac.IsValid());
        assert(this->Size()==fac.Size());
        T *p=this->Head(), *pEnd=p+this->Size();
        T1 *q=fac.Head();
        for(;p!=pEnd;)  _NegShift(*(p++),*(q++));
      }

      template <typename T1,typename T2>
      void Shift(const ArrayNumeric<T1>& A,const T2& d) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(this->Size()==A.Size());
        T *p=this->Head(), *pEnd=p+this->Size();
        T1 *q=A.Head();
        for(;p!=pEnd;)  _Shift(*(p++),*(q++),d);
      }
      template <typename T1,typename T2>
      void Shift(const T1& d,const ArrayNumeric<T2>& A) { Shift(A,d); }

      template <typename T1,typename T2>
      void Shift(const ArrayNumeric<T1>& A, const ArrayNumeric<T2>& B) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(B.IsValid());
        assert(this->Size()==A.Size());
        assert(this->Size()==B.Size());
        T *p=this->Head(), *pEnd=p+this->Size();
        T1 *q=A.Head();
        T2 *r=B.Head();
        for(;p!=pEnd;)  _Shift(*(p++),*(q++),*(r++));
      }

      template <typename T1,typename T2,typename T3>
      void Shift(const T1& d,
                 const ArrayNumeric<T2>& A,const ArrayNumeric<T3>& B) {
        assert(this->IsValid());
        assert(A.IsValid());
        assert(B.IsValid());
        assert(this->Size()==A.Size());
        assert(this->Size()==B.Size());
        T *p=this->Head(), *pEnd=p+this->Size();
        T2 *q=A.Head();
        T3 *r=B.Head();
        for(;p!=pEnd;)  _Shift(*(p++),d,*(q++),*(r++));
      }

      void BlasCopy(const Type& A) {
        typedef typename IsBlasSize<T>::Type  BLASSizeCheck;
        typedef typename BlasSize<T>::Type  RunType;
        assert(this->IsValid());
        assert(A.IsValid());
        assert(this->Size()==A.Size());
        long m=this->Size(), one=1;
        RunType *p=reinterpret_cast<RunType*>(A.Head());
        RunType *q=reinterpret_cast<RunType*>(this->Head());
        BLAS<RunType>::Copy(&m,p,&one,q,&one);
      }
      void BlasFill(const T& d) {
        typedef typename IsBlasSize<T>::Type  BLASSizeCheck;
        typedef typename BlasSize<T>::Type  RunType;
        assert(this->IsValid());
        long m=this->Size(), one=1, zero=0;
        RunType *p=reinterpret_cast<RunType*>(const_cast<T*>(&d));
        RunType *q=reinterpret_cast<RunType*>(this->Head());
        BLAS<RunType>::Copy(&m,p,&zero,q,&one);
      }

      template <typename T1>
      void BlasScale(const T1& d) {
        typedef typename IsBlasable<T>::Type    BlasCheck;
        typedef typename IsIncluded<T,T1>::Type TypeCheck;
        assert(this->IsValid());
        T v=d;
        long m=this->Size(), one=1;
        BLAS<T>::Scale(&m,&v,this->Head(),&one);
      }
      void BlasScale(const ArrayNumeric<T>& A) {
        typedef typename IsBlasable<T>::Type    BlasCheck;
        assert(this->IsValid());
        assert(A.IsValid());
        assert(this->Size()==A.Size());
        long m=this->Size(), one=1, zero=0;
        static char F[]="LNN";
        BLAS<T>::TbMv(F,F+1,F+2,&m,&zero,A.Head(),&one,this->Head(),&one);
      }
      template <typename T1>
      void BlasShift(const T1& d) {
        typedef typename IsBlasable<T>::Type    BlasCheck;
        typedef typename IsIncluded<T,T1>::Type TypeCheck;
        assert(this->IsValid());
        T v=d, vone=1.;
        long m=this->Size(), one=1, zero=0;
        BLAS<T>::Shift(&m,&vone,&v,&zero,this->Head(),&one);
      }
      template <typename T1>
      void BlasShift(const T1& d,const ArrayNumeric<T>& A) {
        typedef typename IsBlasable<T>::Type    BlasCheck;
        typedef typename IsIncluded<T,T1>::Type TypeCheck;
        assert(this->IsValid());
        assert(A.IsValid());
        assert(this->Size()==A.Size());
        T v=d;
        long m=this->Size(), one=1;
        BLAS<T>::Shift(&m,&v,A.Head(),&one,this->Head(),&one);
      }
      template <typename T1>
      void BlasShift(const ArrayNumeric<T>& A,const T1& d) { BlasShift(d,A); }
      void BlasShift(const ArrayNumeric<T>& A) { BlasShift(1.,A); }
      template <typename T1>
      void BlasShift(const T1& d,const ArrayNumeric<T>& A,
                     const ArrayNumeric<T>& B) {
        typedef typename IsBlasable<T>::Type    BlasCheck;
        typedef typename IsIncluded<T,T1>::Type TypeCheck;
        assert(this->IsValid());
        assert(A.IsValid());
        assert(B.IsValid());
        assert(this->Size()==A.Size());
        assert(this->Size()==B.Size());
        T v=d, vone=1.;
        static char F[]="L";
        long m=this->Size(), one=1, zero=0;
        BLAS<T>::SbMv(F,&m,&zero,&v,A.Head(),&one,B.Head(),&one,&vone,
                      this->Head(),&one);
      }
      void BlasShift(const ArrayNumeric<T>& A,const ArrayNumeric<T>& B) {
        BlasShift(1.,A,B);
      }
      T BlasNormSQ() const {
        typedef typename IsBlasable<T>::Type    BlasCheck;
        return BlasDot(*this,*this);
      }
      T BlasNorm() const {
        typedef typename IsBlasable<T>::Type    BlasCheck;
        long m=this->Size(), one=1;
        return BLAS<T>::Norm(&m,this->Head(),&one);
      }
      T BlasAbsSum() const {
        typedef typename IsBlasable<T>::Type    BlasCheck;
        long m=this->Size(), one=1;
        return BLAS<T>::ASum(&m,this->Head(),&one);
      }

      void Inverse() {
        typedef typename IsFloatPoint<typename DataType<T>::Type>::Type
                FloatPointCheck;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  _Inverse(*(p++));
      }
      void SqRoot() {
        typedef typename IsFloatPoint<typename DataType<T>::Type>::Type
                FloatPointCheck;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  _SqRoot(*(p++));
      }
      template <typename T1>
      typename CombineType<typename DataType<T>::Type,
                           typename DataType<T1>::Type>::Type
      __DotN(const ArrayNumeric<T1>& A,unsigned int n) const {
        typedef typename IsNumericObject<ArrayNumeric<T> >::Type  DotCheck;
        typedef typename IsNumericObject<ArrayNumeric<T1> >::Type DotCheck1;
        assert(this->IsValid());
        assert(A.IsValid());
        assert(this->Size()>=n);
        assert(A.Size()>=n);
        typename CombineType<typename DataType<T>::Type,
                             typename DataType<T1>::Type>::Type sum=0;
        T *p=this->Head(), *pEnd=p+n;
        T1 *q=A.Head();
        for(;p!=pEnd;)  sum+=_Dot(*(p++),*(q++));
        return sum;
      }

    private:

      ArrayNumeric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(ArrayNumeric<T>& A) { Clear(static_cast<Array<T>&>(A)); }

  template <typename T>
  bool IsSame(const ArrayNumeric<T>& A, const ArrayNumeric<T>& B) {
    typedef typename ArrayNumeric<T>::ParentType PType;
    return IsSame(static_cast<const PType&>(A),static_cast<const PType&>(B));
  }

  template <typename T1, typename T2>
  void _Copy(ArrayNumeric<T1>& A1,const ArrayNumeric<T2>& A2) { A1.Copy(A2); }

  template <typename T1, typename T2>
  void _Fill(ArrayNumeric<T1>& A, const T2& fac) { A.Fill(fac); }

  template <typename T>
  void _Imprint(ArrayNumeric<T>& A, const ArrayNumeric<T>& B) { A.Imprint(B); }

  template <typename T>
  void _SwapContent(ArrayNumeric<T>& A, ArrayNumeric<T>& B) {
    _SwapContent(static_cast<Array<T>&>(A),static_cast<Array<T>&>(B));
  }

  template <typename T>
  typename DataType<ArrayNumeric<T> >::Type _Sum(const ArrayNumeric<T>& A) {
    return A.Summation();
  }

  template <typename T>
  typename DataType<ArrayNumeric<T> >::Type _AbsSum(const ArrayNumeric<T>& A) {
    return A.AbsSummation();
  }

  template <typename T>
  typename DataType<ArrayNumeric<T> >::Type _NormSQ(const ArrayNumeric<T>& A) {
    return A.NormSQ();
  }

  template <typename T, typename T1>
  void _Scale(ArrayNumeric<T>& A, const T1& fac) { A.Scale(fac); }

  template <typename T, typename T1>
  void _Shift(ArrayNumeric<T>& A, const T1& fac) { A.Shift(fac); }

  template <typename T, typename T1>
  void _NegShift(ArrayNumeric<T>& A,const T1& fac) { A.NegShift(fac); }

  template <typename T,typename T1,typename T2>
  void _Shift(ArrayNumeric<T>& A,const ArrayNumeric<T1>& B,const T2& d) {
    A.Shift(B,d);
  }

  template <typename T,typename T1,typename T2>
  void _Shift(ArrayNumeric<T>& A,const T1& d,const ArrayNumeric<T2>& B) {
    A.Shift(d,B);
  }

  template <typename T,typename T1,typename T2,typename T3>
  void _Shift(ArrayNumeric<T>& A,const T1& d,const ArrayNumeric<T2>& B,
              const ArrayNumeric<T3>& C) {
    A.Shift(d,B,C);
  }

  template <>
  void ArrayNumeric<long double>::BlasCopy(const ArrayNumeric<long double>& A) {
    assert(this->IsValid());
    assert(A.IsValid());
    assert(this->Size()==A.Size());
    assert(sizeof(long double)==3*sizeof(float));
    long m=this->Size(), three=3;
    float *p=reinterpret_cast<float*>(A.Head());
    float *q=reinterpret_cast<float*>(this->Head());
    BLAS<float>::Copy(&m,p,  &three,q,  &three);
    BLAS<float>::Copy(&m,p+1,&three,q+1,&three);
    BLAS<float>::Copy(&m,p+2,&three,q+2,&three);
  }

  template <>
  void ArrayNumeric<long double>::BlasFill(const long double& d) {
    assert(this->IsValid());
    assert(sizeof(long double)==3*sizeof(float));
    long m=this->Size(), three=3, zero=0;
    float *p=reinterpret_cast<float*>(const_cast<long double*>(&d));
    float *q=reinterpret_cast<float*>(this->Head());
    BLAS<float>::Copy(&m,p,  &zero,q,  &three);
    BLAS<float>::Copy(&m,p+1,&zero,q,  &three);
    BLAS<float>::Copy(&m,p+2,&zero,q,  &three);
  }

  template <typename T>
  void _Inverse(ArrayNumeric<T>& A) { A.Inverse(); }

  template <typename T>
  void _SqRoot(ArrayNumeric<T>& A) { A.SqRoot(); }

  template <typename T1,typename T2>
  typename CombineType<typename DataType<T1>::Type,
                       typename DataType<T2>::Type>::Type
  _DotN(const ArrayNumeric<T1>& A, const ArrayNumeric<T2>& B, unsigned int n) {
    return A.__DotN(B,n);
  }

  template <typename T1,typename T2>
  typename CombineType<typename DataType<T1>::Type,
                       typename DataType<T2>::Type>::Type
  _Dot(const ArrayNumeric<T1>& A, const ArrayNumeric<T2>& B) {
    assert(A.Size()==B.Size());
    return _DotN(A,B,A.Size());
  }

  template <typename T>
  T BlasDot(const ArrayNumeric<T>& A,const ArrayNumeric<T>& B) {
    typedef typename IsBlasable<T>::Type    BlasCheck;
    assert(A.IsValid());
    assert(B.IsValid());
    assert(A.Size()==B.Size());
    long m=A.Size(), one=1;
    return BLAS<T>::Dot(&m,A.Head(),&one,B.Head(),&one);
  }

}

#endif

