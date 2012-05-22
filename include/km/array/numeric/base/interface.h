
#ifndef _Array_Numeric_Base_Interface_H_
#define _Array_Numeric_Base_Interface_H_

#include "array/base/interface.h"
#include "basic/sum.h"
#include "basic/abs-sum.h"
#include "basic/scale.h"
#include "basic/shift.h"
#include "type/combine.h"
#include "type/is-intrinsic.h"

namespace mysimulator {

  template <typename T>
  class ArrayNumeric : public ArrayBase<T> {

    public:

      typedef ArrayNumeric<T>   Type;
      typedef ArrayBase<T>      ParentType;
      typedef typename IsNumeric<Type>::Type NumericCheck;
      template <typename T1,typename T2>
      friend typename CombineType<typename DataType<T1>::Type,
                                  typename DataType<T2>::Type>::Type
      _Dot(const ArrayNumeric<T1>&,const ArrayNumeric<T2>&);

      ArrayNumeric() : ParentType() {}
      ~ArrayNumeric() { Clear(*this); }

      typename DataType<Type>::Type Summation() const {
        typedef typename IsNumeric<ArrayNumeric<T> >::Type   SumCheck;
        assert(this->IsValid());
        typename DataType<Type>::Type sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;) sum+=_Sum(*(p++));
        return sum;
      }
      typename DataType<Type>::Type AbsSummation() const {
        typedef typename IsNumeric<ArrayNumeric<T> >::Type   SumCheck;
        assert(this->IsValid());
        typename DataType<Type>::Type sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;) sum+=_AbsSum(*(p++));
        return sum;
      }

      typename DataType<Type>::Type NormSQ() const {
        typedef typename IsNumeric<ArrayNumeric<T> >::Type NormCheck;
        typename DataType<Type>::Type sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  sum+=_NormSQ(*(p++));
        return sum;
      }

      template <typename T1>
      void Scale(const T1& fac) {
        typedef typename IsScalable<ArrayNumeric<T>,T1>::Type   ScaleCheck;
        assert(this->IsValid());
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  _Scale(*(p++),fac);
      }
      template <typename T1>
      void Scale(const ArrayNumeric<T1>& fac) {
        typedef typename IsScalable<ArrayNumeric<T>,ArrayNumeric<T1> >::Type
                ScaleCheck;
        assert(this->IsValid());
        assert(fac.IsValid());
        assert(this->Size()==fac.Size());
        T *p=this->Head(), *pEnd=p+this->Size();
        T1 *q=fac.Head();
        for(;p!=pEnd;)  _Scale(*(p++),*(q++));
      }

      template <typename T1>
      void Shift(const T1& fac) {
        typedef typename IsShiftable<ArrayNumeric<T>,T1>::Type  ShiftCheck;
        assert(this->IsValid());
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  _Shift(*(p++),fac);
      }
      template <typename T1>
      void Shift(const ArrayNumeric<T1>& fac) {
        typedef typename IsShiftable<ArrayNumeric<T>,ArrayNumeric<T1> >::Type
                ShiftCheck;
        assert(this->IsValid());
        assert(fac.IsValid());
        assert(this->Size()==fac.Size());
        T *p=this->Head(), *pEnd=p+this->Size();
        T1 *q=fac.Head();
        for(;p!=pEnd;)  _Shift(*(p++),*(q++));
      }

      template <typename T1>
      void NegShift(const T1& fac) {
        typedef typename IsNegShiftable<ArrayNumeric<T>,T1>::Type NegShiftCheck;
        assert(this->IsValid());
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  _NegShift(*(p++),fac);
      }
      template <typename T1>
      void NegShift(const ArrayNumeric<T1>& fac) {
        typedef typename IsNegShiftable<ArrayNumeric<T>,ArrayNumeric<T1> >::Type
                NegShiftCheck;
        assert(this->IsValid());
        assert(fac.IsValid());
        assert(this->Size()==fac.Size());
        T *p=this->Head(), *pEnd=p+this->Size();
        T1 *q=fac.Head();
        for(;p!=pEnd;)  _NegShift(*(p++),*(q++));
      }

      template <typename T1,typename T2>
      void Shift(const ArrayNumeric<T1>& A,const T2& d) {
        typedef typename IsShiftable3<ArrayNumeric<T>,ArrayNumeric<T1>,T2>::Type
                ShiftCheck;
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
        typedef typename
        IsShiftable3<ArrayNumeric<T>,ArrayNumeric<T1>,ArrayNumeric<T2> >::Type
        ShiftCheck;
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
        typedef typename
        IsShiftable4<ArrayNumeric<T>,ArrayNumeric<T2>,ArrayNumeric<T3>,T1>::Type
        ShiftCheck;
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

    private:

      ArrayNumeric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(ArrayNumeric<T>& A) { Clear(static_cast<ArrayBase<T>&>(A)); }

  template <typename T1, typename T2>
  void _Copy(ArrayNumeric<T1>& A1,const ArrayNumeric<T2>& A2) { A1.Copy(A2); }

  template <typename T1, typename T2>
  void _Fill(ArrayNumeric<T1>& A, const T2& fac) { A.Fill(fac); }

  template <typename T>
  void _Imprint(ArrayNumeric<T>& A, const ArrayNumeric<T>& B) { A.Imprint(B); }

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

}

#endif

