
#ifndef _Array_Numeric_FloatSize_H_
#define _Array_Numeric_FloatSize_H_

#include "array/numeric/base/interface.h"
#include "type/is-float-size.h"
#include "linear-algebra/blas.h"

namespace mysimulator {

  template <typename T>
  class ArrayNumericFloatSize : public ArrayNumeric<T> {

    public:

      typedef ArrayNumericFloatSize<T>  Type;
      typedef ArrayNumeric<T> ParentType;
      typedef typename IsFloatSize<typename DataType<Type>::Type>::Type
              FloatSizeCheck;

      ArrayNumericFloatSize() : ParentType() {}
      ~ArrayNumericFloatSize() { Clear(*this); }

      void BlasCopy(const ArrayNumericFloatSize<T>& A) {
        typedef typename IsFloatSize<T>::Type FloatSizeCheck;
        assert(this->IsValid());
        assert(A.IsValid());
        assert(this->Size()==A.Size());
        long m=this->Size(), one=1;
        float *p=reinterpret_cast<float*>(A.Head());
        float *q=reinterpret_cast<float*>(this->Head());
        BLAS<float>::Copy(&m,p,&one,q,&one);
      }
      void BlasFill(const T& d) {
        typedef typename IsFloatSize<T>::Type FloatSizeCheck;
        assert(this->IsValid());
        long m=this->Size(), one=1, zero=0;
        float *p=reinterpret_cast<float*>(const_cast<T*>(&d));
        float *q=reinterpret_cast<float*>(this->Head());
        BLAS<float>::Copy(&m,p,&zero,q,&one);
      }

    private:

      ArrayNumericFloatSize(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void CLear(ArrayNumericFloatSize<T>& A) {
    Clear(static_cast<ArrayNumeric<T>&>(A));
  }

  template <typename T1, typename T2>
  void _Copy(ArrayNumericFloatSize<T1>& A,const ArrayNumericFloatSize<T2>& B) {
    A.Copy(B);
  }

  template <typename T1, typename T2>
  void _Fill(ArrayNumericFloatSize<T1>& A, const T2& fac) { A.Fill(fac); }

  template <typename T>
  void _Imprint(ArrayNumericFloatSize<T>& A,
                const ArrayNumericFloatSize<T>& B) { A.Imprint(B); }

  template <typename T>
  typename DataType<ArrayNumericFloatSize<T> >::Type
  _Sum(const ArrayNumericFloatSize<T>& A) { return A.Summation(); }

  template <typename T>
  typename DataType<ArrayNumericFloatSize<T> >::Type
  _AbsSum(const ArrayNumericFloatSize<T>& A) { return A.AbsSummation(); }

  template <typename T>
  typename DataType<ArrayNumericFloatSize<T> >::Type
  _NormSQ(const ArrayNumericFloatSize<T>& A) { return A.NormSQ(); }

  template <typename T, typename T1>
  void _Scale(ArrayNumericFloatSize<T>& A,const T1& fac) { A.Scale(fac); }

  template <typename T, typename T1>
  void _Shift(ArrayNumericFloatSize<T>& A,const T1& fac) { A.Shift(fac); }

  template <typename T, typename T1>
  void _NegShift(ArrayNumericFloatSize<T>& A,const T1& d) { A.NegShift(d); }

  template <typename T,typename T1,typename T2>
  void _Shift(ArrayNumericFloatSize<T>& A,const ArrayNumericFloatSize<T1>& B,
              const T2& d) { A.Shift(B,d); }

  template <typename T,typename T1,typename T2>
  void _Shift(ArrayNumericFloatSize<T>& A, const T1& d,
              const ArrayNumericFloatSize<T2>& B) { A.Shift(d,B); }

  template <typename T,typename T1,typename T2, typename T3>
  void _Shift(ArrayNumericFloatSize<T>& A,  const T1& d,
              const ArrayNumericFloatSize<T2>& B,
              const ArrayNumericFloatSize<T3>& C) { A.Shift(d,B,C); }

}

#endif

