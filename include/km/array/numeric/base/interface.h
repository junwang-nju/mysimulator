
#ifndef _Array_Numeric_Base_Interface_H_
#define _Array_Numeric_Base_Interface_H_

#include "array/base/interface.h"
#include "basic/sum.h"
#include "basic/abs-sum.h"
#include "basic/scale.h"
#include "basic/shift.h"

namespace mysimulator {

  template <typename T>
  class ArrayNumeric : public ArrayBase<T> {

    public:

      typedef ArrayNumeric<T>   Type;
      typedef ArrayBase<T>      ParentType;
      typedef typename IsNumeric<T>::Type NumericCheck;

      ArrayNumeric() : ParentType() {}
      ~ArrayNumeric() { Clear(*this); }

      typename DataType<ArrayNumeric<T> >::Type Summation() const {
        typedef typename IsSumable<ArrayNumeric<T> >::Type   SumCheck;
        assert(this->IsValid());
        typename DataType<ArrayNumeric<T> >::Type sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;) sum+=_Sum(*(p++));
        return sum;
      }
      typename DataType<ArrayNumeric<T> >::Type AbsSummation() const {
        typedef typename IsSumable<ArrayNumeric<T> >::Type   SumCheck;
        assert(this->IsValid());
        typename DataType<ArrayNumeric<T> >::Type sum=0;
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;) sum+=_AbsSum(*(p++));
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
      void Scale(const ArrayNumeric<T1>& fac, unsigned int n) {
        typedef typename IsScalable<ArrayNumeric<T>,ArrayNumeric<T1> >::Type
                ScaleCheck;
        assert(this->IsValid());
        assert(fac.IsValid());
        assert(n<=this->Size());
        assert(n<=fac.Size());
        T *p=this->Head(), *pEnd=p+n;
        T1 *q=fac.Head();
        for(;p!=pEnd;)  _Scale(*(p++),*(q++));
      }
      template <typename T1>
      void Scale(const ArrayNumeric<T1>& fac) {
        assert(this->Size()==fac.Size());
        Scale(fac,this->Size());
      }

      template <typename T1>
      void Shift(const T1& fac) {
        typedef typename IsShiftable<ArrayNumeric<T>,T1>::Type  ShiftCheck;
        assert(this->IsValid());
        T *p=this->Head(), *pEnd=p+this->Size();
        for(;p!=pEnd;)  _Shift(*(p++),fac);
      }
      template <typename T1>
      void Shift(const ArrayNumeric<T1>& fac, unsigned int n) {
        typedef typename IsShiftable<ArrayNumeric<T>,ArrayNumeric<T1> >::Type
                ShiftCheck;
        assert(this->IsValid());
        assert(fac.IsValid());
        assert(n<=this->Size());
        assert(n<=fac.Size());
        T *p=this->Head(), *pEnd=p+n;
        T1 *q=fac.Head();
        for(;p!=pEnd;)  _Shift(*(p++),*(q++));
      }
      template <typename T1>
      void Shift(const ArrayNumeric<T1>& fac) {
        assert(this->Size()==fac.Size());
        Shift(fac,this->Size());
      }

    private:

      ArrayNumeric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(ArrayNumeric<T>& A) { Clear(static_cast<ArrayBase<T>&>(A)); }

  template <typename T>
  typename DataType<ArrayNumeric<T> >::Type _Sum(const ArrayNumeric<T>& A) {
    return A.Summation();
  }

  template <typename T>
  typename DataType<ArrayNumeric<T> >::Type _AbsSum(const ArrayNumeric<T>& A) {
    return A.AbsSummation();
  }

  template <typename T, typename T1>
  void _Scale(ArrayNumeric<T>& A, const T1& fac) { A.Scale(fac); }

  template <typename T, typename T1>
  void _Scale(ArrayNumeric<T>& A, const ArrayNumeric<T1>& fac, unsigned int n) {
    A.Scale(fac,n);
  }

  template <typename T, typename T1>
  void _Shift(ArrayNumeric<T>& A, const T1& fac) { A.Shift(fac); }

  template <typename T, typename T1>
  void _Shift(ArrayNumeric<T>& A,const ArrayNumeric<T1>& fac,unsigned int n) {
    A.Shift(fac,n);
  }

}

#endif

