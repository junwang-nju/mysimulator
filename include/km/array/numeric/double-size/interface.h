
#ifndef _Array_Numeric_DoubleSize_Interface_H_
#define _Array_Numeric_DoubleSize_Interface_H_

#include "array/numeric/base/interface.h"
#include "type/is-double-size.h"
#include "linear-algebra/blas.h"

namespace mysimulator {

  template <typename T>
  class ArrayNumericDoubleSize : public ArrayNumeric<T> {

    public:

      typedef ArrayNumericDoubleSize<T> Type;
      typedef ArrayNumeric<T>   ParentType;
      typedef typename IsDoubleSize<typename DataType<Type>::Type>::Type
              DoubleSizeCheck;

      ArrayNumericDoubleSize() : ParentType() {}
      ~ArrayNumericDoubleSize() { Clear(*this); }

      void BlasCopy(const ArrayNumericDoubleSize<T>& A) {
        typedef typename IsDoubleSize<T>::Type  DoubleSizeCheck;
        assert(this->IsValid());
        assert(A.IsValid());
        assert(this->Size()==A.Size());
        long m=this->Size(), one=1;
        double *p=reinterpret_cast<double*>(A.Head());
        double *q=reinterpret_cast<double*>(this->Head());
        BLAS<double>::Copy(&m,p,&one,q,&one);
      }
      void BlasFill(const T& d) {
        typedef typename IsDoubleSize<T>::Type  DoubleSizeCheck;
        assert(this->IsValid());
        long m=this->Size(), one=1, zero=0;
        double *p=reinterpret_cast<double*>(const_cast<T*>(&d));
        double *q=reinterpret_cast<double*>(this->Head());
        BLAS<double>::Copy(&m,p,&zero,q,&one);
      }

    private:

      ArrayNumericDoubleSize(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(ArrayNumericDoubleSize<T>& A) {
    Clear(static_cast<ArrayNumeric<T>&>(A));
  }

  template <typename T1,typename T2>
  void _Copy(ArrayNumericDoubleSize<T1>& A,const ArrayNumericDoubleSize<T2>& B){
    A.Copy(B);
  }

  template <typename T1,typename T2>
  void _Fill(ArrayNumericDoubleSize<T1>& A,const T2& fac) { A.Fill(fac); }

  template <typename T>
  void _Imprint(ArrayNumericDoubleSize<T>& A,
                const ArrayNumericDoubleSize<T>& B) { A.Imprint(B); }

  template <typename T>
  typename DataType<ArrayNumericDoubleSize<T> >::Type
  _Sum(const ArrayNumericDoubleSize<T>& A) {  return A.Summation(); }

  template <typename T>
  typename DataType<ArrayNumericDoubleSize<T> >::Type
  _AbsSum(const ArrayNumericDoubleSize<T>& A) { return A.AbsSummation(); }

  template <typename T>
  typename DataType<ArrayNumericDoubleSize<T> >::Type
  _NormSQ(const ArrayNumericDoubleSize<T>& A) { return A.NormSQ(); }

  template <typename T, typename T1>
  void _Scale(ArrayNumericDoubleSize<T>& A,const T1& fac) { A.Scale(fac); }

  template <typename T, typename T1>
  void _Shift(ArrayNumericDoubleSize<T>& A,const T1& fac) { A.Shift(fac); }

  template <typename T, typename T1>
  void _NegShift(ArrayNumericDoubleSize<T>& A,const T1& d) { A.NegShift(d); }

  template <typename T, typename T1, typename T2>
  void _Shift(ArrayNumericDoubleSize<T>& A,const ArrayNumericDoubleSize<T1>& B,
              const T2& d) {  A.Shift(B,d); }

  template <typename T, typename T1, typename T2>
  void _Shift(ArrayNumericDoubleSize<T>& A,const T1& d,
              const ArrayNumericDoubleSize<T>& B) { A.Shift(d,B); }

  template <typename T, typename T1, typename T2, typename T3>
  void _Shift(ArrayNumericDoubleSize<T>& A,const T1& d,
              const ArrayNumericDoubleSize<T2>& B,
              const ArrayNumericDoubleSize<T3>& C) { A.Shift(d,B,C); }

}

#endif

